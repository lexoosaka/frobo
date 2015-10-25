#ifndef JUDGEMILEAGE_H_
#define JUDGEMILEAGE_H_
/*************************************************************************

  JudgeMileaget.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "RunningPositionInfo.h"


/*===========================================================================
  define
===========================================================================*/


/*===========================================================================
  走行距離判定クラス
===========================================================================*/
/* 属性 */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	判定方法クラス(スーパークラス) */
	RunningPositionInfo* runningPositionInfo; /* 走行位置情報クラスのポインタ */
} JudgeMileage;

/* 操作 */
void JudgeMileage_init(
	JudgeMileage* this,
	RunningPositionInfo* runningPositionInfo
);																		/* 初期化操作 */
void JudgeMileage_finish(JudgeMileage* this);							/* 終了操作 */
S8 JudgeMileage_execution(JudgeMileage* this, S16 mileage, S16 non);	/* 実行 */

#endif

