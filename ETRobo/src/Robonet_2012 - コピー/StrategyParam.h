#ifndef STRATEGYPARAM_H_
#define STRATEGYPARAM_H_
/*************************************************************************

  StrategyParam.h

*************************************************************************/

/*===========================================================================
  define
===========================================================================*/
/* 戦略ID */
#define TOTAL_STRATEGY_ID 15		/* 通常戦略の数 */
#define TOTAL_SP_STRATEGY_ID 1		/* ミステリーサークル戦略の数 */
#define MYSTERY_CIRCLE_ID 0			/* 通常戦略のミステリーサークル戦略へ遷移する戦略の番号 */
#define PATTERN_1 125				/* ミステリーサークル戦略の通過パターン */
#define PATTERN_2 125				/* ミステリーサークル戦略の通過パターン */
#define PATTERN_3 125				/* ミステリーサークル戦略の通過パターン */
#define PATTERN_4 125				/* ミステリーサークル戦略の通過パターン */

/* 操作の数 */
#define TOTAL_JUDGE_METHOD 8
#define TOTAL_OPERATION_METHOD 5

/* 判定方法ID */
#define JUDGE_MILEAGE 0
#define JUDGE_DIRECTION 1
#define JUDGE_BRIGHTNESS 2
#define JUDGE_SEESAW 3
#define JUDGE_STEPCAPTURE 4
#define JUDGE_TAIL 5
#define JUDGE_SONAR 6
#define JUDGE_MARKER 7


/* 走行方法ID */
#define LINE_TRACE 0
#define BLIND_RUNNING 1
#define SCREEN_DETECTION_RUNNING 2
#define STEP_CAPTURE 3
#define SEESAW_PASS 4
#define TAIL_BLIND 5

/*===========================================================================
  type
===========================================================================*/
/* 戦略構造体 */
typedef struct {
	U8 judgeId;  /* 判定関数ID */
	S16 judgeParam1; /* 判定関数引数1 */
	S16 judgeParam2; /* 判定関数引数2 */
	U8 operationId;    /* 操作関数ID */
	S8 operationParam1;  /* 操作関数引数1 */
	S16 operationParam2;  /* 操作関数引数2 */
} strategyParam;


#endif
