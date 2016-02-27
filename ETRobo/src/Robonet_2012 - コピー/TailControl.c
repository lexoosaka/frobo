/*************************************************************************

  TailControl.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "TailControl.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : TailControl_init
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �R���X�g���N�^
  MEMO        :
===========================================================================*/
void TailControl_init(
	TailControl* this,
	U32 port
)
{
	this -> port = port;
	this -> TailMotorDir = 0;
	this -> TailMotorInit = 0;
	return ;

}

/*===========================================================================
  FUNCTION    : TailControl_finish
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �f�X�g���N�^
  MEMO        :
===========================================================================*/
void TailControl_finish(TailControl* this)
{

}

/*===========================================================================
  FUNCTION    : TailControl_Set_TailControlDir
  PARAMETERS  : �����̃|�C���^�A�Z�b�g����l
  RETURN      : �Ȃ�
  DESCRIPTION : ���݂̊p�x�Z�b�g
  MEMO        :
===========================================================================*/
void TailControl_Set_TailControlDir(TailControl* this, S16 SetDir){
	this -> TailMotorDir = SetDir;

	return;
}


/*===========================================================================
  FUNCTION    : TailControl_Get_TailControlDir
  PARAMETERS  : �����̃|�C���^
  RETURN      : ���݂̊p�x�擾
  DESCRIPTION : ���݂̊p�x�擾
  MEMO        :
===========================================================================*/
S16 TailControl_Get_TailControlDir(TailControl* this){
	return this -> TailMotorDir;
}


/*===========================================================================
  FUNCTION    : TailControl_Set_TailControlInit
  PARAMETERS  : �����̃|�C���^�A�Z�b�g����l
  RETURN      : �Ȃ�
  DESCRIPTION : �L�����u���[�V�������ɏ����l�Z�b�g
  MEMO        :
===========================================================================*/
void TailControl_Set_TailControlInit(TailControl* this, S16 SetDir){
	this -> TailMotorInit = SetDir;

	return;
}


/*===========================================================================
  FUNCTION    : TailControl_Get_TailControlDir
  PARAMETERS  : �����̃|�C���^
  RETURN      : �����l�擾
  DESCRIPTION : �����l�擾
  MEMO        :
===========================================================================*/
S16 TailControl_Get_TailControlInit(TailControl* this){
	return this -> TailMotorInit;
}

/*===========================================================================
  FUNCTION    : TailControl_Calibration
  PARAMETERS  : �����̃|�C���^
  RETURN      : �����l�擾
  DESCRIPTION : �����l�擾
  MEMO        :
===========================================================================*/
void TailControl_Calibration(TailControl* this){

	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set TAIL");
	display_update();
	nxt_motor_set_count((PORT_TAIL_MOTOR), 300);

	/* �擾�����l��\������ */
/*	while(0== (ecrobot_is_ENTER_button_pressed()))
	{
		if(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR))
		{
//			TailControl_Set_TailControlInit(this, nxt_motor_get_count(PORT_TAIL_MOTOR));
			this -> TailMotorInit = (S16)(nxt_motor_get_count(PORT_TAIL_MOTOR));
			while(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR));
		}
	}
*/
//	this -> TailMotorNow = this -> TailMotorInit;
	this -> TailMotorInit = 409;
	this -> TailMotorNow = 200;
	/* �K���ݒ�I������ */
	systick_wait_ms(1500);
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp TAIL");
	display_goto_xy(7, 4);
	display_unsigned(this -> TailMotorInit, 0);
	systick_wait_ms(1500);

	return;
}

/*===========================================================================
  FUNCTION    : TailControl_TailOperation
  PARAMETERS  : �����̃|�C���^
  RETURN      : �Ȃ�
  DESCRIPTION : �K������
  MEMO        :
===========================================================================*/
void TailControl_TailOperation(TailControl* this){
//	S16 temp =  this->TailMotorInit  - nxt_motor_get_count(PORT_TAIL_MOTOR);
S16 temp = this -> TailMotorNow - nxt_motor_get_count(PORT_TAIL_MOTOR);
	temp = temp * 2;

	if(temp > 10)
	{
		temp = 10;
	}
	if(temp < -10)
	{
		temp = -10;
	}
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("Tail Culc");
	display_goto_xy(0, 5);
	display_int(temp, 0);
	display_update();

	nxt_motor_set_speed(PORT_TAIL_MOTOR, temp, 1);
	return;
}
