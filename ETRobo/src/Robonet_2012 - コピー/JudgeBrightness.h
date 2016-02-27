#ifndef JUDGEBRIGHTNESS_H_
#define JUDGEBRIGHTNESS_H_
/*************************************************************************

  JudgeBrightness.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "CourseBrightness.h"


/*===========================================================================
  define
===========================================================================*/
#define OVER 0		/* JudgeBrightness_executionの判定モード⇒値以上になったか判定 */
#define UNDER 1		/* JudgeBrightness_executionの判定モード⇒値以下になったか判定 */
#define STABILITY 2	/* JudgeBrightness_executionの判定モード⇒安定しているか判定 */
#define COURSEOUT 3	/* JudgeBrightness_executionの判定モード⇒コースアウトを判定 */
#define EDGE_CHANGE 4
#define RANGE 3		/* JudgeBrightness_executionで安定度を判定する場合の、値の揺れのプラスマイナス方向の許容範囲 */
#define COURSEOUT_RANGE 10
#define STABILITY_COUNT 250


/*===========================================================================
  輝度判定クラス
===========================================================================*/
/* 属性 */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	判定方法クラス(スーパークラス) */
	CourseBrightness* courseBrightness; /* コース輝度クラスのポインタ */
	U16 stabilityCount;
} JudgeBrightness;

/* 操作 */
void JudgeBrightness_init(
	JudgeBrightness* this,
	CourseBrightness* courseBrightness
);																						/* 初期化操作 */
void JudgeBrightness_finish(JudgeBrightness* this);										/* 終了操作 */
S8 JudgeBrightness_execution(JudgeBrightness* this, S16 targetBrightness, S16 mode);	/* 実行 */

#endif

