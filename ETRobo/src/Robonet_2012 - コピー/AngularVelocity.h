#ifndef ANGULARVELOCITY_H_
#define ANGULARVELOCITY_H_
/*************************************************************************

  AngularVelocity.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "port_define.h"


/*===========================================================================
  define
===========================================================================*/
#define ANGULAR_VELOCITY_NUM 10			/* 角速度を格納する配列の大きさ */
#define ANGULAR_VELOCITY_MEAN_NUM 10	/* 平均値を格納する配列の大きさ */
#define ANGULAR_VELOCITY_MEAN_CYCLE 10	/* 平均値を格納する周期 */
#define DEFAULT_OFFSET 599				/* ジャイロセンサオフセット値のデフォルト値 */


/*===========================================================================
  角速度クラス [AngularVelocity]
===========================================================================*/
/* 属性 */
typedef struct {
	U16 offsetValue;								/* ジャイロセンサオフセット値 */
	U16 angularVelocity[ANGULAR_VELOCITY_NUM];		/* 角速度値を格納する配列 */
	U16 meanAngularVelocity[ANGULAR_VELOCITY_NUM];	/* 角速度の平均値を格納する配列 */
	U8 meanCounter;									/* 平均値を更新する周期をカウント */
} AngularVelocity;

/* 操作 */
void AngularVelocity_init(AngularVelocity* this);					/* 初期化操作 */
void AngularVelocity_finish(AngularVelocity* this); 				/* 終了操作 */
void AngularVelocity_Calibration(AngularVelocity* this);			/* オフセット値キャリブレーション */
U16 AngularVelocity_getOffsetValue(AngularVelocity* this);			/* オフセット値取得 */
U16 AngularVelocity_updateAngularVelocity(AngularVelocity* this);	/* 角速度更新 */
U16 AngularVelocity_getMeanAngularVelocity(AngularVelocity* this);	/* 平均値を取得 */

#endif

