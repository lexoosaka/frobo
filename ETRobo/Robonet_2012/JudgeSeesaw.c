/*************************************************************************

  JudgeSeesaw.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "JudgeSeesaw.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : JudgeSeesaw_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void JudgeSeesaw_init(
	JudgeSeesaw* this, 
	MotorCount* motorCountL, 
	MotorCount* motorCountR, 
	Pwm* pwmL, 
	Pwm* pwmR, 
	JudgeDirection* judgeDirection,
	JudgeMileage* judgeMileage
)
{
	this -> motorCountL = motorCountL;
	this -> motorCountR = motorCountR;
	this -> pwmL = pwmL;
	this -> pwmR = pwmR;
	this -> judgeDirection = judgeDirection;
	this -> judgeMileage = judgeMileage;
	this -> seesawTime = 1;

	return ;
	
}

/*===========================================================================
  FUNCTION    : JudgeSeesaw_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void JudgeSeesaw_finish(JudgeSeesaw* this)
{
	
}

/*===========================================================================
  FUNCTION    : JudgeSeesaw_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : シーソー上のイベントを管理
  MEMO        : 
===========================================================================*/
S8 JudgeSeesaw_execution(JudgeSeesaw* this, S16 judgeParam, S16 seesawCtrlTime)
{
	if(seesawCtrlTime == 0)		/* シーソーを見つける前*/
	{
		if(/* 最近モータが逆回転をしたらシーソーに当たったと判定 */
			this -> motorCountR->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountR->motorCount[0] <= SEESAW_FIND_PARAM ||
			this -> motorCountL->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountL->motorCount[0] <= SEESAW_FIND_PARAM
		)
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 1)		//シーソーを見つけたので上るS
	{
		if(/* シーソー開始位置から40mm以上先に進んだらシーソーに乗ったと判定 */
			JudgeMileage_execution(this -> judgeMileage, SEESAW_RIDE_PARAM, 0)
		)
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 2 && judgeParam == JUDGESEESAWSTOP)		//シーソー上旋回地点まで移動B
	{
		if(													/* 旋回開始地点に到達した。 */
			JudgeMileage_execution(this -> judgeMileage, SEESAW_BALANCE_POINT, 0)
		)
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 2 && judgeParam == JUDGESEESAWPASS)
	{
		if(													/* シーソーを通過した(もう降りているはずの位置まで移動した)。 */
			JudgeMileage_execution(this -> judgeMileage, (SEESAW_PASS_PARAM/2), 0)
		)
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 3 && judgeParam == JUDGESEESAWSTOP)		//旋回開始B
	{
		if(
			JudgeDirection_execution(this -> judgeDirection, 20, DIFF)
		)/* 旋回完了 */
		{
			return 1;
		}
	}
		else if(seesawCtrlTime == 3 && judgeParam == JUDGESEESAWPASS)
	{
		if(													/* シーソーを通過した(もう降りているはずの位置まで移動した)。 */
			JudgeMileage_execution(this -> judgeMileage, (SEESAW_PASS_PARAM/2), 0)
		)
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 4)		//旋回開始B
	{
		if(
			JudgeDirection_execution(this -> judgeDirection, 20, DIFF)
		)/* 旋回完了 */
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 5)		//旋回開始B
	{
		if(
			JudgeDirection_execution(this -> judgeDirection, 10, 0)
		)/* 旋回完了 */
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 6)
	{
		if(JudgeDirection_execution(this -> judgeDirection, 41, DIFF))
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 7)		//少し下がるB
	{
		if(JudgeMileage_execution(this -> judgeMileage, -205, 0))
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 8)		//少し下がるB
	{
		if(JudgeMileage_execution(this -> judgeMileage, 1, 0))
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 9)		//少し回転するB
	{
		if(JudgeDirection_execution(this -> judgeDirection, -20, DIFF))
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 10)		//静止を試みるS
	{
		this -> seesawTime = this -> seesawTime + 1;
		if(SEESAW_STOP_TIME < this -> seesawTime)					/* シーソー上で停止を試みる時間が終わった。 */
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 11)		//静止が終わり旋回を開始B
	{
		if(JudgeDirection_execution(this -> judgeDirection, -72, DIFF))/*旋回完了*/
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 12)		//シーソーから降りるS
	{
		if(/* モータがよく回ったらシーソーから降りたと判定 */
			this -> motorCountR->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountR->motorCount[0] >= SEESAW_LEAVE_PARAM &&
			this -> motorCountL->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountL->motorCount[0] >= SEESAW_LEAVE_PARAM
		)
		{
			return 1;
		}
	}
	else{
		;/* ここにはこない */
	}
	return 0;
}

