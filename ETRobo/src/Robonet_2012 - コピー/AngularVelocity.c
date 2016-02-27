/*************************************************************************

  AngularVelocity.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "AngularVelocity.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : AngularVelocity_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ����������
  MEMO        : 
===========================================================================*/
void AngularVelocity_init(AngularVelocity* this)
{
	U8 count;
	
	/* ���������������� */
	this->offsetValue = DEFAULT_OFFSET; /* �W���C���Z���T�I�t�Z�b�g�l���f�t�H���g�l�ɐݒ� */
	this->meanCounter = 0; /* ���ϒl���v�Z����������J�E���g����ϐ��������� */
	for(count = 0; count < ANGULAR_VELOCITY_NUM; count++)
	{
		this->angularVelocity[count] = DEFAULT_OFFSET; /* �z����f�t�H���g�l�ŏ����� */
	}
	for(count = 0; count < ANGULAR_VELOCITY_MEAN_NUM; count++)
	{
		this->meanAngularVelocity[count] = DEFAULT_OFFSET; /* ���ϒl�̔z����f�t�H���g�l�ŏ����� */
	}
}

/*===========================================================================
  FUNCTION    : AngularVelocity_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �I������
  MEMO        : 
===========================================================================*/
void AngularVelocity_finish(AngularVelocity* this)
{
	
}

/*===========================================================================
  FUNCTION    : AngularVelocity_Calibration
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �L�����u���[�V��������
  MEMO        : 
===========================================================================*/
void AngularVelocity_Calibration(AngularVelocity* this)
{
	U8 count = 0;
	
	/* �f�t�H���g�l��\�� */
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set OFFSET");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->offsetValue), 0);
	display_update();
	
	/* �擾�����l��\�� */
	while(0== (ecrobot_is_ENTER_button_pressed()))
	{
		if(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR))
		{
			this->offsetValue = ecrobot_get_gyro_sensor(PORT_GYRO_SENSOR);
			display_goto_xy(7, 4);
			display_unsigned((U32)(this->offsetValue), 0);
			display_update();
			while(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR));
		}
	}
	
	/* �L�����u���[�V�����I������ */
	systick_wait_ms(1500);
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp OFFSET");
	systick_wait_ms(1500);
	display_clear(1);
	
	/* �z���ݒ肵���W���C���Z���T�I�t�Z�b�g�l�ŏ����� */
	for(count = 0; count < ANGULAR_VELOCITY_NUM; count++)
	{
		this->angularVelocity[count] = this->offsetValue;
	}
	for(count = 0; count < ANGULAR_VELOCITY_MEAN_NUM; count++)
	{
		this->meanAngularVelocity[count] = this->offsetValue;
	}
}

/*===========================================================================
  FUNCTION    : AngularVelocity_getOffsetValue
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �W���C���Z���T�I�t�Z�b�g�l���擾����
  MEMO        : 
===========================================================================*/
U16 AngularVelocity_getOffsetValue(AngularVelocity* this)
{
	return (this->offsetValue);
}

/*===========================================================================
  FUNCTION    : AngularVelocity_updateAngularVelocity
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �p���x���X�V����
  MEMO        : 
===========================================================================*/
U16 AngularVelocity_updateAngularVelocity(AngularVelocity* this)
{
	U8 count;
	
	/* ���ϒl�̔z��̍X�V��ANGULAR_VELOCITY_MEAN_CYCLE��Ɉ�� */
	if(this->meanCounter == 0)
	{
		/* ���ϒl�̔z��Ɋi�[����Ă���l��1���O�ɂ��炷 */
		for(count = 0; count < (ANGULAR_VELOCITY_MEAN_NUM - 1); count++)
		{
			this->meanAngularVelocity[count] = this->meanAngularVelocity[count + 1];
		}
		this->meanAngularVelocity[ANGULAR_VELOCITY_MEAN_NUM - 1] = 0;
	}
	
	/* �p���x�̔z��Ɋi�[����Ă���l��1���O�ɂ��炵�ŐV�̒l���Ō���Ɋi�[���� */
	for(count = 0; count < (ANGULAR_VELOCITY_NUM - 1); count++)
	{
		this->angularVelocity[count] = this->angularVelocity[count + 1];
		
		/* ���ϒl�̔z��̍X�V��ANGULAR_VELOCITY_MEAN_CYCLE��Ɉ�� */
		if(this->meanCounter == 0)
		{
			/* ���ϒl���v�Z���邽�߂Ɋp���x�̔z��̒l�����Z���Ă��� */
			this->meanAngularVelocity[ANGULAR_VELOCITY_MEAN_NUM - 1] += this->angularVelocity[count + 1];
		}
	}
	this->angularVelocity[ANGULAR_VELOCITY_NUM - 1] = ecrobot_get_gyro_sensor(PORT_GYRO_SENSOR); /* �ŐV�̒l���擾 */
	
	/* ���ϒl�̔z��̍X�V��ANGULAR_VELOCITY_MEAN_CYCLE��Ɉ�� */
	if(this->meanCounter == 0)
	{
		/* ���ϒl���v�Z */
		this->meanAngularVelocity[ANGULAR_VELOCITY_MEAN_NUM - 1] += this->angularVelocity[ANGULAR_VELOCITY_NUM - 1];
		this->meanAngularVelocity[ANGULAR_VELOCITY_MEAN_NUM - 1] /= (ANGULAR_VELOCITY_NUM);
	}
	
	/* ���ϒl���v�Z����������J�E���g����ϐ���ݒ� */
	this->meanCounter = (this->meanCounter + 1) % ANGULAR_VELOCITY_MEAN_CYCLE;
	
	return (this->angularVelocity[ANGULAR_VELOCITY_NUM - 1]);
}

/*===========================================================================
  FUNCTION    : AngularVelocity_getMeanAngularVelocity
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���ϒl���擾����
  MEMO        : 
===========================================================================*/
U16 AngularVelocity_getMeanAngularVelocity(AngularVelocity* this)
{
	U8 count;
	U16 meanValue = 0;
	
	/* ���ϒl���v�Z���� */
	/* ���ϒl�̕��ς��o�����ƂŒ��������̕��ς��v�Z����(������ANGULAR_VELOCITY_MEAN_NUM * ANGULAR_VELOCITY_MEAN_CYCLE) */
	for(count = 0; count < ANGULAR_VELOCITY_MEAN_NUM; count++)
	{
		meanValue += this->meanAngularVelocity[count];
	}
	meanValue /= ANGULAR_VELOCITY_MEAN_NUM;
	
	return meanValue;
}
