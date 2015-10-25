#ifndef RUNNINGPOSITIONINFO_H_
#define RUNNINGPOSITIONINFO_H_
/*************************************************************************

  RunningPositionInfo.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "MotorCount.h"

/*===========================================================================
  define
===========================================================================*/
#define TRED          155		/* 車輪の間隔 */
#define WHEEL_SIZE    81.6F		/* タイヤのサイズ */
#define CIRCUMFERENCE 256.224F	/* タイヤの円周 */
#define PI            3.14F		/* 円周率 */

/*===========================================================================
  走行体クラス [RunningMachine]
===========================================================================*/
/* 属性 */
typedef struct {
	MotorCount* motorCount[2];	/* モータ回転角クラスのポインタ */
	float mileage;				/* 走行距離 */
	float direction;			/* 向き */
#if 0
	float coordinateX;			/* x座標 */
	float coordinateY;			/* y座標 */
	float preCoordinateX;		/* 直前のx座標 */
	float preCoordinateY;		/* 直前のy座標 */
#endif
	float startMileage;			/* 戦略開始時の走行距離 */
	float startDirection;		/* 戦略開始時の向き */
} RunningPositionInfo;

/* 操作 */
void RunningPositionInfo_init(
	RunningPositionInfo* this,
	MotorCount* motorCountL,
	MotorCount* motorCountR
);																			/* 初期化操作 */
void RunningPositionInfo_finish(RunningPositionInfo* this); 				/* 終了操作 */
void RunningPositionInfo_presumptionPosition(RunningPositionInfo* this);	/* 自己位置推定 */
S32 RunningPositionInfo_getMileage(RunningPositionInfo* this);				/* 走行距離取得 */
S32 RunningPositionInfo_getStartMileage(RunningPositionInfo* this);			/* 戦略開始時の走行距離を取得 */
S16 RunningPositionInfo_getDirection(RunningPositionInfo* this);			/* 向き取得 */
S16 RunningPositionInfo_getStartDirection(RunningPositionInfo* this);		/* 戦略開始時の向きを取得 */
void RunningPositionInfo_getCoordinate(
	RunningPositionInfo* this,
	S16* coordinateX,
	S16* coordinateY
);																			/* 座標取得 */
void RunningPositionInfo_setStartPositionInfo(RunningPositionInfo* this);	/* 戦略開始時の走行位置情報を設定 */

#endif


