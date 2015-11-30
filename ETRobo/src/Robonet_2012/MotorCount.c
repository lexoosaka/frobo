/*************************************************************************

  MotorCount.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "MotorCount.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : MotorCount_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void MotorCount_init(MotorCount* this, U32 port)
{
	int count;
	
	/* 初期化 */
	for(count = 0; count < MOTOR_COUNT_NUM; count++)
	{
		this->motorCount[count] = 0;
	}
	this->port = port;
	this->startMotorCount = 0;
}

/*===========================================================================
  FUNCTION    : MotorCount_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void MotorCount_finish(MotorCount* this)
{
	
}

/*===========================================================================
  FUNCTION    : MotorCount_updateMotorCount
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : モータ回転角を更新
  MEMO        : 
===========================================================================*/
void MotorCount_updateMotorCount(MotorCount* this)
{
	int count;
	
	/* 1つずつ前にずらして最新の値を最後尾に格納 */
	for(count = 0; count < (MOTOR_COUNT_NUM - 1); count++)
	{
		this->motorCount[count] = this->motorCount[count + 1];
	}
	this->motorCount[MOTOR_COUNT_NUM - 1] = nxt_motor_get_count(this->port);
}

/*===========================================================================
  FUNCTION    : MotorCount_getMotorCount
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : モータ回転角を取得
  MEMO        : 
===========================================================================*/
int MotorCount_getMotorCount(MotorCount* this)
{
	return (this->motorCount[MOTOR_COUNT_NUM - 1]);
}

/*===========================================================================
  FUNCTION    : MotorCount_getPastMotorCount
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 過去のモータ回転角を取得
  MEMO        : 
===========================================================================*/
int MotorCount_getPastMotorCount(MotorCount* this, U8 countId)
{
	if((MOTOR_COUNT_NUM - 1) < countId)
	{
		countId = (MOTOR_COUNT_NUM - 1);
	}
	
	return (this->motorCount[MOTOR_COUNT_NUM - 1 - countId]);
}

/*===========================================================================
  FUNCTION    : MotorCount_setStartMotorCount
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 戦略開始時の回転角を設定
  MEMO        : 
===========================================================================*/
void MotorCount_setStartMotorCount(MotorCount* this)
{
	this->startMotorCount = (this->motorCount[MOTOR_COUNT_NUM - 1]);
}

/*===========================================================================
  FUNCTION    : MotorCount_getStartMotorCount
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 戦略開始時の回転角を取得
  MEMO        : 
===========================================================================*/
int MotorCount_getStartMotorCount(MotorCount* this)
{
	return (this->startMotorCount);
}

