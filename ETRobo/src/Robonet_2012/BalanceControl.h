#ifndef BALANCECONTROL_H_
#define BALANCECONTROL_H_
/*************************************************************************

  BalanceControl.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "balancer.h"
#include "CommandValue.h"
#include "AngularVelocity.h"
#include "Pwm.h"
#include "port_define.h"

/*===========================================================================
  define
===========================================================================*/
#define PWM_MOVE 0.625F				/* turn(旋回命令値)1に対するPWMの変化量 */
#define MOVE_PARAM 10 * PWM_MOVE	/* 左右のモータに出力するPWMの調整値 */

/*===========================================================================
  倒立制御クラス [BalanceControl]
===========================================================================*/
/* 属性 */
typedef struct {
	CommandValue* commandValue;			/* 命令値クラスのポインタ */
	AngularVelocity* angularVelocity;	/* 角速度クラスのポインタ */
	Pwm* pwm[2];						/* PWMクラスのポインタ(左右) */
	S8 gyroFlag;						/* 倒立制御するかどうか */
	S8 flagSpeed;						/* 倒立制御しない時のモーターに提出する値 */
} BalanceControl;

/* 操作 */
void BalanceControl_init(
	BalanceControl* this,
	CommandValue* commandValue,
	AngularVelocity* angularVelocity,
	Pwm* pwmL,
	Pwm* pwmR
);																	/* 初期化操作 */
void BalanceControl_finish(BalanceControl* this);					/* 終了操作 */
void BalanceControl_executionBalanceRunning(BalanceControl* this);	/* 倒立走行 */

#endif

