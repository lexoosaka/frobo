#ifndef JUDGEDIRECTION_H_
#define JUDGEDIRECTION_H_
/*************************************************************************

  JudgeDirectiont.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "RunningPositionInfo.h"


/*===========================================================================
  define
===========================================================================*/
#define DIFF 0					/* JudgeDirection_executionの判定モード⇒現在の向きと戦略開始時の向きの差と判定したい値を比較する */
#define ABSOLUTE 1				/* JudgeDirection_executionの判定モード⇒走行開始時から計測し続けている向きと判定したい値を比較する */
#define DIRECTION_STABILITY 2	/* JudgeDirection_executionの判定モード⇒角度が安定しているか判定＝直線に入ったかを判定 */
#define DIRECTION_RANGE 3		/* DIRECTION_STABILITYで判定する角度の揺れ幅の許容値 */


/*===========================================================================
  向き判定クラス
===========================================================================*/
/* 属性 */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	判定方法クラス(スーパークラス) */
	RunningPositionInfo* runningPositionInfo;	/* 走行位置情報クラスのポインタ */
	S32 stabilityMileage;						/* 安定化計測距離の開始距離 */
	S8 diffCount;								/* 角度の変化量 */
	S16 pastDirection;							/* 直前の角度 */
} JudgeDirection;

/* 操作 */
void JudgeDirection_init(
	JudgeDirection* this,
	RunningPositionInfo* runningPositionInfo
);																					/* 初期化操作 */
void JudgeDirection_finish(JudgeDirection* this);									/* 終了操作 */
S8 JudgeDirection_execution(JudgeDirection* this, S16 targetValue, S16 mode);	/* 実行 */

#endif

