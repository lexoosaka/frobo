/*************************************************************************

  RunningPositionInfo.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
/*#include <math.h> */
#include "RunningPositionInfo.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : RunningPositionInfo_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void RunningPositionInfo_init(
	RunningPositionInfo* this,
	MotorCount* motorCountL,
	MotorCount* motorCountR
)
{
	this->motorCount[0] = motorCountL;
	this->motorCount[1] = motorCountR;
	this->mileage = 0;
	this->direction = PI;
#if 0
	this->coordinateX = 0;
	this->coordinateY = 0;
	this->preCoordinateX = 0;
	this->preCoordinateY = 0;
#endif
	this->startMileage = 0;
	this->startDirection = this->direction;
	
}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void RunningPositionInfo_finish(RunningPositionInfo* this)
{

}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_presumptionPosition
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 自己位置推定
  MEMO        : 
===========================================================================*/
void RunningPositionInfo_presumptionPosition(RunningPositionInfo* this)
{
	int diffMotorCountL;
	int diffMotorCountR;
	float diffDirection;          /* 2ms前から現在までに変動した角度 */
	float move;                   /* 2ms前から現在までの移動距離 */
	
	MotorCount_updateMotorCount(this->motorCount[0]); /* 回転角取得 */
	MotorCount_updateMotorCount(this->motorCount[1]); /* 回転角取得 */
	diffMotorCountL = (MotorCount_getMotorCount(this->motorCount[0])) - (MotorCount_getPastMotorCount(this->motorCount[0], 1));
	diffMotorCountR = (MotorCount_getMotorCount(this->motorCount[1])) - (MotorCount_getPastMotorCount(this->motorCount[1], 1));
	diffDirection = ((diffMotorCountR * CIRCUMFERENCE / 360) - (diffMotorCountL * CIRCUMFERENCE / 360)) / TRED; /* 2ms前から現在までに変動した角度を計算 */
	this->direction += diffDirection; /* 現在の走行体の角度を計算 */
#if 0
	this->preCoordinateX = this->coordinateX; /* 2ms前のx座標を更新 */
	this->preCoordinateY = this->coordinateY; /* 2ms前のy座標を更新 */
#endif
	move = (((float)diffMotorCountL + diffMotorCountR) / 2) * CIRCUMFERENCE / 360; /* 2ms前から現在までの移動距離 */
	this->mileage += move; /* 走行開始時から現在までの移動距離を計算 */
#if 0
	this->coordinateX = this->preCoordinateX + move * ((float)cos((double)this->direction + (diffDirection / 2))); /* 現在位置のx座標を計算 */
	this->coordinateY = this->preCoordinateY + move * ((float)sin((double)this->direction + (diffDirection / 2))); /* 現在位置のy座標を計算 */
#endif
}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_getMileage
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 走行距離を取得する
  MEMO        : 
===========================================================================*/
S32 RunningPositionInfo_getMileage(RunningPositionInfo* this)
{
	return (S32)this->mileage;
}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_getStartMileage
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 戦略開始時の走行距離を取得する
  MEMO        : 
===========================================================================*/
S32 RunningPositionInfo_getStartMileage(RunningPositionInfo* this)
{
	return (S32)this->startMileage;
}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_getDirection
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 走行向きを取得する
  MEMO        : 
===========================================================================*/
S16 RunningPositionInfo_getDirection(RunningPositionInfo* this)
{
	float direction = this->direction;
	
	direction = direction / PI * 180;
/*	if(direction < 0)
	{
		direction *= -1;
	}
	direction = (S16)direction % 360;
*/	
	return (S16)direction;
}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_getStartDirection
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 戦略開始時の走行向きを取得する
  MEMO        : 
===========================================================================*/
S16 RunningPositionInfo_getStartDirection(RunningPositionInfo* this)
{
	float direction = this->startDirection;
	
	direction = direction / PI * 180;
/*	if(direction < 0)
	{
		direction *= -1;
	}
	direction = (S16)direction % 360;
*/	
	return (S16)direction;
}

#if 0
/*===========================================================================
  FUNCTION    : RunningPositionInfo_getCoordinate
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 座標を取得する
  MEMO        : 
===========================================================================*/
void RunningPositionInfo_getCoordinate(RunningPositionInfo* this, S16* coordinateX, S16* coordinateY)
{
	*coordinateX = (S16)this->coordinateX;
	*coordinateY = (S16)this->coordinateY;
}
#endif

/*===========================================================================
  FUNCTION    : RunningPositionInfo_setStartPositionInfo
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 走行距離を取得する
  MEMO        : 
===========================================================================*/
void RunningPositionInfo_setStartPositionInfo(RunningPositionInfo* this)
{
	this->startMileage = this->mileage;
	this->startDirection = this->direction;
	
	MotorCount_setStartMotorCount(this->motorCount[1]);
	MotorCount_setStartMotorCount(this->motorCount[0]);
}

