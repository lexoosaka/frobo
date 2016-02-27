/**
******************************************************************************
** ファイル名: StepCapture.c
**
** 概要: 機体の向きを検知し、直進し、階段を上り下りするプログラム
**       マルチタスク
******************************************************************************
**/
/*
*****************************
sh ./rxeflash.sh
*****************************
*/
/****************************
*include
****************************/
#include "StepCapture.h"

/****************************/
//global
/****************************/

/*******************************
*関数プロトタイプ宣言
*******************************/

/*===========================================================================
  FUNCTION    : StepCapture_init
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : StepCaptureの初期化
===========================================================================*/
void StepCapture_init
(
	StepCapture* this,
	CommandValue* commandValue,
	JudgeStepCapture* judgeStepCapture,
	BlindRunning* blindRunning
)
{
	OperationMethod_init(&(this->inherit_operationMethod), commandValue);
	this->judgeStepCapture = judgeStepCapture;
	this->blindRunning = blindRunning;
	this->forward = 0;
	this->time_cnt = 0;
	this->flag = 0;
	this->shift_check = 0;
}

/*===========================================================================
  FUNCTION    : GoUpStep1
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : 1段目を上る。前進命令値の決定
===========================================================================*/
void GoUpStep1(StepCapture* this, S8 vol)
{
	// 初期値の設定 //
	if(this->flag == 0)
	{
		this->forward = FIRSTF1 + vol;
		this->flag++;
	}
	
	// 一定時間ごとにfowradを増加する。上限あり //
	if(this->forward <= (LIMIT1) && (this->time_cnt % CNT1) == 0)
	{
		this->forward++;
	}
}

/*===========================================================================
  FUNCTION    : GoUpStep2
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : 2段目を上る。前進命令値の決定
===========================================================================*/
void GoUpStep2(StepCapture* this, S8 vol)
{
	// 初期値の設定 //
	if(this->flag == 0)
	{
		this->forward = FIRSTF3 + vol;
		this->flag++;
	}
	
	// 一定時間ごとにfowradを増加する。上限あり //
	if(this->forward <= (LIMIT3) && (this->time_cnt % CNT3) == 0){
		this->forward++;
	}
}

/*===========================================================================
  FUNCTION    : LevelRun1
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : 2段目を見つけるまで。前進命令値の決定
===========================================================================*/
void LevelRun1(StepCapture* this)
{
	// 初期値の設定 //
	if(this->flag == 0)
	{
		this->forward = FIRSTF2;
		this->flag++;
	}
	
	// 一定時間ごとにfowradを増加する。上限あり //
	if(this->forward <= (LIMIT2) && (this->time_cnt % CNT2) == 0){
		this->forward++;
	}
}

/*===========================================================================
  FUNCTION    : LevelRun2
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : 階段を降りるまで。前進命令値の決定
===========================================================================*/
void LevelRun2(StepCapture* this)
{
	// 初期値の設定 //
	if(this->flag == 0)
	{
		this->forward = FIRSTF4;
		this->flag++;
	}
	
	// 一定時間ごとにfowradを増加する。上限あり //
	if(this->forward <= (LIMIT4) && (this->time_cnt % CNT4) == 0){
		this->forward++;
	}
}

/*===========================================================================
  FUNCTION    : LevelRun3
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : 階段を降りて安定するまで。前進命令値の決定
===========================================================================*/
void LevelRun3(StepCapture* this)
{
	// 初期値の設定 //
	if(this->flag == 0)
	{
		this->forward = FIRSTF5;
		this->flag++;
	}
	
	// 一定時間ごとにfowradを増加する。上限あり //
	if(this->forward <= (LIMIT5) && (this->time_cnt % CNT5) == 0)
	{
		this->forward++;
	}
}

/*===========================================================================
  FUNCTION    : StepCaptureExecution
  PARAMETERS  : 
  RETURN      : S8
  DESCRIPTION : 求めたforward値を渡す。turn値は0
===========================================================================*/
S8 StepCaptureExecution(StepCapture* this, S8 stage, S16 noParam)
{
	U16 vol;								// 電圧値
	
	vol = ecrobot_get_battery_voltage();	// 電圧値の取得
	
	if(this->shift_check != stage)			// 戦略が移行したかチェック
	{
		this->flag = 0;						// フラグをリセット
		this->shift_check = stage;			// shift_checkの設定
	}
	
	if(stage >= 1 && this->flag == 0)		// 電圧値によってforwardを変化させる
	{
		vol /= 100;							// 値をforwardに合わせるために100で割る
		
		if((vol / 100) >= VOLSTAN)			// 設定値以上だったらfowardを変化させない
		{
			vol = 0;
		}
		else
		{
			vol = VOLSTAN - vol;
		}
	}
	
	// 戦略パラメータごとに関数を実行 //
	if(stage == 0)							// 1段目を見つけるまで
	{
		this->forward = FIRSTFORWARD;
	}
	else if(stage == 1)						// 1段目を上るまで
	{
		GoUpStep1(this, vol);
	}
	else if(stage == 2)						// 2段目を見つけるまで
	{
		LevelRun1(this);
	}
	else if(stage == 3)						// 2段目を上るまで
	{
		GoUpStep2(this, vol);
	}
	else if(stage == 4)						// 階段を下るまで
	{
		LevelRun2(this);
	}
	else if(stage == 5)						// 階段を降りてから安定するまで
	{
		LevelRun3(this);
	}
	
	this->time_cnt++;						// 時間をカウント
	
	BlindRunning_execution(this->blindRunning, this->forward, 0);	// forward値を渡してブラインド走行を実行、直進
	
	return (S8)1;
}

