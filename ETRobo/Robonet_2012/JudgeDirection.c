/*************************************************************************

  JudgeDirection.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "JudgeDirection.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : JudgeDirection_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void JudgeDirection_init(JudgeDirection* this, RunningPositionInfo* runningPositionInfo)
{
	this->runningPositionInfo = runningPositionInfo;
	this->diffCount = -125;
}

/*===========================================================================
  FUNCTION    : JudgeDirection_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void JudgeDirection_finish(JudgeDirection* this)
{
	
}

/*===========================================================================
  FUNCTION    : JudgeDirection_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 向きを判定する
  MEMO        : 
===========================================================================*/
S8 JudgeDirection_execution(
	JudgeDirection* this,
	S16 targetValue,
	S16 mode
)
{
	S16 direction;
	S32 mileage;
	S8 diff;
	
	/* 現在の走行体の向きを取得 */
	direction = RunningPositionInfo_getDirection(this->runningPositionInfo);
	
	/* 直線に入ったか判定 */
	if(mode == DIRECTION_STABILITY)
	{
#if 0
		/* 角度の揺れ幅の測定を開始していない(開始していない場合、揺れ幅が大きくなり過ぎてリセットした場合は"this->diffCount"に"-125"が入っている)*/
		if(this->diffCount == -125)
		{
			diff = 0;
		}
		/* 角度の揺れ幅の測定を開始している */
		else
		{
			diff = this->pastDirection - direction; /* 直前からの揺れ幅を測定 */
		}
#endif
		diff = this->pastDirection - direction; /* 直前からの揺れ幅を測定 */
		this->pastDirection = direction; /* 過去の角度を更新 */
		
		/* 直前の揺れ幅を判定し、揺れ幅が許容範囲内 */
		if(((-1 * DIRECTION_RANGE) < diff) && (diff < DIRECTION_RANGE))
		{
			/* 今回から揺れ幅の測定を開始し始めた */
			if(this->diffCount == -125)
			{
				this->stabilityMileage = RunningPositionInfo_getMileage(this->runningPositionInfo); /* 開始距離を格納 */
				this->diffCount = diff; /* 揺れ幅を格納 */
			}
			/* すでに開始している */
			else
			{
				mileage = RunningPositionInfo_getMileage(this->runningPositionInfo); /* 現在距離取得 */
				this->diffCount += diff; /* 揺れ幅を加算 */
				
				/* 加算した揺れ幅が許容範囲内 */
				if(((-1 * DIRECTION_RANGE) < (this->diffCount)) && ((this->diffCount) < DIRECTION_RANGE))
				{
					/* 揺れ幅を測定し始めて指定距離走行した(この判定モードでは"targetValue"で走行距離を指定する) */
					if(targetValue < (mileage - (this->stabilityMileage)))
					{
						this->diffCount = -125; /* 揺れ幅判定値を初期化 */
						return 1; /* 判定が満たされたことを通知 */
					}
				}
				/* 許容範囲を越えた */
				else
				{
					this->diffCount = -125; /* 揺れ幅判定値を初期化し揺れ幅の測定をやり直す */
				}
			}
		}
		/* 許容範囲を越えた */
		else
		{
			this->diffCount = -125; /* 揺れ幅判定値を初期化し揺れ幅の測定をやり直す */
		}
	}
	/* 他の判定モード(戦略開始から現在までの走行体の向きを判定、または走行開始からの絶対角度を判定) */
	else
	{
		/* 戦略開始から現在までの走行体の向きを判定する場合 */
		if(mode == DIFF)
		{
			/* 実行中の戦略開始時から現在までに変化した向きを取得 */
			direction -= RunningPositionInfo_getStartDirection(this->runningPositionInfo);
		}
		
		/* 比較して判定 */
		if(targetValue < 0)
		{
			if(direction < targetValue)
			{
				return 1;
			}
		}
		else
		{
			if(targetValue < direction)
			{
				return 1;
			}
		}
	}
	
	return 0;
}

