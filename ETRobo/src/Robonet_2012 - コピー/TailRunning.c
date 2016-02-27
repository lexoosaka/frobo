/*************************************************************************

  TailRunning.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "TailRunning.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : TailRunning_init
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �R���X�g���N�^
  MEMO        :
===========================================================================*/
void TailRunning_init(
	TailRunning* this,
	CommandValue* commandValue,
	TailControl* tailControl,
	Pwm* pwmL,
	Pwm* pwmR
)
{
	/* ������������ */
	this->commandValue = commandValue;
	this->tailControl = tailControl;
	this->pwm[0] = pwmL;
	this->pwm[1] = pwmR;
	this->motorRight = 0;
	this->motorLeft = 0;
}

/*===========================================================================
  FUNCTION    : TailRunning_finish
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �f�X�g���N�^
  MEMO        :
===========================================================================*/
void TailRunning_finish(TailRunning* this)
{

}

/*===========================================================================
  FUNCTION    : TailRunning_executionBalanceRunning
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �|�����s���s��
  MEMO        :
===========================================================================*/
void TailRunning_executionTailRunning(TailRunning* this)
{
	signed char pwmL = this->motorLeft;
	signed char pwmR = this->motorRight;

	/* �|������API���Ă΂Ȃ� */

	/* ���[�^�ɏo�� */
//	nxt_motor_set_speed(PORT_LEFT_MOTOR, pwmL, 1);
//	nxt_motor_set_speed(PORT_RIGHT_MOTOR, pwmR, 1);

	nxt_motor_set_speed(PORT_LEFT_MOTOR, (pwmL + MOVE_PARAM), 1);
	nxt_motor_set_speed(PORT_RIGHT_MOTOR, (pwmR - MOVE_PARAM), 1);
	/* Pwm�l���X�V */
	Pwm_updatePwm((this->pwm[0]), pwmL);
	Pwm_updatePwm((this->pwm[1]), pwmR);
}

