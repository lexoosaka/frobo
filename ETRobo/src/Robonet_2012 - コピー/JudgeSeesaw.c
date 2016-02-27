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
  DESCRIPTION : �R���X�g���N�^
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
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void JudgeSeesaw_finish(JudgeSeesaw* this)
{
	
}

/*===========================================================================
  FUNCTION    : JudgeSeesaw_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �V�[�\�[��̃C�x���g���Ǘ�
  MEMO        : 
===========================================================================*/
S8 JudgeSeesaw_execution(JudgeSeesaw* this, S16 judgeParam, S16 seesawCtrlTime)
{
	if(seesawCtrlTime == 0)		/* �V�[�\�[��������O*/
	{
		if(/* �ŋ߃��[�^���t��]��������V�[�\�[�ɓ��������Ɣ��� */
			this -> motorCountR->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountR->motorCount[0] <= SEESAW_FIND_PARAM ||
			this -> motorCountL->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountL->motorCount[0] <= SEESAW_FIND_PARAM
		)
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 1)		//�V�[�\�[���������̂ŏ��S
	{
		if(/* �V�[�\�[�J�n�ʒu����40mm�ȏ��ɐi�񂾂�V�[�\�[�ɏ�����Ɣ��� */
			JudgeMileage_execution(this -> judgeMileage, SEESAW_RIDE_PARAM, 0)
		)
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 2 && judgeParam == JUDGESEESAWSTOP)		//�V�[�\�[�����n�_�܂ňړ�B
	{
		if(													/* ����J�n�n�_�ɓ��B�����B */
			JudgeMileage_execution(this -> judgeMileage, SEESAW_BALANCE_POINT, 0)
		)
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 2 && judgeParam == JUDGESEESAWPASS)
	{
		if(													/* �V�[�\�[��ʉ߂���(�����~��Ă���͂��̈ʒu�܂ňړ�����)�B */
			JudgeMileage_execution(this -> judgeMileage, (SEESAW_PASS_PARAM/2), 0)
		)
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 3 && judgeParam == JUDGESEESAWSTOP)		//����J�nB
	{
		if(
			JudgeDirection_execution(this -> judgeDirection, 20, DIFF)
		)/* ���񊮗� */
		{
			return 1;
		}
	}
		else if(seesawCtrlTime == 3 && judgeParam == JUDGESEESAWPASS)
	{
		if(													/* �V�[�\�[��ʉ߂���(�����~��Ă���͂��̈ʒu�܂ňړ�����)�B */
			JudgeMileage_execution(this -> judgeMileage, (SEESAW_PASS_PARAM/2), 0)
		)
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 4)		//����J�nB
	{
		if(
			JudgeDirection_execution(this -> judgeDirection, 20, DIFF)
		)/* ���񊮗� */
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 5)		//����J�nB
	{
		if(
			JudgeDirection_execution(this -> judgeDirection, 10, 0)
		)/* ���񊮗� */
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
	else if(seesawCtrlTime == 7)		//����������B
	{
		if(JudgeMileage_execution(this -> judgeMileage, -205, 0))
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 8)		//����������B
	{
		if(JudgeMileage_execution(this -> judgeMileage, 1, 0))
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 9)		//������]����B
	{
		if(JudgeDirection_execution(this -> judgeDirection, -20, DIFF))
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 10)		//�Î~�����݂�S
	{
		this -> seesawTime = this -> seesawTime + 1;
		if(SEESAW_STOP_TIME < this -> seesawTime)					/* �V�[�\�[��Œ�~�����݂鎞�Ԃ��I������B */
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 11)		//�Î~���I��������J�nB
	{
		if(JudgeDirection_execution(this -> judgeDirection, -72, DIFF))/*���񊮗�*/
		{
			return 1;
		}
	}
	else if(seesawCtrlTime == 12)		//�V�[�\�[����~���S
	{
		if(/* ���[�^���悭�������V�[�\�[����~�肽�Ɣ��� */
			this -> motorCountR->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountR->motorCount[0] >= SEESAW_LEAVE_PARAM &&
			this -> motorCountL->motorCount[MOTOR_COUNT_NUM - 1] - this -> motorCountL->motorCount[0] >= SEESAW_LEAVE_PARAM
		)
		{
			return 1;
		}
	}
	else{
		;/* �����ɂ͂��Ȃ� */
	}
	return 0;
}

