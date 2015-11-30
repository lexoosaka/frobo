/*************************************************************************

  BlindRunning.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "BlindRunning.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : BlindRunning_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void BlindRunning_init(
	BlindRunning* this,
	MotorCount* motorCountL,
	MotorCount* motorCountR,
	CommandValue* commandValue
)
{
	/* 属性を初期化 */
	OperationMethod_init(&(this->inherit_operationMethod), commandValue);
	this->motorCount[0] = motorCountL;
	this->motorCount[1] = motorCountR;
}

/*===========================================================================
  FUNCTION    : BlindRunning_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void BlindRunning_finish(BlindRunning* this)
{

}

/*===========================================================================
  FUNCTION    : BlindRunning_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ブラインド走行時の命令値を決定する
  MEMO        : 
===========================================================================*/
S8 BlindRunning_execution(BlindRunning* this, S8 speed, S16 turningRadius)
{
	S16 targetRatioL; /* 左モータの回転角の目標比 */
	S16 targetRatioR; /* 右モータの回転角の目標比 */
	S32 targetCountR; /* 右モータの目標回転角 */
	S16 nowCountL; /* ブラインド走行開始後からの左モータの回転角 */
	S16 nowCountR; /* ブラインド走行開始後からの右モータの回転角 */
	S16 turningRadiusCopy = turningRadius; /* 旋回半径をコピー */
	S32 turn; /* 旋回命令値 */
	
	/* 計算のため旋回半径が負の値の場合は正の値に変換する */
	if(turningRadiusCopy < 0)
	{
		turningRadiusCopy *= -1;
	}
	/* 左モータの回転角の目標比を計算 */
	targetRatioL = turningRadiusCopy - (TRED / 2);
	if(targetRatioL < 0)
	{
		targetRatioL *= -1;
	}
	/* 右モータの回転角の目標比を計算 */
	targetRatioR = turningRadiusCopy + (TRED / 2);
	
	/* 旋回半径が負の値の場合左右のモータの目標比を入れ替える */
	if(turningRadius < 0)
	{
		turningRadiusCopy = targetRatioL;
		targetRatioL = targetRatioR;
		targetRatioR = turningRadiusCopy;
	}
	
	/* ブラインド走行開始後からのそれぞれのモータの回転角を取得 */
	nowCountL = (MotorCount_getMotorCount(this->motorCount[0])) - (MotorCount_getStartMotorCount(this->motorCount[0]));
	nowCountR = (MotorCount_getMotorCount(this->motorCount[1])) - (MotorCount_getStartMotorCount(this->motorCount[1]));
	
	/* 現在の左モータの回転角から右モータの目標回転角を計算 */
	targetCountR = nowCountL * targetRatioR / targetRatioL;
	
	/* 右モータの目標回転角と現在の回転角の差から旋回命令値を決定 */
	turn = (nowCountR - targetCountR) * 2;
	
	turn = (((turn) >= (50)) ? (50) : (((turn) <= (-50)) ? (-50) : (turn)));
	
	/* 命令値を設定 */
	CommandValue_setCommandValue((this->inherit_operationMethod.commandValue), (S8)turn, speed);
	
	return (S8)1;
}




