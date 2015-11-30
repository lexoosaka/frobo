#ifndef COURSEBRIGHTNESS_H_
#define COURSEBRIGHTNESS_H_
/*************************************************************************

  CourseBrightness.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "port_define.h"

/*===========================================================================
  define
===========================================================================*/
#define BRIGHTNESS_NUM 20				/* 輝度値を格納する配列の大きさ */
#define BRIGHTNESS_MEAN_NUM 10			/* 輝度値の平均値を格納する配列の大きさ */
#define BRIGHTNESS_MOVING_AVE_CYCLE 5 	/* 輝度値を格納する配列の大きさ */
#define BRIGHTNESS_MOVING_AVE_NUM 2		/* 移動平均値を格納する配列の大きさ */
#define BRIGHTNESS_MEAN_CYCLE 20		/* 輝度値の平均値を格納する周期 */
#define BLACK 0							/* 引数で指定する色 */
#define WHITE 1							/* 引数で指定する色 */
#define GRAY 2							/* 引数で指定する色 */
#define WHITE_GRAY 3					/* 引数で指定する色 */
#define MARKER 4						/* 引数で指定する色 */
/*===========================================================================
  param
===========================================================================*/

/*===========================================================================
  コース輝度値クラス [CourseBrightness]
===========================================================================*/
/* 属性 */
typedef struct {
	int blackThreshold;									/* 黒値 */
	int whiteThreshold;									/* 白値 */
	int grayThreshold;									/* 灰色(エッジ)値 */
	int markerThreshold;								/* マーカー検知閾値 */
	int brightness[BRIGHTNESS_NUM];						/* 輝度値を格納 */
/*	int brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM];	移動平均値を格納 */
	int brightnessMeanValue[BRIGHTNESS_MEAN_NUM];				/* 平均値を格納 */
	U8 meanCounter;
} CourseBrightness;

/* 操作 */
void CourseBrightness_init(CourseBrightness* this);				/* 初期化操作 */
void CourseBrightness_finish(CourseBrightness* this);			/* 終了操作 */
int CourseBrightness_updateBrightness(CourseBrightness* this);	/* 輝度値を更新 */
int CourseBrightness_getBrightness(CourseBrightness* this);		/* 輝度値を取得 */
int CourseBrightness_getDiffEdge(CourseBrightness* this);		/* エッジとの差を取得 */
int CourseBrightness_getDiffPast(CourseBrightness* this);		/* 過去との差を取得 */
void CourseBrightness_Calibration(CourseBrightness* this);		/* キャリブレーション */
int CourseBrightness_getThreshold(CourseBrightness* this, U8 thresholdId);		/* 閾値を取得 */
int CourseBrightness_getMeanBrightness(CourseBrightness* this);		/* 平均値を取得 */

#endif

