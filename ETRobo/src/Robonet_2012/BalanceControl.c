/*************************************************************************

  BalanceControl.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "BalanceControl.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : BalanceControl_init
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : コンストラクタ
  MEMO        :
===========================================================================*/
void BalanceControl_init(
	BalanceControl* this,
	CommandValue* commandValue,
	AngularVelocity* angularVelocity,
	Pwm* pwmL,
	Pwm* pwmR
)
{
	/* 属性を初期化 */
	this->commandValue = commandValue;
	this->angularVelocity = angularVelocity;
	this->pwm[0] = pwmL;
	this->pwm[1] = pwmR;
}

/*===========================================================================
  FUNCTION    : BalanceControl_finish
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : デストラクタ
  MEMO        :
===========================================================================*/
void BalanceControl_finish(BalanceControl* this)
{

}

/*===========================================================================
  FUNCTION    : BalanceControl_executionBalanceRunning
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : 倒立走行を行う
  MEMO        :
===========================================================================*/
void BalanceControl_executionBalanceRunning(BalanceControl* this)
{
	signed char pwmL = 0;
	signed char pwmR = 0;

	/* 倒立制御APIを呼ぶ */
	balance_control
	(
		(float)CommandValue_getForward(this->commandValue),
		(float)CommandValue_getTurn(this->commandValue),
		(float)AngularVelocity_updateAngularVelocity(this->angularVelocity),
		(float)AngularVelocity_getOffsetValue(this->angularVelocity),
		(float)nxt_motor_get_count(PORT_LEFT_MOTOR),
		(float)nxt_motor_get_count(PORT_RIGHT_MOTOR),
		(float)ecrobot_get_battery_voltage(),
		&pwmL,
		&pwmR
	);
	/* モータに出力 */
//	nxt_motor_set_speed(PORT_LEFT_MOTOR, pwmL, 1);
//	nxt_motor_set_speed(PORT_RIGHT_MOTOR, pwmR, 1);

	nxt_motor_set_speed(PORT_LEFT_MOTOR, (pwmL + MOVE_PARAM), 1);
	nxt_motor_set_speed(PORT_RIGHT_MOTOR, (pwmR - MOVE_PARAM), 1);
	/* Pwm値を更新 */
	Pwm_updatePwm((this->pwm[0]), pwmL);
	Pwm_updatePwm((this->pwm[1]), pwmR);
}

