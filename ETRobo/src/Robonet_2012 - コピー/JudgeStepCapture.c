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
  DESCRIPTION : �R���X�g���N�^
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
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void JudgeStepCapture_finish(JudgeStepCapture* this)
{
	
}

/*===========================================================================
  FUNCTION    : JudgeStepCapture_BalanceCheckC
  PARAMETERS  : 
  RETURN      : S8
  DESCRIPTION : �o�����X�̕���𔻒肷��
  MEMO        : 
===========================================================================*/
S8 JudgeStepCapture_BalanceCheckC(JudgeStepCapture* this)
{
	U16 meanValue;
	
	meanValue = AngularVelocity_getMeanAngularVelocity(this->angularVelocity);	// �W���C���l���擾
	
	// �W���C���l����l�ȏ�A�������͊�l�ȉ��������� //
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
  DESCRIPTION : �o�����X�̈���𔻒肷��i���f���߁j
  MEMO        : 
===========================================================================*/
S8 JudgeStepCapture_BalanceCheckS1(JudgeStepCapture* this)
{
	U16 meanValue;
	
	meanValue = AngularVelocity_getMeanAngularVelocity(this->angularVelocity);	// �W���C���l���擾
	
	// �W���C���l����l���������� //
	if(((meanValue >= this->angularVelocity->offsetValue - STEPJUDGE2) && (meanValue <= this->angularVelocity->offsetValue - STEPJUDGE1)))
	{
		this -> stab_cnt++;							// ��l���ɂ������Ԃ��J�E���g
		if(this -> stab_cnt > STEP1JUDGECNT)		// ��莞�Ԋ�l���ɂ���
		{
			this->stab_cnt = 0;
			return 1;
		}
	}
	else
	{
		this -> stab_cnt = 0;						// stab_cnt�����Z�b�g
	}
	
	return 0;
}

/*===========================================================================
  FUNCTION    : JudgeStepCapture_BalanceCheckS2
  PARAMETERS  : 
  RETURN      : S8
  DESCRIPTION : �o�����X�̈���𔻒肷��i���f�x�߁j
  MEMO        : 
===========================================================================*/
S8 JudgeStepCapture_BalanceCheckS2(JudgeStepCapture* this)
{
	U16 meanValue;
	
	meanValue = AngularVelocity_getMeanAngularVelocity(this->angularVelocity);	// �W���C���l���擾
	
	// �W���C���l����l���������� //
	if(((meanValue >= this->angularVelocity->offsetValue - STEPJUDGE2) && (meanValue <= this->angularVelocity->offsetValue - STEPJUDGE1)))
	{
		this -> stab_cnt++;							// ��l���ɂ������Ԃ��J�E���g
		if(this -> stab_cnt > STEP2JUDGECNT)		// ��莞�Ԋ�l���ɂ���
		{
			this->stab_cnt = 0;
			return 1;
		}
	}
	else
	{
		this -> stab_cnt = 0;						// stab_cnt�����Z�b�g
	}
	
	return 0;
}

/*===========================================================================
  FUNCTION    : JudgeStepCapture_TimeCount
  PARAMETERS  : 
  RETURN      : S8
  DESCRIPTION : ���Ԃ��J�E���g����
  MEMO        : 
===========================================================================*/
S8 JudgeStepCapture_TimeCount(JudgeStepCapture* this, S8 flag)
{
	this->time_cnt++;
	
	// ��莞�ԉ߂���A��������flag������1�ł��邩 //
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
  DESCRIPTION : �헪�̈ӌ��𔻒f����
  MEMO        : 
===========================================================================*/
S8 JudgeStepCapture_execution
(
	JudgeStepCapture* this,
	S16 prm1,
	S16 prm2
)
{
	S8 flag = 0;											// �헪�ڍs�̃t���O
	
	if(prm1 == 0)											// �o�����X�̕���𔻒f����
	{
		flag = JudgeStepCapture_BalanceCheckC(this);
	}
	else if(prm1 == 1)										// �o�����X�̈���𔻒肷��(������)
	{
		flag = JudgeStepCapture_BalanceCheckS1(this);
	}
	else if(prm1 == 2)										// �o�����X�̈���𔻒肷��(���x��)
	{
		flag = JudgeStepCapture_BalanceCheckS2(this);
	}
	
	if(prm2 == 1)											// ���Ԃ��J�E���g����
	{
		flag = JudgeStepCapture_TimeCount(this, flag);
	}
	
	return flag;
}

