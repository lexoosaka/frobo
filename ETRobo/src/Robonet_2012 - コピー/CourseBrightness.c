/*************************************************************************

  CourseBrightness.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "CourseBrightness.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : CourseBrightness_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �R���X�g���N�^
  MEMO        : 
===========================================================================*/
void CourseBrightness_init(CourseBrightness* this)
{
	U8 count;
	
	/* ������������ */
	this->blackThreshold = 700;
	this->whiteThreshold = 500;
	this->grayThreshold = 600;
	this->markerThreshold = 600;
	this->meanCounter = 0;
/*	for(count = 0; count < BRIGHTNESS_MOVING_AVE_NUM; count++)
	{
		this->brightnessMovingAveValue[count] = this->grayThreshold;
	}
*/	for(count = 0; count < BRIGHTNESS_NUM; count++)
	{
		this->brightness[count] = this->grayThreshold;
	}
	for(count = 0; count < BRIGHTNESS_MEAN_NUM; count++)
	{
		this->brightnessMeanValue[count] = this->grayThreshold;
	}
}

/*===========================================================================
  FUNCTION    : CourseBrightness_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void CourseBrightness_finish(CourseBrightness* this)
{
	
}

/*===========================================================================
  FUNCTION    : CourseBrightness_updateBrightness
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �P�x�l���X�V����
  MEMO        : 
===========================================================================*/
int CourseBrightness_updateBrightness(CourseBrightness* this)
{
	U8 count;
	
	/* �ړ����ς��i�[����z��̒���1�ÂO�ɂ��炷 */
/*	for(count = 0; count < (BRIGHTNESS_MOVING_AVE_NUM - 1); count++)
	{
		this->brightnessMovingAveValue[count] = this->brightnessMovingAveValue[count + 1];
	}
	this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1] = 0;
*/	
	/* ���ϒl��BRIGHTNESS_MEAN_CYCLE�񒆂�1��X�V���� */
	if(this->meanCounter == 0)
	{
		/* ���ϒl��1���O�ɂ��炷 */
		for(count = 0; count < (BRIGHTNESS_MEAN_NUM - 1); count++)
		{
			this->brightnessMeanValue[count] = this->brightnessMeanValue[count + 1];
		}
		this->brightnessMeanValue[BRIGHTNESS_MEAN_NUM - 1] = 0; /* �Ō���Ɉړ����ϒl���v�Z���ē���邽��0�ɂ��� */
	}
	
	/* �P�x�l���X�V���� */
	for(count = 0; count < (BRIGHTNESS_NUM - 1); count++)
	{
		/* �P�x�l��1���O�ɂ��炷 */
		this->brightness[count] = this->brightness[count + 1];
		
		/* �ړ����ς��v�Z���邽�߂ɍŌ������BRIGHTNESS_MOVING_AVE_CYCLE�̒l�����Z���� */
		if((BRIGHTNESS_NUM - BRIGHTNESS_MOVING_AVE_CYCLE - 1) < count)
		{
			/* ���Z */
/*			this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1] += this->brightness[count + 1];*/
		}
		
		/* ���ϒl��BRIGHTNESS_MEAN_CYCLE�񒆂�1��X�V���� */
		if(this->meanCounter == 0)
		{
			/* ���ϒl���v�Z���邽�߂ɋP�x�l�����Z */
			this->brightnessMeanValue[BRIGHTNESS_MEAN_NUM - 1] += this->brightness[count + 1];
		}
	}
	
	/* �ŐV�̒l���i�[���� */
	this->brightness[BRIGHTNESS_NUM - 1] = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
	
	/* �ŐV�̈ړ����ς��v�Z���� */
/*	this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1] += this->brightness[BRIGHTNESS_NUM - 1];
	this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1] /= BRIGHTNESS_MOVING_AVE_CYCLE;
*/	
	/* ���ϒl��BRIGHTNESS_MEAN_CYCLE�񒆂�1��X�V���� */
	if(this->meanCounter == 0)
	{
		/* �ŐV�̕��ϒl���v�Z���� */
		this->brightnessMeanValue[BRIGHTNESS_MEAN_NUM - 1] += this->brightness[BRIGHTNESS_NUM - 1];
		this->brightnessMeanValue[BRIGHTNESS_MEAN_NUM - 1] /= BRIGHTNESS_NUM;
	}
	
	/* ���ϒl���v�Z����������J�E���g����l��ݒ� */
	this->meanCounter = (this->meanCounter + 1) % BRIGHTNESS_MEAN_CYCLE;
	
/*	return (this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1]);*/
	return (this->grayThreshold - this->brightness[BRIGHTNESS_NUM - 1]);
}

/*===========================================================================
  FUNCTION    : CourseBrightness_getBrightness
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �P�x�l���擾����
  MEMO        : 
===========================================================================*/
int CourseBrightness_getBrightness(CourseBrightness* this)
{
/*	return (this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1]);*/
	return this->brightness[BRIGHTNESS_NUM - 1];
}

/*===========================================================================
  FUNCTION    : CourseBrightness_getDiffEdge
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �G�b�W�i�D�F臒l�j�Ƃ̍����擾����
  MEMO        : 
===========================================================================*/
int CourseBrightness_getDiffEdge(CourseBrightness* this)
{
/*	return (this->grayThreshold - this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1]); */
	return (this->grayThreshold - this->brightness[BRIGHTNESS_NUM - 1]);
	
}

/*===========================================================================
  FUNCTION    : CourseBrightness_getDiffPast
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �ߋ��Ƃ̍����擾����
  MEMO        : 
===========================================================================*/
int CourseBrightness_getDiffPast(CourseBrightness* this)
{
/*	return (this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 2] - this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1]);*/
	return (this->brightness[BRIGHTNESS_NUM - 1 - 5]) - (this->brightness[BRIGHTNESS_NUM - 1]);
}

/*===========================================================================
  FUNCTION    : CourseBrightness_Calibration
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �L�����u���[�V�������s��
  MEMO        : 
===========================================================================*/
void CourseBrightness_Calibration(CourseBrightness* this)
{
	U8 count;
	
	/* ����臒l��ݒ肷�� */
	/* �f�t�H���g�l��\������ */
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set BLACK");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->blackThreshold), 0);
	display_update();
	
	/* �擾�����l��\������ */
	while(0== (ecrobot_is_ENTER_button_pressed()))
	{
		if(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR))
		{
			this->blackThreshold = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
			display_goto_xy(7, 4);
			display_unsigned((U32)(this->blackThreshold), 0);
			display_update();
			while(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR));
		}
	}
	
	/* ��臒l�ݒ�I������ */
	systick_wait_ms(1500);
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp BLACK");
	systick_wait_ms(1500);
	
	/* ����臒l��ݒ肷�� */
	/* �f�t�H���g�l��\������ */
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set WHITE");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->whiteThreshold), 0);
	display_update();
	
	/* �擾�����l��\������ */
	while(0== (ecrobot_is_ENTER_button_pressed()))
	{
		if(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR))
		{
			this->whiteThreshold = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
			display_goto_xy(7, 4);
			display_unsigned((U32)(this->whiteThreshold), 0);
			display_update();
			while(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR));
		}
	}
	
	/* ��臒l�ݒ�I������ */
	systick_wait_ms(1500);
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp WHITE");
	systick_wait_ms(1500);
	
	/* ���ƍ���臒l����D�F��臒l�����肵�\������ */
	this->grayThreshold = (this->blackThreshold + this->whiteThreshold) / 2;
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp GLAY");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->grayThreshold), 0);
	systick_wait_ms(2500);
	display_clear(1);
	

	/* �D�F�}�[�J�[��臒l��ݒ肷�� */
	/* �f�t�H���g�l��\������ */
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set MARKER");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->markerThreshold), 0);
	display_update();
	
	/* �擾�����l��\������ */
	while(0== (ecrobot_is_ENTER_button_pressed()))
	{
		if(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR))
		{
			this->whiteThreshold = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
			display_goto_xy(7, 4);
			display_unsigned((U32)(this->markerThreshold), 0);
			display_update();
			while(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR));
		}
	}
	
	/* ���ƍ���臒l����D�F��臒l�����肵�\������ */
//	this->markerThreshold = (this->blackThreshold + this->markerThreshold) / 2;
	systick_wait_ms(1000);
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp MARKER");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->markerThreshold), 0);
	systick_wait_ms(1500);
	display_clear(1);

	
	
	/* �z����D�F��臒l�ŏ����� */
	this->grayThreshold = 610;
/*	for(count = 0; count < BRIGHTNESS_MOVING_AVE_NUM; count++)
	{
		this->brightnessMovingAveValue[count] = this->grayThreshold;
	}
*/	for(count = 0; count < BRIGHTNESS_NUM; count++)
	{
		this->brightness[count] = this->grayThreshold;
	}
	for(count = 0; count < BRIGHTNESS_MEAN_NUM; count++)
	{
		this->brightnessMeanValue[count] = this->grayThreshold;
	}
}

/*===========================================================================
  FUNCTION    : CourseBrightness_getThreshold
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 臒l���擾����
  MEMO        : 
===========================================================================*/
int CourseBrightness_getThreshold(CourseBrightness* this, U8 thresholdId)
{
	int threshold;
	
	switch(thresholdId)
	{
	case BLACK:
		threshold = this->blackThreshold;
		break;
	case WHITE:
		threshold = this->whiteThreshold;
		break;
	case GRAY:
		threshold = this->grayThreshold;
		break;
	case MARKER:
		threshold = this->markerThreshold;
		break;
	default:
		threshold = this->grayThreshold;
		break;
	}
	
	return threshold;
}

/*===========================================================================
  FUNCTION    : CourseBrightness_getMeanBrightness
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���ϒl���擾����
  MEMO        : 
===========================================================================*/
int CourseBrightness_getMeanBrightness(CourseBrightness* this)
{
	U8 count;
	int meanValue = 0;
	
	for(count = 0; count < BRIGHTNESS_MEAN_NUM; count++)
	{
		meanValue += this->brightnessMeanValue[count];
	}
	meanValue /= BRIGHTNESS_MEAN_NUM;
	
	return meanValue;
}
