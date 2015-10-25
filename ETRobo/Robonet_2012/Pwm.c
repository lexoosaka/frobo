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
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void Pwm_init(Pwm* this)
{
	int count;
	
	/* 初期化 */
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
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void Pwm_finish(Pwm* this)
{

}

/*===========================================================================
  FUNCTION    : Pwm_updatePwm
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : PWM値を更新
  MEMO        : 
===========================================================================*/
void Pwm_updatePwm(Pwm* this, signed char pwmValue)
{
	int count;
	int meanValue = 0;
	
	/* 平均値を更新はPWM_MEAN_CYCLE回に一回 */
	if(this->meanCounter == 0)
	{
		/* 平均値を格納する配列の中身を一つずつ前にずらす */
		for(count = 0; count < (PWM_MEAN_NUM - 1); count++)
		{
			this->pwmMeanValue[count] = this->pwmMeanValue[count + 1];
		}
	}
	
	/* PWM値を格納する配列の中身を一つずつ前にずらす */
	for(count = 0; count < (PWM_NUM - 1); count++)
	{
		this->pwmValue[count] = this->pwmValue[count + 1];
		
		/* 平均値を更新はPWM_MEAN_CYCLE回に一回 */
		if(this->meanCounter == 0)
		{
			/* 平均を出すために加算 */
			meanValue += (int)(this->pwmValue[count + 1]);
		}
	}
	/* 最新の値を格納 */
	this->pwmValue[PWM_NUM - 1] = pwmValue;
	
	/* 平均値を更新はPWM_MEAN_CYCLE回に一回 */
	if(this->meanCounter == 0)
	{
		/* 平均値を計算 */
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
  DESCRIPTION : PWM値を取得
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
  DESCRIPTION : 平均値を取得する
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

