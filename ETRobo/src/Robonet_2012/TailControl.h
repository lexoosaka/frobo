#ifndef TAILCONTROL_H_
#define TAILCONTROL_H_
/*************************************************************************

  TailControl.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "port_define.h"

/*===========================================================================
  define
===========================================================================*/

/*===========================================================================
  尻尾管理クラス
===========================================================================*/
/* 属性 */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	判定方法クラス(スーパークラス) */
	S16 TailMotorDir;					/* 現在の角度 */
	S16 TailMotorInit;					/* キャリブレーション値 */
	S16 TailMotorNow;
//	S16 SetTailDir;
	U32 port;							/* モータが接続されているポート */
} TailControl;

/* 操作 */
void TailControl_init(TailControl* this, U32 port);				/* 初期化操作 */
void TailControl_finish(TailControl* this);						/* 終了操作 */
void TailControl_Set_TailControlDir(TailControl* this, S16);	/* 現在の角度セット */
S16 TailControl_Get_TailControlDir(TailControl* this);			/* 現在の角度取得 */
void TailControl_Set_TailControlInit(TailControl* this, S16);	/* キャリブレーションした初期値 */
S16 TailControl_Get_TailControlInit(TailControl* this);			/* 初期値取得 */
void TailControl_Calibration(TailControl* this);				/* キャリブレーション */
void TailControl_TailOperation(TailControl* this);				/* 尻尾操作 */

#endif

