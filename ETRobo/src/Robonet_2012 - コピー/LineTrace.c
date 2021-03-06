/*************************************************************************

  LineTrace.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "LineTrace.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : LineTrace_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : RXgN^
  MEMO        : 
===========================================================================*/
void LineTrace_init(
	LineTrace* this,
	CourseBrightness* courseBrightness,
	CommandValue* commandValue
	
)
{
	/* ú» */
	this->courseBrightness = courseBrightness;
	OperationMethod_init(&(this->inherit_operationMethod), commandValue);
}

/*===========================================================================
  FUNCTION    : LineTrace_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : fXgN^
  MEMO        : 
===========================================================================*/
void LineTrace_finish(LineTrace* this)
{

}

/*===========================================================================
  FUNCTION    : LineTrace_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 
  MEMO        : 
===========================================================================*/
S8 LineTrace_execution(LineTrace* this, S8 speed, S16 mode)
{
	float turn; /* ùñ½ßl */
	
	/* äá§äìÊðvZ */
	if((mode == LEFT_SMALL) || (mode == RIGHT_SMALL) || (mode == LEFT_BIG) || (mode == RIGHT_BIG))
	{
		if((mode == LEFT_SMALL) || (mode == RIGHT_SMALL))
		{
			turn = ((CourseBrightness_getThreshold(this->courseBrightness, GRAY) * 2) + (CourseBrightness_getThreshold(this->courseBrightness, WHITE))) / 3;
		}
		else
		{
			turn = ((CourseBrightness_getThreshold(this->courseBrightness, GRAY) * 2) + (CourseBrightness_getThreshold(this->courseBrightness, BLACK))) / 3;
		}
		turn -= CourseBrightness_getBrightness(this->courseBrightness);
		turn *= P_PARAM;
	}
	else
	{
		turn = (float)(CourseBrightness_getDiffEdge(this->courseBrightness)) * P_PARAM;
	}

#if 0
	/* ÷ª§äìÊðvZ */
	if((mode == LEFT_EDGE) || (mode == RIGHT_EDGE) || (mode == SMOOTHNESS_LEFT) || (mode == SMOOTHNESS_RIGHT) || (mode == LEFT_SMALL) || (mode == RIGHT_SMALL))
	{	
		turn += (float)(CourseBrightness_getDiffPast(this->courseBrightness)) * D_PARAM;
	}	
	turn = (((turn) >= (100)) ? (100) : (((turn) <= (-100)) ? (-100) : (turn))); /* turnÌÍÍÍ100`-100 */
	
	/* EGbWsÌêùñ½ßlð½] */
	if((mode == RIGHT_EDGE) || (mode == DIFF_CTRL_OFF_RIGHT) || (mode == SMOOTHNESS_RIGHT) || (mode == RIGHT_SMALL))
	{
		turn *= -1;
	}
#endif
	
	/* ç©sÌêùñ½ßlðÊíÌ3ªÌ1É·é */
	if((mode == SMOOTHNESS_LEFT) || (mode == SMOOTHNESS_RIGHT))
	{
		turn /= 3;
	}
	
	/* ÷ª§äìÊðvZ */
	if((mode == LEFT_EDGE) || (mode == RIGHT_EDGE) || (mode == LEFT_SMALL) || (mode == RIGHT_SMALL) || (mode == LEFT_BIG) || (mode == RIGHT_BIG))
	{	
		//turn += (float)(CourseBrightness_getDiffPast(this->courseBrightness)) * D_PARAM;
		//+(float)(CourseBrightness_getDiffPast(this->courseBrightness)) * D_PARAM;
		turn+=(float)(CourseBrightness_getDiffEdge(this->courseBrightness)) * P_PARAM
		+(float)(this->courseBrightness->brightness[BRIGHTNESS_NUM - 1 - 5])*0.2F+
		(float)((this->courseBrightness->brightness[BRIGHTNESS_NUM - 1 - 5]) - (this->courseBrightness->brightness[BRIGHTNESS_NUM - 1])
			-(this->courseBrightness->brightness[BRIGHTNESS_NUM - 1 - 5]) - (this->courseBrightness->brightness[BRIGHTNESS_NUM - 2]))*D_PARAM;
		//¢MVn = Kp(en-en-1) + Ki en + Kd((en-en-1) - (en-1-en-2))
	}	
	turn = (((turn) >= (100)) ? (100) : (((turn) <= (-100)) ? (-100) : (turn))); /* turnÌÍÍÍ100`-100 */
	
	/* EGbWsÌêùñ½ßlð½] */
	if((mode == RIGHT_EDGE) || (mode == DIFF_CTRL_OFF_RIGHT) || (mode == RIGHT_SMALL) || (mode == RIGHT_BIG))
	{
		turn *= -1;
	}
	
	/* ½ßlðÝè */
	CommandValue_setCommandValue((this->inherit_operationMethod.commandValue), (S8)turn, speed);

	return (S8)1;
}

