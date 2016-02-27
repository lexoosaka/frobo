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
  DESCRIPTION : �R���X�g���N�^
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
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void JudgeDirection_finish(JudgeDirection* this)
{
	
}

/*===========================================================================
  FUNCTION    : JudgeDirection_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �����𔻒肷��
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
	
	/* ���݂̑��s�̂̌������擾 */
	direction = RunningPositionInfo_getDirection(this->runningPositionInfo);
	
	/* �����ɓ����������� */
	if(mode == DIRECTION_STABILITY)
	{
#if 0
		/* �p�x�̗h�ꕝ�̑�����J�n���Ă��Ȃ�(�J�n���Ă��Ȃ��ꍇ�A�h�ꕝ���傫���Ȃ�߂��ă��Z�b�g�����ꍇ��"this->diffCount"��"-125"�������Ă���)*/
		if(this->diffCount == -125)
		{
			diff = 0;
		}
		/* �p�x�̗h�ꕝ�̑�����J�n���Ă��� */
		else
		{
			diff = this->pastDirection - direction; /* ���O����̗h�ꕝ�𑪒� */
		}
#endif
		diff = this->pastDirection - direction; /* ���O����̗h�ꕝ�𑪒� */
		this->pastDirection = direction; /* �ߋ��̊p�x���X�V */
		
		/* ���O�̗h�ꕝ�𔻒肵�A�h�ꕝ�����e�͈͓� */
		if(((-1 * DIRECTION_RANGE) < diff) && (diff < DIRECTION_RANGE))
		{
			/* ���񂩂�h�ꕝ�̑�����J�n���n�߂� */
			if(this->diffCount == -125)
			{
				this->stabilityMileage = RunningPositionInfo_getMileage(this->runningPositionInfo); /* �J�n�������i�[ */
				this->diffCount = diff; /* �h�ꕝ���i�[ */
			}
			/* ���łɊJ�n���Ă��� */
			else
			{
				mileage = RunningPositionInfo_getMileage(this->runningPositionInfo); /* ���݋����擾 */
				this->diffCount += diff; /* �h�ꕝ�����Z */
				
				/* ���Z�����h�ꕝ�����e�͈͓� */
				if(((-1 * DIRECTION_RANGE) < (this->diffCount)) && ((this->diffCount) < DIRECTION_RANGE))
				{
					/* �h�ꕝ�𑪒肵�n�߂Ďw�苗�����s����(���̔��胂�[�h�ł�"targetValue"�ő��s�������w�肷��) */
					if(targetValue < (mileage - (this->stabilityMileage)))
					{
						this->diffCount = -125; /* �h�ꕝ����l�������� */
						return 1; /* ���肪�������ꂽ���Ƃ�ʒm */
					}
				}
				/* ���e�͈͂��z���� */
				else
				{
					this->diffCount = -125; /* �h�ꕝ����l�����������h�ꕝ�̑������蒼�� */
				}
			}
		}
		/* ���e�͈͂��z���� */
		else
		{
			this->diffCount = -125; /* �h�ꕝ����l�����������h�ꕝ�̑������蒼�� */
		}
	}
	/* ���̔��胂�[�h(�헪�J�n���猻�݂܂ł̑��s�̂̌����𔻒�A�܂��͑��s�J�n����̐�Ίp�x�𔻒�) */
	else
	{
		/* �헪�J�n���猻�݂܂ł̑��s�̂̌����𔻒肷��ꍇ */
		if(mode == DIFF)
		{
			/* ���s���̐헪�J�n�����猻�݂܂łɕω������������擾 */
			direction -= RunningPositionInfo_getStartDirection(this->runningPositionInfo);
		}
		
		/* ��r���Ĕ��� */
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

