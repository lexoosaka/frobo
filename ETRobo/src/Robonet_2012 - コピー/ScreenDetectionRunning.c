/*************************************************************************

  ScreenDetectionRunning.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "ScreenDetectionRunning.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : ScreenDetectionRunning_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �R���X�g���N�^
  MEMO        : 
===========================================================================*/
void ScreenDetectionRunning_init(
	ScreenDetectionRunning* this,
	BlindRunning* blindRunning,
	CommandValue* commandValue,
	SonarData* sonarData
)
{
	U8 count;
	
	/* ������������ */
	OperationMethod_init(&(this->inherit_operationMethod), commandValue);
	this->blindRunning = blindRunning;
	this->sonarData = sonarData;
	for(count = 0; count < SCREEN; count++)
	{
		this->screen[count] = 0;
	}
}

/*===========================================================================
  FUNCTION    : ScreenDetectionRunning_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void ScreenDetectionRunning_finish(ScreenDetectionRunning* this)
{

}

/*===========================================================================
  FUNCTION    : ScreenDetectionRunning_execution
  PARAMETERS  : 
  RETURN      : 1�F�~�X�e���[�T�[�N���ʉ߃��[�g�̕ύX����
                2�F�~�X�e���[�T�[�N���ʉ߃��[�g���p�^�[��B�ɕύX
                3�F�~�X�e���[�T�[�N���ʉ߃��[�g���p�^�[��C�ɕύX
                4�F�~�X�e���[�T�[�N���ʉ߃��[�g���p�^�[��D�ɕύX
  DESCRIPTION : �՗��̌��o�Ɩ��ߒl�̐ݒ�
  MEMO        : �~�X�e���[�T�[�N���ʉ߃��[�g�̓f�t�H���g�Ńp�^�[��A�ɐݒ�
                �˕ύX��1����Ȃ��ꍇ�A�p�^�[��A�ő��s����
===========================================================================*/
S8 ScreenDetectionRunning_execution(ScreenDetectionRunning* this, S8 screenId, S16 turningRadius)
{
	S32 sonarReturn = 0; /* �\�i�[�Z���T�̖߂�l */
	S8 rtn = 1; /* ���^�[���l */
	
	/* �\�i�[�Z���T�ŏ�Q���܂ł̋����𑪒� */
	sonarReturn = SonarData_get(this->sonarData);
	
	/* ��Q���܂ł̋������ݒ�l�ȉ��ł���΁A�՗�������Ɣ��f���� */
	if(sonarReturn <= MINDISTANCE)
	{
		/* �����՗������x�����o���Ă��ʉ߃��[�g��ύX����͍̂ŏ��̈��̂� */
		if(this->screen[screenId] == 0)
		{
			/* �՗��p�^�[����ݒ� */
			this->screen[screenId] = 1;
			
			/* �՗��p�^�[������ʉ߃��[�g�𔻒f���߂�l��ݒ� */
			if(this->screen[0] == 0)
			{
				/* �p�^�[��B */
				if(this->screen[1] == 1)
				{
					rtn = 2;
				}
			}
			else
			{
				/* �p�^�[��C */
				if(this->screen[1] == 0)
				{
					rtn = 3;
				}
				/* �p�^�[��D */
				else
				{
					rtn = 4;
				}
			}
		}
	}
	
	/* ���ߒl��ݒ� */
	if(turningRadius < (TRED / 2))
	{
		BlindRunning_execution(this->blindRunning, 0, (TRED / 2 + 10));
	}
	else
	{
		BlindRunning_execution(this->blindRunning, 30, turningRadius);
	}
/*	CommandValue_setCommandValue((this->inherit_operationMethod.commandValue), -30, speed);*/
	
	return rtn;
}


