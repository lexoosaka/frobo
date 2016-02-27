#ifndef STRATEGY_H_
#define STRATEGY_H_
/*************************************************************************

  Strategy.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "RunningPositionInfo.h"
#include "OperationMethod.h"
#include "JudgeMethod.h"
#include "JudgeBrightness.h"
#include "JudgeMileage.h"
#include "JudgeDirection.h"
#include "JudgeBrightness.h"
#include "JudgeMarker.h"
#include "JudgeSeesaw.h"
#include "JudgeSonar.h"
#include "JudgeStepCapture.h"
#include "JudgeTail.h"
#include "LineTrace.h"
#include "BlindRunning.h"
#include "ScreenDetectionRunning.h"
#include "SeesawPass.h"
#include "StepCapture.h"
#include "StrategyParam.h"

/*===========================================================================
  define
===========================================================================*/
/* 戦略実行状態 */
#define RUN 0
#define INTERRUPTION 1

/* 戻り値 */
#define END 0							/* 終了 */
#define CONTINUE 1						/* 続行 */
#define EXECUTION_ANOTHER_STRATEGY 2	/* 特殊戦略実行 */
#define MAX_ID 124						/* 最大ID */
#define MAX_NUM 255						/* 最大値 */

/* 走行方法選択 */
#define TAIL_RUN 0					/* 尻尾走行 */
#define GYRO_RUN 1					/* 倒立制御走行 */


/*===========================================================================
  戦略クラス [Strategy]
===========================================================================*/
/* 属性 */
typedef struct {
	RunningPositionInfo* runningPositionInfo;		/* 走行位置情報クラスのポインタ */
	JudgeBrightness* judgeBrightness;				/* 輝度判定クラスのポインタ */
	JudgeMileage* judgeMileage;						/* 走行距離判定クラスのポインタ */
	JudgeDirection* judgeDirection;					/* 向き判定クラスのポインタ */
	JudgeMarker* judgeMarker;						/* マーカー判定(検地)クラスのポインタ */
	JudgeSeesaw* judgeSeesaw;						/* シーソー判定クラスのポインタ */
	JudgeSonar* judgeSonar;							/* ソナー判定クラスのポインタ */
	JudgeStepCapture* judgeStepCapture;				/* 階段判定クラスのポインタ */
	JudgeTail* judgeTail;							/* 尻尾判定クラスのポインタ */
	LineTrace* lineTrace;							/* ライントレースクラスのポインタ */
	BlindRunning* blindRunning;						/* ブラインド走行クラスのポインタ */
	ScreenDetectionRunning* screenDetectionRunning;	/* 衝立検出走行クラスのポインタ */
	SeesawPass* seesawPass;							/* シーソー走行クラスのポインタ */
	StepCapture* stepCapture;						/* 階段走行クラスのポインタ */
	strategyParam* strategy;						/* 戦略 */
	U8 strategyId;									/* 実行中の戦略番号 */
	U8 totalId;										/* 戦略の総数 */
	U8 state;
	S8* runningFlag;
} Strategy;

/* 操作 */
void Strategy_init(
	Strategy* this,
	RunningPositionInfo* runningPositionInfo,
	strategyParam* strategy,
	S8 totalId,
	JudgeBrightness* judgeBrightness,
	JudgeMileage* judgeMileage,
	JudgeDirection* judgeDirection,
	JudgeMarker* judgeMarker,
	JudgeSeesaw* judgeSeesaw,
	JudgeSonar* judgeSonar,
	JudgeStepCapture* judgeStepCapture,
	JudgeTail* judgeTail,
	LineTrace* lineTrace,
	BlindRunning* blindRunning,
	ScreenDetectionRunning* screenDetectionRunning,
	SeesawPass* seesawPass,
	StepCapture* stepCapture,
	S8* runningFlag
); 													/* 初期化操作 */
void Strategy_finish(Strategy* this);				/* 終了操作 */
U8 Strategy_execution(Strategy* this);				/* 戦略の実行 */
S8 Strategy_judge(Strategy* this);					/* 判定方法の実行 */
S8 Strategy_operation(Strategy* this);				/* 走行方法の実行 */
void Strategy_setStrategyId(Strategy* this, U8 id);	/* 実行する戦略の番号を設定 */
void Strategy_setStrategy(Strategy* this, U8 id, U8 strategyId); /* 戦略を設定(ミステリーサークル専用) */

#endif

