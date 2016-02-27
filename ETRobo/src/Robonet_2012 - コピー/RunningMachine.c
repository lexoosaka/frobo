/*************************************************************************

  RunningMachine.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include <math.h>
#include "RunningMachine.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : RunningMachine_init
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �R���X�g���N�^
  MEMO        :
===========================================================================*/
void RunningMachine_init(
	RunningMachine* this,
	RunningPositionInfo* runningPositionInfo,
	CourseBrightness* courseBrightness,
	Bluetooth* bluetooth,
	Pwm* pwmL,
	Pwm* pwmR,
	Strategy* strategy,
	Strategy* spStrategy
)
{
	/* ������ */
	this->runningPositionInfo = runningPositionInfo;
	this->courseBrightness = courseBrightness;
	this->bluetooth = bluetooth;
	this->pwm[0] = pwmL;
	this->pwm[1] = pwmR;
	this->strategy[0] = strategy;
	this->strategy[1] = spStrategy;
}

/*===========================================================================
  FUNCTION    : RunningMachine_finish
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �f�X�g���N�^
  MEMO        :
===========================================================================*/
void RunningMachine_finish(RunningMachine* this)
{

}


/*===========================================================================
  FUNCTION    : RunningMachine_waitStart
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : ���s�w���҂�
  MEMO        :
===========================================================================*/
void RunningMachine_waitStart(RunningMachine* this, S16 TailInit)
{

		display_clear(1);
		display_goto_xy(0, 3);
		display_string("Wait Start");
		display_update();
		static int roop_c = 0;
	while(0 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR) || Bluetooth_waitStart(this -> bluetooth))
	{
//			S16 temp = nxt_motor_get_count(PORT_TAIL_MOTOR) - TailInit;
		S16 temp = TailInit - nxt_motor_get_count(PORT_TAIL_MOTOR);
		
		
		
		temp = temp * 10;
		
		if(temp > 100)
		{
			temp = 100;
		}
		if(temp < -100)
		{
			temp = -100;
		}
		if(roop_c >=  500){
			roop_c = 0;
			ecrobot_read_bt(this -> bluetooth -> bt_receive_buf, BT_RCV_BUF_SIZE, BT_RCV_BUF_SIZE);	//master����A�f�[�^���
			ecrobot_send_bt(this -> bluetooth -> bt_receive_buf, BT_RCV_BUF_SIZE, BT_RCV_BUF_SIZE);	//master����A�f�[�^���
			display_clear(0);
			display_goto_xy(0,1);
			display_int(this -> bluetooth -> bt_receive_buf[7], 0);
			display_goto_xy(0,2);
			display_int(this -> bluetooth -> bt_receive_buf[8], 0);
			display_update();

//			Bluetooth_execution(this->bluetooth);
		}
		roop_c++;
		systick_wait_ms(1);
		nxt_motor_set_speed(PORT_TAIL_MOTOR, temp, 1);
		if(this -> bluetooth -> bt_receive_buf[8] != 0){
			break;	
		}
	}
}

/*===========================================================================
  FUNCTION    : RunningMachine_judgeFall
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �]�|���f
  MEMO        :
===========================================================================*/
S8 RunningMachine_judgeFall(RunningMachine* this)
{
	signed char pwmMeanValueL;
	signed char pwmMeanValueR;

	pwmMeanValueL = Pwm_getMeanPwm(this->pwm[0]);
	pwmMeanValueR = Pwm_getMeanPwm(this->pwm[1]);
	if(((pwmMeanValueL == 100) || (pwmMeanValueL == (-100))) && ((pwmMeanValueR == 100) || (pwmMeanValueR == (-100))))
	{
		return (S8)1;
	}
	return (S8)0;
}

/*===========================================================================
  FUNCTION    : RunningMachine_run
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : ���s
  MEMO        :
===========================================================================*/
S8 RunningMachine_run(RunningMachine* this)
{
	U8 rtn = 0;

	/* �]�|�𔻒� */
	if(1 == (RunningMachine_judgeFall(this)))
	{
		return (S8)0;
	}
	/* ���s�ʒu�𐄒� */
	RunningPositionInfo_presumptionPosition(this->runningPositionInfo);

	/* �R�[�X�P�x���X�V */
	CourseBrightness_updateBrightness(this->courseBrightness);

	while(1)
	{
		/* �ʏ�헪�����s */
		rtn = Strategy_execution(this->strategy[0]);
		if(rtn == CONTINUE)
		{
			return (S8)1;
		}
		/* ����헪�����s����ꍇ */
		else if((rtn == EXECUTION_ANOTHER_STRATEGY) || (((SP_STRATEGY_MIN_ID - 1) < rtn) && (rtn < SP_STRATEGY_MAX_ID)))
		{
			if(rtn != EXECUTION_ANOTHER_STRATEGY){
				/* ����헪�̎��s�ԍ���ݒ� */
				Strategy_setStrategyId(this->strategy[1], (rtn - SP_STRATEGY_MIN_ID));

			}
			/* ����헪�����s */
			rtn = Strategy_execution(this->strategy[1]);

			/* ����헪���I�������ꍇ */
			if(rtn == END)
			{
				/* �ʏ�헪�̎��s�ԍ���ݒ� */
				Strategy_setStrategyId(this->strategy[0], (this->strategy[0]->strategyId + 1));
			}

			/* ����헪���I�����Ă��Ȃ��ꍇ */
			else if(rtn == CONTINUE)
			{
				return (S8)1;
			}

			/* ����ȊO */
			else
			{
				return (S8)0;
			}
		}
		/* �I�� */
		else
		{
			return (S8)0;
		}
	}

	return (S8)1;
}

/*===========================================================================
  FUNCTION    : RunningMachine_stop
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : ��~
  MEMO        :
===========================================================================*/
void RunningMachine_stop(RunningMachine* this)
{
	nxt_motor_set_speed(PORT_RIGHT_MOTOR, 0, 1);
	nxt_motor_set_speed(PORT_LEFT_MOTOR, 0, 1);
}

