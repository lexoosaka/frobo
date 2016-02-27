/*************************************************************************

  Pwm.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "Pwm.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : Pwm_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �R���X�g���N�^
  MEMO        : 
===========================================================================*/
void Pwm_init(Pwm* this)
{
	int count;
	
	/* ������ */
	for(count = 0; count < PWM_NUM; count++)
	{
		this->pwmValue[count] = 0;
	}
	for(count = 0; count < PWM_MEAN_NUM; count++)
	{
		this->pwmMeanValue[count] = 0;
	}
	this->meanCounter = 0;
}

/*===========================================================================
  FUNCTION    : Pwm_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void Pwm_finish(Pwm* this)
{

}

/*===========================================================================
  FUNCTION    : Pwm_updatePwm
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : PWM�l���X�V
  MEMO        : 
===========================================================================*/
void Pwm_updatePwm(Pwm* this, signed char pwmValue)
{
	int count;
	int meanValue = 0;
	
	/* ���ϒl���X�V��PWM_MEAN_CYCLE��Ɉ�� */
	if(this->meanCounter == 0)
	{
		/* ���ϒl���i�[����z��̒��g������O�ɂ��炷 */
		for(count = 0; count < (PWM_MEAN_NUM - 1); count++)
		{
			this->pwmMeanValue[count] = this->pwmMeanValue[count + 1];
		}
	}
	
	/* PWM�l���i�[����z��̒��g������O�ɂ��炷 */
	for(count = 0; count < (PWM_NUM - 1); count++)
	{
		this->pwmValue[count] = this->pwmValue[count + 1];
		
		/* ���ϒl���X�V��PWM_MEAN_CYCLE��Ɉ�� */
		if(this->meanCounter == 0)
		{
			/* ���ς��o�����߂ɉ��Z */
			meanValue += (int)(this->pwmValue[count + 1]);
		}
	}
	/* �ŐV�̒l���i�[ */
	this->pwmValue[PWM_NUM - 1] = pwmValue;
	
	/* ���ϒl���X�V��PWM_MEAN_CYCLE��Ɉ�� */
	if(this->meanCounter == 0)
	{
		/* ���ϒl���v�Z */
		meanValue += (int)pwmValue;
		meanValue /= (PWM_NUM);
		this->pwmMeanValue[PWM_MEAN_NUM - 1] = (char)meanValue;
	}
	
	this->meanCounter = (this->meanCounter + 1) % PWM_MEAN_CYCLE;
}

/*===========================================================================
  FUNCTION    : Pwm_getPwm
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : PWM�l���擾
  MEMO        : 
===========================================================================*/
signed char Pwm_getPwm(Pwm* this)
{
	return (this->pwmValue[PWM_NUM - 1]);
}

/*===========================================================================
  FUNCTION    : Pwm_getMeanPwm
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���ϒl���擾����
  MEMO        : 
===========================================================================*/
signed char Pwm_getMeanPwm(Pwm* this)
{
	U8 count;
	S16 meanValue = 0;
	
	for(count = 0; count < PWM_MEAN_NUM; count++)
	{
		meanValue += this->pwmMeanValue[count];
	}
	meanValue /= PWM_MEAN_NUM;
	
	return (signed char)meanValue;
}

