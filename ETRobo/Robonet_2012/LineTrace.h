#ifndef LINETRACE_H_
#define LINETRACE_H_
/*************************************************************************

  LineTrace.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "OperationMethod.h"
#include "CourseBrightness.h"
#include "CommandValue.h"


/*===========================================================================
  define
===========================================================================*/
#define LEFT_EDGE 0				/* 左エッジを走行 */
#define RIGHT_EDGE 1			/* 右エッジを走行 */
#define DIFF_CTRL_OFF_LEFT 2	/* 左エッジを走行(比例制御のみ) */
#define DIFF_CTRL_OFF_RIGHT 3	/* 右エッジを走行(比例制御のみ) */
#define LEFT_SMALL 4			/* 目標値を減少させたライントレース */
#define RIGHT_SMALL 5			/* 目標値を減少させたライントレース */
#define LEFT_BIG 6			/* 目標値を減少させたライントレース */
#define RIGHT_BIG 7			/* 目標値を減少させたライントレース */
#define SMOOTHNESS_LEFT 8		/* 旋回量を抑えた左エッジ走行 */
#define SMOOTHNESS_RIGHT 9		/* 旋回量を抑えた右エッジ走行 */
#define P_PARAM 1.2F			/* 比例制御パラメータ */
#define D_PARAM 4.0F			/* 微分制御パラメータ */


/*===========================================================================
  ライントレースクラス [LineTrace]
===========================================================================*/
/* 属性 */
typedef struct {
	OperationMethod inherit_operationMethod;		/* 走行方法クラス(スーパークラス) */
	CourseBrightness* courseBrightness;				/* コース輝度クラスのポインタ */
} LineTrace;

/* 操作 */
void LineTrace_init(
	LineTrace* this,
	CourseBrightness* courseBrightness,
	CommandValue* commandValue
);															/* 初期化操作 */
void LineTrace_finish(LineTrace* this);						/* 終了操作 */
S8 LineTrace_execution(LineTrace* this, S8 speed, S16 mode);	/* 実行 */

#endif

