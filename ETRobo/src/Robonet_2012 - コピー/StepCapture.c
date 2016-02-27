/**
******************************************************************************
** �t�@�C����: StepCapture.c
**
** �T�v: �@�̂̌��������m���A���i���A�K�i����艺�肷��v���O����
**       �}���`�^�X�N
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
*�֐��v���g�^�C�v�錾
*******************************/

/*===========================================================================
  FUNCTION    : StepCapture_init
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : StepCapture�̏�����
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
  DESCRIPTION : 1�i�ڂ����B�O�i���ߒl�̌���
===========================================================================*/
void GoUpStep1(StepCapture* this, S8 vol)
{
	// �����l�̐ݒ� //
	if(this->flag == 0)
	{
		this->forward = FIRSTF1 + vol;
		this->flag++;
	}
	
	// ��莞�Ԃ��Ƃ�fowrad�𑝉�����B������� //
	if(this->forward <= (LIMIT1) && (this->time_cnt % CNT1) == 0)
	{
		this->forward++;
	}
}

/*===========================================================================
  FUNCTION    : GoUpStep2
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : 2�i�ڂ����B�O�i���ߒl�̌���
===========================================================================*/
void GoUpStep2(StepCapture* this, S8 vol)
{
	// �����l�̐ݒ� //
	if(this->flag == 0)
	{
		this->forward = FIRSTF3 + vol;
		this->flag++;
	}
	
	// ��莞�Ԃ��Ƃ�fowrad�𑝉�����B������� //
	if(this->forward <= (LIMIT3) && (this->time_cnt % CNT3) == 0){
		this->forward++;
	}
}

/*===========================================================================
  FUNCTION    : LevelRun1
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : 2�i�ڂ�������܂ŁB�O�i���ߒl�̌���
===========================================================================*/
void LevelRun1(StepCapture* this)
{
	// �����l�̐ݒ� //
	if(this->flag == 0)
	{
		this->forward = FIRSTF2;
		this->flag++;
	}
	
	// ��莞�Ԃ��Ƃ�fowrad�𑝉�����B������� //
	if(this->forward <= (LIMIT2) && (this->time_cnt % CNT2) == 0){
		this->forward++;
	}
}

/*===========================================================================
  FUNCTION    : LevelRun2
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : �K�i���~���܂ŁB�O�i���ߒl�̌���
===========================================================================*/
void LevelRun2(StepCapture* this)
{
	// �����l�̐ݒ� //
	if(this->flag == 0)
	{
		this->forward = FIRSTF4;
		this->flag++;
	}
	
	// ��莞�Ԃ��Ƃ�fowrad�𑝉�����B������� //
	if(this->forward <= (LIMIT4) && (this->time_cnt % CNT4) == 0){
		this->forward++;
	}
}

/*===========================================================================
  FUNCTION    : LevelRun3
  PARAMETERS  : 
  RETURN      : none
  DESCRIPTION : �K�i���~��Ĉ��肷��܂ŁB�O�i���ߒl�̌���
===========================================================================*/
void LevelRun3(StepCapture* this)
{
	// �����l�̐ݒ� //
	if(this->flag == 0)
	{
		this->forward = FIRSTF5;
		this->flag++;
	}
	
	// ��莞�Ԃ��Ƃ�fowrad�𑝉�����B������� //
	if(this->forward <= (LIMIT5) && (this->time_cnt % CNT5) == 0)
	{
		this->forward++;
	}
}

/*===========================================================================
  FUNCTION    : StepCaptureExecution
  PARAMETERS  : 
  RETURN      : S8
  DESCRIPTION : ���߂�forward�l��n���Bturn�l��0
===========================================================================*/
S8 StepCaptureExecution(StepCapture* this, S8 stage, S16 noParam)
{
	U16 vol;								// �d���l
	
	vol = ecrobot_get_battery_voltage();	// �d���l�̎擾
	
	if(this->shift_check != stage)			// �헪���ڍs�������`�F�b�N
	{
		this->flag = 0;						// �t���O�����Z�b�g
		this->shift_check = stage;			// shift_check�̐ݒ�
	}
	
	if(stage >= 1 && this->flag == 0)		// �d���l�ɂ����forward��ω�������
	{
		vol /= 100;							// �l��forward�ɍ��킹�邽�߂�100�Ŋ���
		
		if((vol / 100) >= VOLSTAN)			// �ݒ�l�ȏゾ������foward��ω������Ȃ�
		{
			vol = 0;
		}
		else
		{
			vol = VOLSTAN - vol;
		}
	}
	
	// �헪�p�����[�^���ƂɊ֐������s //
	if(stage == 0)							// 1�i�ڂ�������܂�
	{
		this->forward = FIRSTFORWARD;
	}
	else if(stage == 1)						// 1�i�ڂ����܂�
	{
		GoUpStep1(this, vol);
	}
	else if(stage == 2)						// 2�i�ڂ�������܂�
	{
		LevelRun1(this);
	}
	else if(stage == 3)						// 2�i�ڂ����܂�
	{
		GoUpStep2(this, vol);
	}
	else if(stage == 4)						// �K�i������܂�
	{
		LevelRun2(this);
	}
	else if(stage == 5)						// �K�i���~��Ă�����肷��܂�
	{
		LevelRun3(this);
	}
	
	this->time_cnt++;						// ���Ԃ��J�E���g
	
	BlindRunning_execution(this->blindRunning, this->forward, 0);	// forward�l��n���ău���C���h���s�����s�A���i
	
	return (S8)1;
}

