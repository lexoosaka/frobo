#ifndef STEPCAPTURE_H
#define STEPCAPTURE_H
/*************************************************************************

  StepCapture.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include <string.h>
#include "ecrobot_interface.h"
#include "balancer.h"
#include "CommandValue.h"
#include "OperationMethod.h"
#include "JudgeStepCapture.h"
#include "BlindRunning.h"

/*===========================================================================
  define
===========================================================================*/
#define VOLSTAN 90			// 電圧値の基準値
#define FIRSTFORWARD 40		// 階段に入る前のforward
#define FIRSTF1 30			// 戦略移動時のforwardの初期値(GoUpStep1)
#define FIRSTF2 20			// 戦略移動時のforwardの初期値(LevelRun1)
#define FIRSTF3 30			// 戦略移動時のforwardの初期値(GoUpStep2)
#define FIRSTF4 20			// 戦略移動時のforwardの初期値(LevelRun2)
#define FIRSTF5 30			// 戦略移動時のforwardの初期値(LevelRun3)
#define LIMIT1 50			// 上昇するforwardの上限(GoUpStep1)
#define LIMIT2 30			// 上昇するforwardの上限(LevelRun1)
#define LIMIT3 55			// 上昇するforwardの上限(GoUpStep2)
#define LIMIT4 40			// 上昇するforwardの上限(LevelRun2)
#define LIMIT5 50			// 上昇するforwardの上限(LevelRun3)
#define CNT1 30				// forwardの上昇間隔(GoUpStep1)
#define CNT2 1000			// forwardの上昇間隔(LevelRun1)
#define CNT3 30				// forwardの上昇間隔(GoUpStep2)
#define CNT4 40				// forwardの上昇間隔(LevelRun2)
#define CNT5 30				// forwardの上昇間隔(LevelRun3)

/*===========================================================================
  階段攻略クラス [StepCapture]
===========================================================================*/
/* 属性 */
typedef struct
{
	OperationMethod inherit_operationMethod;	// 汎化のため
	JudgeStepCapture* judgeStepCapture; 
	BlindRunning* blindRunning;
	S8 forward;
	U32 time_cnt;			// 時間をカウントする
	S8 flag;				// forwardの初期値を設定したかのフラグ
	S8 shift_check;			// 戦略が移行したかのフラグ
} StepCapture;

/* 操作 */
void StepCapture_init
(
	StepCapture* this,
	CommandValue* commandValue,
	JudgeStepCapture* judgeStepCapture,
	BlindRunning* blindRunning
);
S8 StepCaptureExecution
(
	StepCapture* this,
	S8 stage,
	S16 noParam2
);
void GoUpStep1(StepCapture* this, S8 vol);
void LevelRun1(StepCapture* this);
void GoUpStep2(StepCapture* this, S8 vol);
void LevelRun2(StepCapture* this);
void LevelRun3(StepCapture* this);

#endif

