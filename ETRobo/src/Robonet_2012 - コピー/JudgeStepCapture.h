#ifndef JUDGESTEPCAPTURE_H_
#define JUDGESTEPCAPTURE_H_
/*************************************************************************

  JudgeStepCapturet.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include <string.h>
#include "ecrobot_interface.h"
#include "balancer.h"
#include "ecrobot_interface.h"
#include "RunningPositionInfo.h"
#include "OperationMethod.h"
#include "AngularVelocity.h"
#include "motorCount.h"

/*===========================================================================
  define
===========================================================================*/
#define STEP1MEANVALUE 22				// 一段目に差し掛かったかを判断するmeanValueの○以上の値
#define STEPJUDGE1 1					// 安定したかを判断するmeanValueの○以下の値
#define STEPJUDGE2 3					// 安定したかを判断するmeanValueの○以上の値
#define STEP1JUDGECNT 19				// 一段目を上って安定したかを判断するのに必要なカウント数
#define STEP2JUDGECNT 39				// 二段目を上って安定したかを判断するのに必要なカウント数
#define TIMEJUDGE 4000					// 階段に突入してから、階段を通過したことにするまでの時間

/*===========================================================================
  向き判定クラス
===========================================================================*/
/* 属性 */
typedef struct 
{
	AngularVelocity* angularVelocity;
	MotorCount* motorCount[2];
	U32 time_cnt;						// 難所に突入してからの時間カウント
	U32 stab_cnt;						// 安定した走行をしているかを見る変数
} JudgeStepCapture;

/* 操作 */
void JudgeStepCapture_init
(
	JudgeStepCapture* this,
	AngularVelocity* angularVelocity,
	MotorCount* motorCountL,
	MotorCount* motorCountR
);
void JudgeStepCapture_finish(JudgeStepCapture* this);
S8 JudgeStepCapture_BalanceCheckC(JudgeStepCapture* this);
S8 JudgeStepCapture_BalanceCheckS1(JudgeStepCapture* this);
S8 JudgeStepCapture_BalanceCheckS2(JudgeStepCapture* this);
S8 JudgeStepCapture_TimeCount(JudgeStepCapture* this, S8 flag);
S8 JudgeStepCapture_execution(
	JudgeStepCapture* this,
	S16 prm1,
	S16 prm2
);

#endif

