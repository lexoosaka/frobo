#ifndef JUDGEMARKER_H_
#define JUDGEMARKER_H_
/*************************************************************************

  JudgeMarker.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "CourseBrightness.h"
#include "RunningPositionInfo.h"

/*===========================================================================
  define
===========================================================================*/



/*===========================================================================
  マーカー判定(サーチ)クラス
===========================================================================*/
/* 属性 */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	判定方法クラス(スーパークラス) */
	CourseBrightness* courseBrightness; /* コース輝度クラスのポインタ */
	RunningPositionInfo* runningPositionInfo;
	S32 searchStart;					/* 最後に閾値内にいたポイント */
} JudgeMarker;

/* 操作 */
void JudgeMarker_init(
	JudgeMarker* this,
	CourseBrightness* courseBrightness,
	RunningPositionInfo* runningPositionInfo
);																						/* 初期化操作 */
void JudgeMarker_finish(JudgeMarker* this);										/* 終了操作 */
S8 JudgeMarker_execution(JudgeMarker* this, S16 targetBrightness, S16 mode);	/* 実行 */

#endif
