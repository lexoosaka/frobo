/*************************************************************************

  SeesawPass.c
  
  プログラム概要
  ETロボコン2010年度の難所、シーソーを攻略すためのプログラム。
  
*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "SeesawPass.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : SeesawPass_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void SeesawPass_init(SeesawPass* this, MotorCount* motorCountL, MotorCount* motorCountR, Pwm* pwmL, Pwm* pwmR, BlindRunning* blindRunning)
{
	this -> motorCountL = motorCountL;
	this -> motorCountR = motorCountR;
	this -> pwmL = pwmL;
	this -> pwmR = pwmR;
	this -> blindRunning = blindRunning;
	this -> seesawTime = 1;
	this -> past_param = 0.025;
	
	return ;
}

/*===========================================================================
  FUNCTION    : SeesawPass_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void SeesawPass_finish(SeesawPass* this)
{
	return ;
}

/*===========================================================================
  FUNCTION    : SeesawPass_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : シーソー上のイベントを管理
  MEMO        : 
===========================================================================*/
S8 SeesawPass_execution(SeesawPass* this, S16 judgeParam, S16 seesawCtrlTime)
{
	S8 rtn = 0;
	S8 forward = 0;
	S16 turn = 0;
	S16 nowCountL; /* ブラインド走行開始後からの左モータの回転角 */
	S16 nowCountR; /* ブラインド走行開始後からの右モータの回転角 */

	if(seesawCtrlTime == 0)		/* シーソーを見つける前*/
	{
		rtn = (BlindRunning_execution((this -> blindRunning), SEESAW_START_PARAM, 0));
	}
	else if(seesawCtrlTime == 1)		//シーソーを見つけたので上るS
	{
		this -> seesawTime = this -> seesawTime + 1;
		forward = SEESAW_START_PARAM + (this -> seesawTime / SEESAW_INCR_PARAM);		//徐々に前進命令値を上昇させる
//		forward = 40;
//		rtn = (BlindRunning_execution(this -> blindRunning, forward, 0));
		
		/* 段差を利用してシーソーに対して真正面から入れるようにする。*/
		nowCountL = MotorCount_getMotorCount(this -> motorCountL) - MotorCount_getPastMotorCount(this -> motorCountL, 1);
		nowCountR = MotorCount_getMotorCount(this -> motorCountR) - MotorCount_getPastMotorCount(this -> motorCountR, 1);
		
		if(-1 < nowCountL && -1 < nowCountR)//段差にぶつかったら無理に前進しない。
		{
			forward = -1;
		}
/*		
		if(-1 < nowCountL && nowCountR < 0)
		{
			turn = -1;
		}
		else if(-1 < nowCountR && nowCountL < 0)
		{
			turn = 1;//minus
		}
		else
		{
			turn = -1;
		}
*/
		rtn = (BlindRunning_execution(this -> blindRunning, forward, turn));
//	rtn = 1;
//		CommandValue_setCommandValue((this -> blindRunning->inherit_operationMethod.commandValue), turn, forward);
	}
	else if(seesawCtrlTime == 2 && judgeParam == EXECUTIONSEESAWSTOP)		//シーソー上旋回地点まで移動B
	{
		if(this -> seesawTime != 1)
		{
			this -> seesawTime = 1;
		}
		rtn = (BlindRunning_execution(this -> blindRunning, 20, 0));
	}
	else if(seesawCtrlTime == 2 && judgeParam == EXECUTIONSEESAWPASS)	//シーソー前半通過
	{
		rtn = (BlindRunning_execution(this -> blindRunning, 40, 1200));
	}
	else if(seesawCtrlTime == 3 && judgeParam == EXECUTIONSEESAWSTOP)		//旋回開始B
	{
//		rtn = (BlindRunning_execution(this -> blindRunning, 10, -158));
		rtn = 1;
		CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), -20, 1);
	}
	else if(seesawCtrlTime == 3 && judgeParam == EXECUTIONSEESAWPASS)
	{
		forward = (S8)SeesawPass_seesawNormalPass(this);
		rtn = (BlindRunning_execution(this -> blindRunning, forward, 0));
	}
	else if(seesawCtrlTime == 4)		//旋回開始B
	{
		rtn = (BlindRunning_execution(this -> blindRunning, 10, 158));
		rtn = 1;
		CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), -15, 0);
	}
	else if(seesawCtrlTime == 5)
	{
//		rtn = (BlindRunning_execution(this -> blindRunning, -1, 0));
//		rtn = (BlindRunning_execution(this -> blindRunning, 1, 80));
		rtn = 1;
		CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), -7, 0);
	
	}
	else if(seesawCtrlTime == 6)		//少し下がるB
	{
//		rtn = (BlindRunning_execution(this -> blindRunning, 1, 155));
		rtn = 1;
//		nowCountL = (MotorCount_getMotorCount(this->motorCountL)) - (MotorCount_getStartMotorCount(this->motorCountL));
//		nowCountR = (MotorCount_getMotorCount(this->motorCountR)) - (MotorCount_getStartMotorCount(this->motorCountR));
//		nowCountL = -nowCountL;
		
//		if((nowCountR - nowCountL) >= 0)
//		{
//			forward = -10;
//			turn = -20;
//		}
//		else
//		{
//			forward = 0;
//			turn = -5;
//		}

		CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), -5, 0);
	}
	else if(seesawCtrlTime == 7)
	{
		rtn = (BlindRunning_execution(this -> blindRunning, -10, 0));
	}
	else if(seesawCtrlTime == 8)
	{
		rtn = (BlindRunning_execution(this -> blindRunning, 10, 0));
	}
	else if(seesawCtrlTime == 9)		//少し回転するB
	{
		if(this -> seesawTime != 1)
		{
			this -> seesawTime = 1;
		}
//		rtn = 1;
//		CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), 10, 10);
		rtn = (BlindRunning_execution(this -> blindRunning ,20, -80));
	}
	else if(seesawCtrlTime == 10)		//静止を試みるS
	{
/*
		this -> seesawTime = this -> seesawTime + 1;
		//シーソー上静止を時間を使って実現する場合
		if(((this -> seesawTime / SEESAW_SQUARE_TIME) % 2) == 0)
		{
			forward = SEESAW_STOP_FORWARD;
		}
		else
		{
			forward = (-1) * SEESAW_STOP_FORWARD;
		}
*/
		//シーソー上停止をモータ回転角を利用して実現する場合
		nowCountL = (MotorCount_getMotorCount(this->motorCountL)) - (MotorCount_getStartMotorCount(this->motorCountL));
		nowCountR = (MotorCount_getMotorCount(this->motorCountR)) - (MotorCount_getStartMotorCount(this->motorCountR));
		if(this -> seesawTime == 1 && nowCountL + nowCountR <  SEESAW_STOP_DIG + SEESAW_SQUARE_DIG)
		{//前進中(目標地点未到達)
//	old		forward = SEESAW_STOP_FORWARD;
			forward = (SEESAW_STOP_DIG + SEESAW_SQUARE_DIG) - (nowCountL + nowCountR);
		}
		else if(this -> seesawTime == 1 && nowCountL + nowCountR >= SEESAW_STOP_DIG + SEESAW_SQUARE_DIG)
		{//前進中(目標地点到達済)
//	old		forward = (-1) * SEESAW_STOP_FORWARD;
			forward = -100;
			this -> seesawTime = 2;
		}
		else if(this -> seesawTime == 2 && nowCountL + nowCountR > SEESAW_STOP_DIG)
		{//後進中(目標地点未到達)
//	old		forward = (-1) * SEESAW_STOP_FORWARD;
			forward = (nowCountL + nowCountR) - SEESAW_STOP_DIG;
		}
		else if(this -> seesawTime == 2 && nowCountL + nowCountR <= SEESAW_STOP_DIG)
		{//後進中(目標地点到達済)
//	old		forward = SEESAW_STOP_FORWARD;
			forward = 100;
			this -> seesawTime = 1;
		}
		else
		{//ここにはこない。
			forward = 0;
			this -> seesawTime = 2;
		}
		//CommandValue_setCommandValue((this->blindRunning->inherit_operationMethod.commandValue), 0, forward);
		forward = forward / 10;
		if(this -> seesawTime == 1)
		{
			forward = forward + 10;
		}
		else if(this -> seesawTime == 2)
		{
			forward = forward - 10;
		}
		rtn = (BlindRunning_execution((this->blindRunning), forward, 0));
	}
	else if(seesawCtrlTime == 11)		//静止が終わり旋回を開始B
	{
		rtn = (BlindRunning_execution(this -> blindRunning, 20, -80));
	}
	else if(seesawCtrlTime == 12)		//シーソーから降りるS
	{
		forward = SeesawPass_seesawLeave(this);
		rtn = (BlindRunning_execution(this -> blindRunning, forward, 0));
	}
	else if(seesawCtrlTime >= 13)		//シーソーから降りたS 次の戦略を実行するべきところ
	{
		rtn = (BlindRunning_execution(this -> blindRunning, 40, 0));
	}
	return rtn;
}

S8 SeesawPass_seesawLeave(SeesawPass* this)
{
	S8 forward;
	
	F32 l_motor = 0;
	F32 r_motor = 0;
	F32 result_motor;
	F32 l_angle;
	F32 r_angle;
	U8 i;
	
	for(i=0;i<PWM_NUM;i++)
	{
		l_motor = l_motor + this -> pwmL->pwmValue[i];									/* 左モータPWM値 */
		r_motor = r_motor + this -> pwmR->pwmValue[i];									/* 右モータPWM値 */
	}
	l_angle = this -> motorCountL->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountL->motorCount[0];		/* 左モータ回転角 */
	r_angle = this -> motorCountR->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountR->motorCount[0];		/* 右モータ回転角 */
	
	result_motor = l_motor + r_motor;
	
	if(result_motor == 0)//割り算の分母に0が入る可能性を回避
	{
		result_motor = 0.1;
	}
	
	/* 前後進命令値の決定(微分制御) */
	/* 前進命令値 = 基本前進命令値 + 微分制御値 × ((過去のモータ回転角 / 過去のモータPWM値) - (現在のモータ回転角 / 現在のモータPWM値)) */
	forward = SEESAW_LEAVE_MAX + (SEESAW_DIFF_PARAM * (this -> past_param - ((l_angle + r_angle) / ((result_motor)))));
	/* 前後進命令値が閾値を越えていたら閾値の範囲内に収める。 */

	if(SEESAW_LEAVE_MAX < forward)
	{
		forward = SEESAW_LEAVE_MAX;
	}
	else if(forward < -100)
	{
		forward = -100;
	}
	/* (現在のモータ回転角 / 現在のモータPWM値) */
	this -> past_param = ((l_angle + r_angle) / (result_motor));
	return forward;
}

S8 SeesawPass_seesawNormalPass(SeesawPass* this)
{
	S8 forward;
	
	F32 l_motor = 0;
	F32 r_motor = 0;
	F32 result_motor;
	F32 l_angle;
	F32 r_angle;
	U8 i;

	//static integ_e = 0;
	
	for(i=0;i<PWM_NUM;i++)
	{
		l_motor = l_motor + this -> pwmL->pwmValue[i];									/* 左モータPWM値 */
		r_motor = r_motor + this -> pwmR->pwmValue[i];									/* 右モータPWM値 */
	}
	l_angle = this -> motorCountL->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountL->motorCount[0];		/* 左モータ回転角 */
	r_angle = this -> motorCountR->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountR->motorCount[0];		/* 右モータ回転角 */
	
	result_motor = (l_motor + r_motor);
	if(result_motor == 0) //割り算の分母に0が入る可能性を回避
	{
		result_motor = 0.1;
	}
	
	/* 前後進命令値の決定(比例制御) *//*  */
	/* 前進命令値 = 比例制御値 × ((傾斜0度時のモータ回転角 / 出力モータPWM値) - (実際のモータ回転角 / 出力モータPWM値)) */
	forward = (SEESAW_PROPO_PARAM * ((SMOOTH_CTRL) - ((l_angle + r_angle) / result_motor)));
	
	/* 前後進命令値の決定(積分制御) */
	/* 前進命令値 = 比例制御結果値 + (積分制御値 × (残留偏差 / 積分時間)) */
	/* 式があってるかどうかは不明 */
	//forward = forward + (SEESAW_INTEG_PARAM * (integ_e / seesaw_time));
	
		/* 前後進命令値が閾値を超えていたら閾値内に収める */
	if(forward < SEESAW_MIN_FORWARD)
	{
		forward = SEESAW_MIN_FORWARD;
	}
	else if(SEESAW_MAX_FORWARD < forward)
	{
		forward = SEESAW_MAX_FORWARD;
	}
	/* 前後進命令値の決定(微分制御) */
	/* 前進命令値 = 比例積分制御結果値 + 微分制御値 × ((過去のモータ回転角 / 過去のモータPWM値) - (現在のモータ回転角 / 現在のモータPWM値)) */
	forward = forward + (SEESAW_DIFF_PARAM * (this -> past_param - ((l_angle + r_angle) / result_motor)));
	
	/* 前後進命令値が閾値を超えていたら閾値内に収める */
	if(forward < SEESAW_MIN_FORWARD)
	{
		forward = SEESAW_MIN_FORWARD;
	}
	else if(SEESAW_MAX_FORWARD < forward)
	{
		forward = SEESAW_MAX_FORWARD;
	}
	
	/* (現在のモータ回転角 / 現在のモータPWM値) */
	this -> past_param = ((l_angle + r_angle) / result_motor);

	/* 残留偏差計算 */
//	integ_e = integ_e + (SMOOTH_CTRL- past_param);
	return forward; //ゆっくり過ぎても転ぶ。

}
