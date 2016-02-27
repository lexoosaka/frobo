#ifndef RUNNINGMACHINE_H_
#define RUNNINGMACHINE_H_
/*************************************************************************

  RunningMachine.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "Bluetooth.h"
#include "CourseBrightness.h"
#include "RunningPositionInfo.h"
#include "Strategy.h"
#include "Pwm.h"
#include "port_define.h"


/*===========================================================================
  define
===========================================================================*/
#define SP_STRATEGY_MIN_ID 125		/* この値以上かつSP_STRATEGY_MAX_ID未満の場合、特殊戦略を実行 */
#define SP_STRATEGY_MAX_ID 255		/* この値未満かつSP_STRATEGY_MIN_ID以上の場合、特殊戦略を実行 */

/*===========================================================================
  走行体クラス [RunningMachine]
===========================================================================*/
/* 属性 */
typedef struct {
	RunningPositionInfo* runningPositionInfo;	/* 走行位置情報クラスのポインタ */
	Bluetooth* bluetooth;				/* Bluetoothクラスポインタ */
	CourseBrightness* courseBrightness;			/* コース輝度値クラスのポインタ */
	Pwm* pwm[2];								/* Pwm値クラスのポインタ */
	Strategy* strategy[2];						/* 戦略クラスのポインタ */
} RunningMachine;

/* 操作 */
void RunningMachine_init(
	RunningMachine* this,
	RunningPositionInfo* runningPositionInfo,
	CourseBrightness* courseBrightness,
	Bluetooth* bluetooth,
	Pwm* pwmL,
	Pwm* pwmR,
	Strategy* strategy,
	Strategy* spStrategy
); 													/* 初期化操作 */
void RunningMachine_finish(RunningMachine* this);	/* 終了操作 */
void RunningMachine_waitStart(RunningMachine* this, S16);/* 走行指示待ち */
S8 RunningMachine_judgeFall(RunningMachine* this);	/* 転倒判定 */
S8 RunningMachine_run(RunningMachine* this); 		/* 走行 */
void RunningMachine_stop(RunningMachine* this);		/* 停止 */

#endif


