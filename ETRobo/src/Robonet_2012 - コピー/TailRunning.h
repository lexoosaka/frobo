#ifndef TAILRUNNING_H_
#define TAILRUNNING_H_
/*************************************************************************

  TailRunning.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "balancer.h"
#include "CommandValue.h"
#include "Pwm.h"
#include "TailControl.h"
#include "port_define.h"


/*===========================================================================
  define
===========================================================================*/
#define PWM_MOVE 0.625F				/* turn(旋回命令値)1に対するPWMの変化量 */
#define MOVE_PARAM 10 * PWM_MOVE	/* 左右のモータに出力するPWMの調整値 */



/*===========================================================================
  倒立制御クラス [TailRunning]
===========================================================================*/
/* 属性 */
typedef struct {
	CommandValue* commandValue;			/* 命令値クラスのポインタ */
	Pwm* pwm[2];						/* PWMクラスのポインタ(左右) */
	TailControl* tailControl;
	signed char motorLeft;				/* 左モータ出力 */
	signed char motorRight;				/* 右モータ出力 */
} TailRunning;

/* 操作 */
void TailRunning_init(
	TailRunning* this,
	CommandValue* commandValue,
	TailControl* tailControl,
	Pwm* pwmL,
	Pwm* pwmR
);																	/* 初期化操作 */
void TailRunning_finish(TailRunning* this);							/* 終了操作 */
void TailRunning_executionTailRunning(TailRunning* this);		/* 倒立走行 */

#endif

