#ifndef MOTORCOUNT_H_
#define MOTORCOUNT_H_
/*************************************************************************

  MotorCount.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"

/*===========================================================================
  define
===========================================================================*/
#define MOTOR_COUNT_NUM 20

/*===========================================================================
  モータ回転角クラス [MotorCount]
===========================================================================*/
/* 属性 */
typedef struct {
	U32 port;						/* モータが接続されているポート */
	int motorCount[MOTOR_COUNT_NUM];	/* モータ回転角を格納する配列 */
	int startMotorCount;			/* 戦略開始時のモータ回転角 */
} MotorCount;

/* 操作 */
void MotorCount_init(MotorCount* this, U32 port);				/* 初期化操作 */
void MotorCount_finish(MotorCount* this);						/* 終了操作 */
void MotorCount_updateMotorCount(MotorCount* this);				/* 回転角を更新 */
int MotorCount_getMotorCount(MotorCount* this);					/* 回転角を取得 */
int MotorCount_getPastMotorCount(MotorCount* this, U8 countId);	/* 過去の回転角を取得 */
void MotorCount_setStartMotorCount(MotorCount* this);			/* 戦略開始時のモータ回転角を設定 */
int MotorCount_getStartMotorCount(MotorCount* this);			/* 戦略開始時のモータ回転角を取得 */

#endif

