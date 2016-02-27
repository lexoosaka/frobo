/*************************************************************************

  PDControlParameter.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "PDControlParameter.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : PDControlParameter_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �R���X�g���N�^
  MEMO        : 
===========================================================================*/
void PDControlParameter_init(PDControlParameter* this)
{
	this->pControlParameter = 0;
	this->dControlParameter = 0;
}

/*===========================================================================
  FUNCTION    : PDControlParameter_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void PDControlParameter_finish(PDControlParameter* this)
{

}

/*===========================================================================
  FUNCTION    : PDControlParameter_setParameter
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �p�����[�^����
  MEMO        : 
===========================================================================*/
void PDControlParameter_setParameter(PDControlParameter* this)
{
	int pControlParameter = (int)(this->pControlParameter * 10);
	int dControlParameter = (int)(this->dControlParameter * 10);
	
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set PParameter");
	display_goto_xy(7, 4);
	display_unsigned((U32)(pControlParameter), 0);
	display_update();
	while(0 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR))
	{
		if(1 == ecrobot_is_RUN_button_pressed()) {
			if(20 < (++pControlParameter))
			{
				pControlParameter = 20;
			}
			while(1 == ecrobot_is_RUN_button_pressed())
			{
				display_clear(1);
				display_goto_xy(7, 4);
				display_unsigned((U32)pControlParameter, 0);
				display_update();
			}
		}
		else if(1== (ecrobot_is_ENTER_button_pressed()))
		{
			if((--pControlParameter) < 0)
			{
				pControlParameter = 0;
			}
			while(1 == ecrobot_is_ENTER_button_pressed())
			{
				display_clear(1);
				display_goto_xy(7, 4);
				display_unsigned((U32)pControlParameter, 0);
				display_update();
			}
		}
	}
	this->pControlParameter = pControlParameter;
	this->pControlParameter /= 10;

	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set DParameter");
	display_goto_xy(7, 4);
	display_unsigned((U32)(dControlParameter), 0);
	display_update();
	while(0 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR))
	{
		if(1 == ecrobot_is_RUN_button_pressed()) {
			if(20 < (++dControlParameter))
			{
				dControlParameter = 20;
			}
			while(1 == ecrobot_is_RUN_button_pressed())
			{
				display_clear(1);
				display_goto_xy(7, 4);
				display_unsigned((U32)dControlParameter, 0);
				display_update();
			}
		}
		else if(1== (ecrobot_is_ENTER_button_pressed()))
		{
			if((--dControlParameter) < 0)
			{
				dControlParameter = 0;
			}
			while(1 == ecrobot_is_ENTER_button_pressed())
			{
				display_clear(1);
				display_goto_xy(7, 4);
				display_unsigned((U32)dControlParameter, 0);
				display_update();
			}
		}
	}
	this->dControlParameter = dControlParameter;
	this->dControlParameter /= 10;
}

/*===========================================================================
  FUNCTION    : PDControlParameter_getPParameter
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : P����p�����[�^���擾
  MEMO        : 
===========================================================================*/
float PDControlParameter_getPParameter(PDControlParameter* this)
{
	return (this->pControlParameter);
}

/*===========================================================================
  FUNCTION    : PDControlParameter_getDParameter
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : D����p�����[�^���擾
  MEMO        : 
===========================================================================*/
float PDControlParameter_getDParameter(PDControlParameter* this)
{
	return (this->dControlParameter);
}


