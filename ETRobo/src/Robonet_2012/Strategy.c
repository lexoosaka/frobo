/*************************************************************************

  Strategy.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "Strategy.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : Strategy_init
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : コンストラクタ
  MEMO        :
===========================================================================*/
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
)
{
	/* 初期化 */
	this->strategy = strategy;
	this->totalId = totalId;
	this->strategyId = 0;
	this->state = RUN;
	this->runningPositionInfo = runningPositionInfo;
	this->judgeBrightness = judgeBrightness;
	this->judgeMileage = judgeMileage;
	this->judgeMarker = judgeMarker;
	this->judgeDirection = judgeDirection;
	this->judgeSeesaw = judgeSeesaw;
	this->judgeSonar = judgeSonar;
	this->judgeStepCapture = judgeStepCapture;
	this->judgeTail = judgeTail;
	this->lineTrace = lineTrace;
	this->blindRunning = blindRunning;
	this->screenDetectionRunning = screenDetectionRunning;
	this->seesawPass = seesawPass;
	this->stepCapture = stepCapture;
	this->runningFlag = runningFlag;
}

/*===========================================================================
  FUNCTION    : Strategy_finish
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : デストラクタ
  MEMO        :
===========================================================================*/
void Strategy_finish(Strategy* this)
{

}

/*===========================================================================
  FUNCTION    : Strategy_execution
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : 戦略の実行
  MEMO        :
===========================================================================*/
U8 Strategy_execution(Strategy* this)
{
	/* 判定方法IDが設定されている判定方法の数未満 */
	if((this->strategy[this->strategyId].judgeId) < (TOTAL_JUDGE_METHOD))
	{
		/* 戦略を実行中 */
		if(this->state == RUN)
		{
			/* 判定方法を実行した結果、戦略を遷移する場合 */
			if(1 == Strategy_judge(this))
			{
				/* 戦略を遷移した時に実行戦略IDが戦略の総数を超えない場合 */
				if((this->strategyId + 1) < this->totalId)
				{
					/* 戦略を遷移するため実行戦略IDを設定 */
					Strategy_setStrategyId(this, (this->strategyId + 1));

					/* 遷移した戦略の判定方法IDが、MAX_IDより大きくMAX_NUMより小さい場合、他戦略へ遷移する */
					if((MAX_ID < (this->strategy[this->strategyId].judgeId)) && ((this->strategy[this->strategyId].judgeId) < MAX_NUM))
					{
						/* 他戦略へ遷移するため、判定方法IDを返す */
						return (this->strategy[this->strategyId].judgeId);
					}

					/* 判定方法IDが大きすぎる場合 */
					else if(MAX_NUM <= (this->strategy[this->strategyId].judgeId))
					{
						return (S8)0;
					}
				}

				/* 総数を超えてしまう場合 */
				else
				{
					return (S8)0;
				}
			}
		}

		/* 走行方法IDが設定されている走行方法の数未満 */
		if(this->strategy[this->strategyId].operationId < TOTAL_OPERATION_METHOD)
		{
			Strategy_operation(this);
		}
	}

	/* 判定方法IDが、MAX_IDより大きくMAX_NUMより小さい場合、他戦略へ遷移する */
	else if((MAX_ID < (this->strategy[this->strategyId].judgeId)) && ((this->strategy[this->strategyId].judgeId) < MAX_NUM))
	{
		return (U8)EXECUTION_ANOTHER_STRATEGY;
	}

	/* 判定方法IDが大きすぎる場合 */
	else
	{
		return (U8)0;
	}

	return (U8)1;
}

/*===========================================================================
  FUNCTION    : Strategy_judge
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : 判定方法の実行
  MEMO        :
===========================================================================*/
S8 Strategy_judge(Strategy* this)
{
	S8 rtn = 0;

	switch(this->strategy[this->strategyId].judgeId)
	{
	case JUDGE_MILEAGE:
		rtn = (JudgeMileage_execution(this->judgeMileage, this->strategy[this->strategyId].judgeParam1, this->strategy[this->strategyId].judgeParam2));
		break;
	case JUDGE_DIRECTION:
		rtn = (JudgeDirection_execution(this->judgeDirection, this->strategy[this->strategyId].judgeParam1, this->strategy[this->strategyId].judgeParam2));
		break;
	case JUDGE_BRIGHTNESS:
		rtn = (JudgeBrightness_execution(this->judgeBrightness, this->strategy[this->strategyId].judgeParam1, this->strategy[this->strategyId].judgeParam2));
		break;
	case JUDGE_SEESAW:
		rtn = (JudgeSeesaw_execution(this -> judgeSeesaw,this->strategy[this->strategyId].judgeParam1, this->strategy[this->strategyId].judgeParam2));
		break;
	case JUDGE_STEPCAPTURE:
		rtn = (JudgeStepCapture_execution(this -> judgeStepCapture, this->strategy[this->strategyId].judgeParam1, this->strategy[this->strategyId].judgeParam2));
		break;
	case JUDGE_TAIL:
		rtn = (JudgeTail_execution(this -> judgeTail, this->strategy[this->strategyId].judgeParam1, this->strategy[this->strategyId].judgeParam2));
		break;
	case JUDGE_SONAR:
		rtn = (JudgeSonar_execution(this -> judgeSonar, this->strategy[this->strategyId].judgeParam1, this->strategy[this->strategyId].judgeParam2));
		break;
	case JUDGE_MARKER:
		rtn = (JudgeMarker_execution(this -> judgeMarker, this->strategy[this->strategyId].judgeParam1, this->strategy[this->strategyId].judgeParam2));
		break;
	default:
		break;
	}

	return rtn;

}

/*===========================================================================
  FUNCTION    : Strategy_operation
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : 走行方法の実行
  MEMO        :
===========================================================================*/
S8 Strategy_operation(Strategy* this)
{
	S8 rtn = 0;
	U8 pattern;

	/* デフォルトは倒立走行、必要に応じてswitch文内で上書き */
	S8 tmp = GYRO_RUN;
	this -> runningFlag = &tmp;

	switch(this->strategy[this->strategyId].operationId)
	{
	case LINE_TRACE:
		if((this->strategy[this->strategyId].operationParam2 == LEFT_SMALL) || (this->strategy[this->strategyId].operationParam2 == RIGHT_SMALL) || (this->strategy[this->strategyId].operationParam2 == LEFT_BIG) || (this->strategy[this->strategyId].operationParam2 == RIGHT_BIG))
		{
			rtn = (LineTrace_execution(this->lineTrace, this->strategy[this->strategyId].operationParam1, this->strategy[this->strategyId].operationParam2));
		}
		else
		{
			if((1 == JudgeBrightness_execution(this->judgeBrightness, 3, COURSEOUT)) || (this->state == INTERRUPTION))
			{
				if(1 == (JudgeBrightness_execution(this->judgeBrightness, 3, STABILITY)))
				{
					this->state = RUN;
				}
				else
				{
					this->state = INTERRUPTION;
				}

				if(1 == (JudgeBrightness_execution(this->judgeBrightness, WHITE, 1)))
				{
/*				pattern = (this->strategy[this->strategyId].operationParam2) % 2;*/
/*				pattern = ((pattern == 0) ? -20 : 20);*/
/*				rtn = (BlindRunning_execution(this->blindRunning, -10, (S16)pattern));*/
					rtn = (BlindRunning_execution(this->blindRunning, -10, 0));
				}
				else
				{
					pattern = (this->strategy[this->strategyId].operationParam2) % 2;
					rtn = (LineTrace_execution(this->lineTrace, 0, (S16)pattern));
				}
			}
			else
			{
				this->state = RUN;
				rtn = (LineTrace_execution(this->lineTrace, this->strategy[this->strategyId].operationParam1, this->strategy[this->strategyId].operationParam2));
			}
		}
		break;
	case BLIND_RUNNING:
		rtn = (BlindRunning_execution(this->blindRunning, this->strategy[this->strategyId].operationParam1, this->strategy[this->strategyId].operationParam2));
		break;
	case SCREEN_DETECTION_RUNNING:
		rtn = (ScreenDetectionRunning_execution(this->screenDetectionRunning, this->strategy[this->strategyId].operationParam1, this->strategy[this->strategyId].operationParam2));
		if(1 < rtn)
		{
			switch(rtn)
			{
			case 2:
				pattern = PATTERN_2;
				break;
			case 3:
				pattern = PATTERN_3;
				break;
			case 4:
				pattern = PATTERN_4;
				break;
			default:
				pattern = PATTERN_1;
				break;
			}
			Strategy_setStrategy(this, pattern, MYSTERY_CIRCLE_ID);
			rtn = 1;
		}
		break;
	case STEP_CAPTURE:
		rtn = (StepCaptureExecution(this->stepCapture, this->strategy[this->strategyId].operationParam1, this->strategy[this->strategyId].operationParam2));
		break;
	case SEESAW_PASS:
		rtn = (SeesawPass_execution(this->seesawPass, this->strategy[this->strategyId].operationParam1, this->strategy[this->strategyId].operationParam2));
		break;
	case TAIL_BLIND:
		rtn = (BlindRunning_execution(this->blindRunning, this->strategy[this->strategyId].operationParam1, this->strategy[this->strategyId].operationParam2));
		this -> runningFlag = TAIL_RUN;
		break;
	default:
		break;
	}


	return rtn;
}


/*===========================================================================
  FUNCTION    : Strategy_setStrategyId
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : 実行戦略IDの設定
  MEMO        :
===========================================================================*/
void Strategy_setStrategyId(Strategy* this, U8 strategyId)
{
	this->strategyId = strategyId;
	RunningPositionInfo_setStartPositionInfo(this->runningPositionInfo);
}

/*===========================================================================
  FUNCTION    : Strategy_setStrategy
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : 戦略を設定
  MEMO        :
===========================================================================*/
void Strategy_setStrategy(Strategy* this, U8 id, U8 strategyId)
{
	this->strategy[strategyId].judgeId = id;
}

