#ifndef BLINDRUNNING_H_
#define BLINDRUNNING_H_
/*************************************************************************

  BlindRunning.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "OperationMethod.h"
#include "MotorCount.h"
#include "CommandValue.h"
#include "RunningPositionInfo.h"


/*===========================================================================
  define
===========================================================================*/


/*===========================================================================
  ブラインド走行クラス [BlindRunning]
===========================================================================*/
/* 属性 */
typedef struct {
	OperationMethod inherit_operationMethod;	/* 走行方法クラス(スーパークラス) */
	MotorCount* motorCount[2];					/* モータ回転角クラスのポインタ(左右) */
}BlindRunning;

/* 操作 */
void BlindRunning_init(
	BlindRunning* this,
	MotorCount* motorCountL,
	MotorCount* motorCountR,
	CommandValue* commandValue
);																			/* 初期化操作 */
void BlindRunning_finish(BlindRunning* this);								/* 終了操作 */
S8 BlindRunning_execution(BlindRunning* this, S8 speed, S16 turningRadius);	/* 実行 */

#endif

