/*************************************************************************

  JudgeStepCapture.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "JudgeStepCapture.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : JudgeStepCapture_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void JudgeStepCapture_init
(
	JudgeStepCapture* this,
	AngularVelocity* angularVelocity,
	MotorCount* motorCountL,
	MotorCount* motorCountR
)
{
	this->angularVelocity = angularVelocity;
	this->motorCount[0] = motorCountL;
	this->motorCount[1] = motorCountR;
	this -> time_cnt = 0;
	this -> stab_cnt = 0;
}

/*===========================================================================
  FUNCTION    : JudgeStepCapture_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void JudgeStepCapture_finish(JudgeStepCapture* this)
{
	
}

/*===========================================================================
  FUNCTION    : JudgeStepCapture_BalanceCheckC
  PARAMETERS  : 
  RETURN      : S8
  DESCRIPTION : バランスの崩れを判定する
  MEMO        : 
===========================================================================*/
S8 JudgeStepCapture_BalanceCheckC(JudgeStepCapture* this)
{
	U16 meanValue;
	
	meanValue = AngularVelocity_getMeanAngularVelocity(this->angularVelocity);	// ジャイロ値を取得
	
	// ジャイロ値が基準値以上、もしくは基準値以下かを見る //
	if(((meanValue > this->angularVelocity->offsetValue + STEP1MEANVALUE) || (meanValue < this->angularVelocity->offsetValue - STEP1MEANVALUE)))
	{
		return 1;
	}
	
	return 0;
}

/*===========================================================================
  FUNCTION    : JudgeStepCapture_BalanceCheckS1
  PARAMETERS  : 
  RETURN      : S8
  DESCRIPTION : バランスの安定を判定する（判断早め）
  MEMO        : 
===========================================================================*/
S8 JudgeStepCapture_BalanceCheckS1(JudgeStepCapture* this)
{
	U16 meanValue;
	
	meanValue = AngularVelocity_getMeanAngularVelocity(this->angularVelocity);	// ジャイロ値を取得
	
	// ジャイロ値が基準値内かを見る //
	if(((meanValue >= this->angularVelocity->offsetValue - STEPJUDGE2) && (meanValue <= this->angularVelocity->offsetValue - STEPJUDGE1)))
	{
		this -> stab_cnt++;							// 基準値内にいた時間をカウント
		if(this -> stab_cnt > STEP1JUDGECNT)		// 一定時間基準値内にいた
		{
			this->stab_cnt = 0;
			return 1;
		}
	}
	else
	{
		this -> stab_cnt = 0;						// stab_cntをリセット
	}
	
	return 0;
}

/*===========================================================================
  FUNCTION    : JudgeStepCapture_BalanceCheckS2
  PARAMETERS  : 
  RETURN      : S8
  DESCRIPTION : バランスの安定を判定する（判断遅め）
  MEMO        : 
===========================================================================*/
S8 JudgeStepCapture_BalanceCheckS2(JudgeStepCapture* this)
{
	U16 meanValue;
	
	meanValue = AngularVelocity_getMeanAngularVelocity(this->angularVelocity);	// ジャイロ値を取得
	
	// ジャイロ値が基準値内かを見る //
	if(((meanValue >= this->angularVelocity->offsetValue - STEPJUDGE2) && (meanValue <= this->angularVelocity->offsetValue - STEPJUDGE1)))
	{
		this -> stab_cnt++;							// 基準値内にいた時間をカウント
		if(this -> stab_cnt > STEP2JUDGECNT)		// 一定時間基準値内にいた
		{
			this->stab_cnt = 0;
			return 1;
		}
	}
	else
	{
		this -> stab_cnt = 0;						// stab_cntをリセット
	}
	
	return 0;
}

/*===========================================================================
  FUNCTION    : JudgeStepCapture_TimeCount
  PARAMETERS  : 
  RETURN      : S8
  DESCRIPTION : 時間をカウントする
  MEMO        : 
===========================================================================*/
S8 JudgeStepCapture_TimeCount(JudgeStepCapture* this, S8 flag)
{
	this->time_cnt++;
	
	// 一定時間過ぎる、もしくはflagが既に1であるか //
	if(this->time_cnt > TIMEJUDGE || flag == 1)
	{
		return 1;
	}
	
	return 0;
}

/*===========================================================================
  FUNCTION    : JudgeStepCapture_execution
  PARAMETERS  : 
  RETURN      : S8
  DESCRIPTION : 戦略の意向を判断する
  MEMO        : 
===========================================================================*/
S8 JudgeStepCapture_execution
(
	JudgeStepCapture* this,
	S16 prm1,
	S16 prm2
)
{
	S8 flag = 0;											// 戦略移行のフラグ
	
	if(prm1 == 0)											// バランスの崩れを判断する
	{
		flag = JudgeStepCapture_BalanceCheckC(this);
	}
	else if(prm1 == 1)										// バランスの安定を判定する(判早め)
	{
		flag = JudgeStepCapture_BalanceCheckS1(this);
	}
	else if(prm1 == 2)										// バランスの安定を判定する(判遅め)
	{
		flag = JudgeStepCapture_BalanceCheckS2(this);
	}
	
	if(prm2 == 1)											// 時間をカウントする
	{
		flag = JudgeStepCapture_TimeCount(this, flag);
	}
	
	return flag;
}

