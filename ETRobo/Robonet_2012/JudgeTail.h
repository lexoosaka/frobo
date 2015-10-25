#ifndef JUDGETAIL_H_
#define JUDGETAIL_H_
/*************************************************************************

  JudgeTail.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "TailControl.h"

/*===========================================================================
  define
===========================================================================*/
#define JUDGETAILSTABILITY 3
/*===========================================================================
  尻尾判定クラス
===========================================================================*/
/* 属性 */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	判定方法クラス(スーパークラス) */
	TailControl tailControl;
	S16 SetTailDir;
} JudgeTail;

/* 操作 */
void JudgeTail_init(JudgeTail* this, TailControl* tailControl);				/* 初期化操作 */
void JudgeTail_finish(JudgeTail* this);						/* 終了操作 */
S8 JudgeTail_execution(JudgeTail* this, S16, S16);			/* 実行 */

#endif

