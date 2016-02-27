/*************************************************************************

  SeesawPass.c
  
  �v���O�����T�v
  ET���{�R��2010�N�x�̓�A�V�[�\�[���U�������߂̃v���O�����B
  
*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "SeesawPass.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : SeesawPass_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �R���X�g���N�^
  MEMO        : 
===========================================================================*/
void SeesawPass_init(SeesawPass* this, MotorCount* motorCountL, MotorCount* motorCountR, Pwm* pwmL, Pwm* pwmR, BlindRunning* blindRunning)
{
	this -> motorCountL = motorCountL;
	this -> motorCountR = motorCountR;
	this -> pwmL = pwmL;
	this -> pwmR = pwmR;
	this -> blindRunning = blindRunning;
	this -> seesawTime = 1;
	this -> past_param = 0.025;
	
	return ;
}

/*===========================================================================
  FUNCTION    : SeesawPass_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void SeesawPass_finish(SeesawPass* this)
{
	return ;
}

/*===========================================================================
  FUNCTION    : SeesawPass_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �V�[�\�[��̃C�x���g���Ǘ�
  MEMO        : 
===========================================================================*/
S8 SeesawPass_execution(SeesawPass* this, S16 judgeParam, S16 seesawCtrlTime)
{
	S8 rtn = 0;
	S8 forward = 0;
	S16 turn = 0;
	S16 nowCountL; /* �u���C���h���s�J�n�ォ��̍����[�^�̉�]�p */
	S16 nowCountR; /* �u���C���h���s�J�n�ォ��̉E���[�^�̉�]�p */

	if(seesawCtrlTime == 0)		/* �V�[�\�[��������O*/
	{
		rtn = (BlindRunning_execution((this -> blindRunning), SEESAW_START_PARAM, 0));
	}
	else if(seesawCtrlTime == 1)		//�V�[�\�[���������̂ŏ��S
	{
		this -> seesawTime = this -> seesawTime + 1;
		forward = SEESAW_START_PARAM + (this -> seesawTime / SEESAW_INCR_PARAM);		//���X�ɑO�i���ߒl���㏸������
//		forward = 40;
//		rtn = (BlindRunning_execution(this -> blindRunning, forward, 0));
		
		/* �i���𗘗p���ăV�[�\�[�ɑ΂��Đ^���ʂ�������悤�ɂ���B*/
		nowCountL = MotorCount_getMotorCount(this -> motorCountL) - MotorCount_getPastMotorCount(this -> motorCountL, 1);
		nowCountR = MotorCount_getMotorCount(this -> motorCountR) - MotorCount_getPastMotorCount(this -> motorCountR, 1);
		
		if(-1 < nowCountL && -1 < nowCountR)//�i���ɂԂ������疳���ɑO�i���Ȃ��B
		{
			forward = -1;
		}
/*		
		if(-1 < nowCountL && nowCountR < 0)
		{
			turn = -1;
		}
		else if(-1 < nowCountR && nowCountL < 0)
		{
			turn = 1;//minus
		}
		else
		{
			turn = -1;
		}
*/
		rtn = (BlindRunning_execution(this -> blindRunning, forward, turn));
//	rtn = 1;
//		CommandValue_setCommandValue((this -> blindRunning->inherit_operationMethod.commandValue), turn, forward);
	}
	else if(seesawCtrlTime == 2 && judgeParam == EXECUTIONSEESAWSTOP)		//�V�[�\�[�����n�_�܂ňړ�B
	{
		if(this -> seesawTime != 1)
		{
			this -> seesawTime = 1;
		}
		rtn = (BlindRunning_execution(this -> blindRunning, 20, 0));
	}
	else if(seesawCtrlTime == 2 && judgeParam == EXECUTIONSEESAWPASS)	//�V�[�\�[�O���ʉ�
	{
		rtn = (BlindRunning_execution(this -> blindRunning, 40, 1200));
	}
	else if(seesawCtrlTime == 3 && judgeParam == EXECUTIONSEESAWSTOP)		//����J�nB
	{
//		rtn = (BlindRunning_execution(this -> blindRunning, 10, -158));
		rtn = 1;
		CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), -20, 1);
	}
	else if(seesawCtrlTime == 3 && judgeParam == EXECUTIONSEESAWPASS)
	{
		forward = (S8)SeesawPass_seesawNormalPass(this);
		rtn = (BlindRunning_execution(this -> blindRunning, forward, 0));
	}
	else if(seesawCtrlTime == 4)		//����J�nB
	{
		rtn = (BlindRunning_execution(this -> blindRunning, 10, 158));
		rtn = 1;
		CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), -15, 0);
	}
	else if(seesawCtrlTime == 5)
	{
//		rtn = (BlindRunning_execution(this -> blindRunning, -1, 0));
//		rtn = (BlindRunning_execution(this -> blindRunning, 1, 80));
		rtn = 1;
		CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), -7, 0);
	
	}
	else if(seesawCtrlTime == 6)		//����������B
	{
//		rtn = (BlindRunning_execution(this -> blindRunning, 1, 155));
		rtn = 1;
//		nowCountL = (MotorCount_getMotorCount(this->motorCountL)) - (MotorCount_getStartMotorCount(this->motorCountL));
//		nowCountR = (MotorCount_getMotorCount(this->motorCountR)) - (MotorCount_getStartMotorCount(this->motorCountR));
//		nowCountL = -nowCountL;
		
//		if((nowCountR - nowCountL) >= 0)
//		{
//			forward = -10;
//			turn = -20;
//		}
//		else
//		{
//			forward = 0;
//			turn = -5;
//		}

		CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), -5, 0);
	}
	else if(seesawCtrlTime == 7)
	{
		rtn = (BlindRunning_execution(this -> blindRunning, -10, 0));
	}
	else if(seesawCtrlTime == 8)
	{
		rtn = (BlindRunning_execution(this -> blindRunning, 10, 0));
	}
	else if(seesawCtrlTime == 9)		//������]����B
	{
		if(this -> seesawTime != 1)
		{
			this -> seesawTime = 1;
		}
//		rtn = 1;
//		CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), 10, 10);
		rtn = (BlindRunning_execution(this -> blindRunning ,20, -80));
	}
	else if(seesawCtrlTime == 10)		//�Î~�����݂�S
	{
/*
		this -> seesawTime = this -> seesawTime + 1;
		//�V�[�\�[��Î~�����Ԃ��g���Ď�������ꍇ
		if(((this -> seesawTime / SEESAW_SQUARE_TIME) % 2) == 0)
		{
			forward = SEESAW_STOP_FORWARD;
		}
		else
		{
			forward = (-1) * SEESAW_STOP_FORWARD;
		}
*/
		//�V�[�\�[���~�����[�^��]�p�𗘗p���Ď�������ꍇ
		nowCountL = (MotorCount_getMotorCount(this->motorCountL)) - (MotorCount_getStartMotorCount(this->motorCountL));
		nowCountR = (MotorCount_getMotorCount(this->motorCountR)) - (MotorCount_getStartMotorCount(this->motorCountR));
		if(this -> seesawTime == 1 && nowCountL + nowCountR <  SEESAW_STOP_DIG + SEESAW_SQUARE_DIG)
		{//�O�i��(�ڕW�n�_�����B)
//	old		forward = SEESAW_STOP_FORWARD;
			forward = (SEESAW_STOP_DIG + SEESAW_SQUARE_DIG) - (nowCountL + nowCountR);
		}
		else if(this -> seesawTime == 1 && nowCountL + nowCountR >= SEESAW_STOP_DIG + SEESAW_SQUARE_DIG)
		{//�O�i��(�ڕW�n�_���B��)
//	old		forward = (-1) * SEESAW_STOP_FORWARD;
			forward = -100;
			this -> seesawTime = 2;
		}
		else if(this -> seesawTime == 2 && nowCountL + nowCountR > SEESAW_STOP_DIG)
		{//��i��(�ڕW�n�_�����B)
//	old		forward = (-1) * SEESAW_STOP_FORWARD;
			forward = (nowCountL + nowCountR) - SEESAW_STOP_DIG;
		}
		else if(this -> seesawTime == 2 && nowCountL + nowCountR <= SEESAW_STOP_DIG)
		{//��i��(�ڕW�n�_���B��)
//	old		forward = SEESAW_STOP_FORWARD;
			forward = 100;
			this -> seesawTime = 1;
		}
		else
		{//�����ɂ͂��Ȃ��B
			forward = 0;
			this -> seesawTime = 2;
		}
		//CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), 0, forward);
		forward = forward / 10;
		if(this -> seesawTime == 1)
		{
			forward = forward + 10;
		}
		else if(this -> seesawTime == 2)
		{
			forward = forward - 10;
		}
		rtn = (BlindRunning_execution((this->blindRunning), forward, 0));
	}
	else if(seesawCtrlTime == 11)		//�Î~���I��������J�nB
	{
		rtn = (BlindRunning_execution(this -> blindRunning, 20, -80));
	}
	else if(seesawCtrlTime == 12)		//�V�[�\�[����~���S
	{
		forward = SeesawPass_seesawLeave(this);
		rtn = (BlindRunning_execution(this -> blindRunning, forward, 0));
	}
	else if(seesawCtrlTime >= 13)		//�V�[�\�[����~�肽S ���̐헪�����s����ׂ��Ƃ���
	{
		rtn = (BlindRunning_execution(this -> blindRunning, 40, 0));
	}
	return rtn;
}

S8 SeesawPass_seesawLeave(SeesawPass* this)
{
	S8 forward;
	
	F32 l_motor = 0;
	F32 r_motor = 0;
	F32 result_motor;
	F32 l_angle;
	F32 r_angle;
	U8 i;
	
	for(i=0;i<PWM_NUM;i++)
	{
		l_motor = l_motor + this -> pwmL->pwmValue[i];									/* �����[�^PWM�l */
		r_motor = r_motor + this -> pwmR->pwmValue[i];									/* �E���[�^PWM�l */
	}
	l_angle = this -> motorCountL->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountL->motorCount[0];		/* �����[�^��]�p */
	r_angle = this -> motorCountR->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountR->motorCount[0];		/* �E���[�^��]�p */
	
	result_motor = l_motor + r_motor;
	
	if(result_motor == 0)//����Z�̕����0������\�������
	{
		result_motor = 0.1;
	}
	
	/* �O��i���ߒl�̌���(��������) */
	/* �O�i���ߒl = ��{�O�i���ߒl + ��������l �~ ((�ߋ��̃��[�^��]�p / �ߋ��̃��[�^PWM�l) - (���݂̃��[�^��]�p / ���݂̃��[�^PWM�l)) */
	forward = SEESAW_LEAVE_MAX + (SEESAW_DIFF_PARAM * (this -> past_param - ((l_angle + r_angle) / ((result_motor)))));
	/* �O��i���ߒl��臒l���z���Ă�����臒l�͈͓̔��Ɏ��߂�B */

	if(SEESAW_LEAVE_MAX < forward)
	{
		forward = SEESAW_LEAVE_MAX;
	}
	else if(forward < -100)
	{
		forward = -100;
	}
	/* (���݂̃��[�^��]�p / ���݂̃��[�^PWM�l) */
	this -> past_param = ((l_angle + r_angle) / (result_motor));
	return forward;
}

S8 SeesawPass_seesawNormalPass(SeesawPass* this)
{
	S8 forward;
	
	F32 l_motor = 0;
	F32 r_motor = 0;
	F32 result_motor;
	F32 l_angle;
	F32 r_angle;
	U8 i;

	//static integ_e = 0;
	
	for(i=0;i<PWM_NUM;i++)
	{
		l_motor = l_motor + this -> pwmL->pwmValue[i];									/* �����[�^PWM�l */
		r_motor = r_motor + this -> pwmR->pwmValue[i];									/* �E���[�^PWM�l */
	}
	l_angle = this -> motorCountL->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountL->motorCount[0];		/* �����[�^��]�p */
	r_angle = this -> motorCountR->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountR->motorCount[0];		/* �E���[�^��]�p */
	
	result_motor = (l_motor + r_motor);
	if(result_motor == 0) //����Z�̕����0������\�������
	{
		result_motor = 0.1;
	}
	
	/* �O��i���ߒl�̌���(��ᐧ��) *//*  */
	/* �O�i���ߒl = ��ᐧ��l �~ ((�X��0�x���̃��[�^��]�p / �o�̓��[�^PWM�l) - (���ۂ̃��[�^��]�p / �o�̓��[�^PWM�l)) */
	forward = (SEESAW_PROPO_PARAM * ((SMOOTH_CTRL) - ((l_angle + r_angle) / result_motor)));
	
	/* �O��i���ߒl�̌���(�ϕ�����) */
	/* �O�i���ߒl = ��ᐧ�䌋�ʒl + (�ϕ�����l �~ (�c���΍� / �ϕ�����)) */
	/* ���������Ă邩�ǂ����͕s�� */
	//forward = forward + (SEESAW_INTEG_PARAM * (integ_e / seesaw_time));
	
		/* �O��i���ߒl��臒l�𒴂��Ă�����臒l���Ɏ��߂� */
	if(forward < SEESAW_MIN_FORWARD)
	{
		forward = SEESAW_MIN_FORWARD;
	}
	else if(SEESAW_MAX_FORWARD < forward)
	{
		forward = SEESAW_MAX_FORWARD;
	}
	/* �O��i���ߒl�̌���(��������) */
	/* �O�i���ߒl = ���ϕ����䌋�ʒl + ��������l �~ ((�ߋ��̃��[�^��]�p / �ߋ��̃��[�^PWM�l) - (���݂̃��[�^��]�p / ���݂̃��[�^PWM�l)) */
	forward = forward + (SEESAW_DIFF_PARAM * (this -> past_param - ((l_angle + r_angle) / result_motor)));
	
	/* �O��i���ߒl��臒l�𒴂��Ă�����臒l���Ɏ��߂� */
	if(forward < SEESAW_MIN_FORWARD)
	{
		forward = SEESAW_MIN_FORWARD;
	}
	else if(SEESAW_MAX_FORWARD < forward)
	{
		forward = SEESAW_MAX_FORWARD;
	}
	
	/* (���݂̃��[�^��]�p / ���݂̃��[�^PWM�l) */
	this -> past_param = ((l_angle + r_angle) / result_motor);

	/* �c���΍��v�Z */
//	integ_e = integ_e + (SMOOTH_CTRL- past_param);
	return forward; //�������߂��Ă��]�ԁB

}
