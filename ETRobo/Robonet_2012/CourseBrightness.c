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
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void CourseBrightness_init(CourseBrightness* this)
{
	U8 count;
	
	/* 属性を初期化 */
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
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void CourseBrightness_finish(CourseBrightness* this)
{
	
}

/*===========================================================================
  FUNCTION    : CourseBrightness_updateBrightness
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 輝度値を更新する
  MEMO        : 
===========================================================================*/
int CourseBrightness_updateBrightness(CourseBrightness* this)
{
	U8 count;
	
	/* 移動平均を格納する配列の中を1つづつ前にずらす */
/*	for(count = 0; count < (BRIGHTNESS_MOVING_AVE_NUM - 1); count++)
	{
		this->brightnessMovingAveValue[count] = this->brightnessMovingAveValue[count + 1];
	}
	this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1] = 0;
*/	
	/* 平均値はBRIGHTNESS_MEAN_CYCLE回中に1回更新する */
	if(this->meanCounter == 0)
	{
		/* 平均値を1つずつ前にずらす */
		for(count = 0; count < (BRIGHTNESS_MEAN_NUM - 1); count++)
		{
			this->brightnessMeanValue[count] = this->brightnessMeanValue[count + 1];
		}
		this->brightnessMeanValue[BRIGHTNESS_MEAN_NUM - 1] = 0; /* 最後尾に移動平均値を計算して入れるため0にする */
	}
	
	/* 輝度値を更新する */
	for(count = 0; count < (BRIGHTNESS_NUM - 1); count++)
	{
		/* 輝度値を1つずつ前にずらす */
		this->brightness[count] = this->brightness[count + 1];
		
		/* 移動平均を計算するために最後尾からBRIGHTNESS_MOVING_AVE_CYCLE個の値を加算する */
		if((BRIGHTNESS_NUM - BRIGHTNESS_MOVING_AVE_CYCLE - 1) < count)
		{
			/* 加算 */
/*			this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1] += this->brightness[count + 1];*/
		}
		
		/* 平均値はBRIGHTNESS_MEAN_CYCLE回中に1回更新する */
		if(this->meanCounter == 0)
		{
			/* 平均値を計算するために輝度値を加算 */
			this->brightnessMeanValue[BRIGHTNESS_MEAN_NUM - 1] += this->brightness[count + 1];
		}
	}
	
	/* 最新の値を格納する */
	this->brightness[BRIGHTNESS_NUM - 1] = ecrobot_get_light_sensor(PORT_LIGHT_SENSOR);
	
	/* 最新の移動平均を計算する */
/*	this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1] += this->brightness[BRIGHTNESS_NUM - 1];
	this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1] /= BRIGHTNESS_MOVING_AVE_CYCLE;
*/	
	/* 平均値はBRIGHTNESS_MEAN_CYCLE回中に1回更新する */
	if(this->meanCounter == 0)
	{
		/* 最新の平均値を計算する */
		this->brightnessMeanValue[BRIGHTNESS_MEAN_NUM - 1] += this->brightness[BRIGHTNESS_NUM - 1];
		this->brightnessMeanValue[BRIGHTNESS_MEAN_NUM - 1] /= BRIGHTNESS_NUM;
	}
	
	/* 平均値を計算する周期をカウントする値を設定 */
	this->meanCounter = (this->meanCounter + 1) % BRIGHTNESS_MEAN_CYCLE;
	
/*	return (this->brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM - 1]);*/
	return (this->grayThreshold - this->brightness[BRIGHTNESS_NUM - 1]);
}

/*===========================================================================
  FUNCTION    : CourseBrightness_getBrightness
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 輝度値を取得する
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
  DESCRIPTION : エッジ（灰色閾値）との差を取得する
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
  DESCRIPTION : 過去との差を取得する
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
  DESCRIPTION : キャリブレーションを行う
  MEMO        : 
===========================================================================*/
void CourseBrightness_Calibration(CourseBrightness* this)
{
	U8 count;
	
	/* 黒の閾値を設定する */
	/* デフォルト値を表示する */
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set BLACK");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->blackThreshold), 0);
	display_update();
	
	/* 取得した値を表示する */
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
	
	/* 黒閾値設定終了処理 */
	systick_wait_ms(1500);
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp BLACK");
	systick_wait_ms(1500);
	
	/* 白の閾値を設定する */
	/* デフォルト値を表示する */
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set WHITE");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->whiteThreshold), 0);
	display_update();
	
	/* 取得した値を表示する */
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
	
	/* 白閾値設定終了処理 */
	systick_wait_ms(1500);
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp WHITE");
	systick_wait_ms(1500);
	
	/* 白と黒の閾値から灰色の閾値を決定し表示する */
	this->grayThreshold = (this->blackThreshold + this->whiteThreshold) / 2;
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp GLAY");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->grayThreshold), 0);
	systick_wait_ms(2500);
	display_clear(1);
	

	/* 灰色マーカーの閾値を設定する */
	/* デフォルト値を表示する */
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set MARKER");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->markerThreshold), 0);
	display_update();
	
	/* 取得した値を表示する */
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
	
	/* 白と黒の閾値から灰色の閾値を決定し表示する */
//	this->markerThreshold = (this->blackThreshold + this->markerThreshold) / 2;
	systick_wait_ms(1000);
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp MARKER");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->markerThreshold), 0);
	systick_wait_ms(1500);
	display_clear(1);

	
	
	/* 配列を灰色の閾値で初期化 */
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
  DESCRIPTION : 閾値を取得する
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
  DESCRIPTION : 平均値を取得する
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
