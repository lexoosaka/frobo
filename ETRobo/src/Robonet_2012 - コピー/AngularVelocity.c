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
  DESCRIPTION : 初期化操作
  MEMO        : 
===========================================================================*/
void AngularVelocity_init(AngularVelocity* this)
{
	U8 count;
	
	/* 属性を初期化する */
	this->offsetValue = DEFAULT_OFFSET; /* ジャイロセンサオフセット値をデフォルト値に設定 */
	this->meanCounter = 0; /* 平均値を計算する周期をカウントする変数を初期化 */
	for(count = 0; count < ANGULAR_VELOCITY_NUM; count++)
	{
		this->angularVelocity[count] = DEFAULT_OFFSET; /* 配列をデフォルト値で初期化 */
	}
	for(count = 0; count < ANGULAR_VELOCITY_MEAN_NUM; count++)
	{
		this->meanAngularVelocity[count] = DEFAULT_OFFSET; /* 平均値の配列をデフォルト値で初期化 */
	}
}

/*===========================================================================
  FUNCTION    : AngularVelocity_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 終了操作
  MEMO        : 
===========================================================================*/
void AngularVelocity_finish(AngularVelocity* this)
{
	
}

/*===========================================================================
  FUNCTION    : AngularVelocity_Calibration
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : キャリブレーション処理
  MEMO        : 
===========================================================================*/
void AngularVelocity_Calibration(AngularVelocity* this)
{
	U8 count = 0;
	
	/* デフォルト値を表示 */
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set OFFSET");
	display_goto_xy(7, 4);
	display_unsigned((U32)(this->offsetValue), 0);
	display_update();
	
	/* 取得した値を表示 */
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
	
	/* キャリブレーション終了処理 */
	systick_wait_ms(1500);
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("comp OFFSET");
	systick_wait_ms(1500);
	display_clear(1);
	
	/* 配列を設定したジャイロセンサオフセット値で初期化 */
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
  DESCRIPTION : ジャイロセンサオフセット値を取得する
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
  DESCRIPTION : 角速度を更新する
  MEMO        : 
===========================================================================*/
U16 AngularVelocity_updateAngularVelocity(AngularVelocity* this)
{
	U8 count;
	
	/* 平均値の配列の更新はANGULAR_VELOCITY_MEAN_CYCLE回に一回 */
	if(this->meanCounter == 0)
	{
		/* 平均値の配列に格納されている値を1つずつ前にずらす */
		for(count = 0; count < (ANGULAR_VELOCITY_MEAN_NUM - 1); count++)
		{
			this->meanAngularVelocity[count] = this->meanAngularVelocity[count + 1];
		}
		this->meanAngularVelocity[ANGULAR_VELOCITY_MEAN_NUM - 1] = 0;
	}
	
	/* 角速度の配列に格納されている値を1つずつ前にずらし最新の値を最後尾に格納する */
	for(count = 0; count < (ANGULAR_VELOCITY_NUM - 1); count++)
	{
		this->angularVelocity[count] = this->angularVelocity[count + 1];
		
		/* 平均値の配列の更新はANGULAR_VELOCITY_MEAN_CYCLE回に一回 */
		if(this->meanCounter == 0)
		{
			/* 平均値を計算するために角速度の配列の値を加算していく */
			this->meanAngularVelocity[ANGULAR_VELOCITY_MEAN_NUM - 1] += this->angularVelocity[count + 1];
		}
	}
	this->angularVelocity[ANGULAR_VELOCITY_NUM - 1] = ecrobot_get_gyro_sensor(PORT_GYRO_SENSOR); /* 最新の値を取得 */
	
	/* 平均値の配列の更新はANGULAR_VELOCITY_MEAN_CYCLE回に一回 */
	if(this->meanCounter == 0)
	{
		/* 平均値を計算 */
		this->meanAngularVelocity[ANGULAR_VELOCITY_MEAN_NUM - 1] += this->angularVelocity[ANGULAR_VELOCITY_NUM - 1];
		this->meanAngularVelocity[ANGULAR_VELOCITY_MEAN_NUM - 1] /= (ANGULAR_VELOCITY_NUM);
	}
	
	/* 平均値を計算する周期をカウントする変数を設定 */
	this->meanCounter = (this->meanCounter + 1) % ANGULAR_VELOCITY_MEAN_CYCLE;
	
	return (this->angularVelocity[ANGULAR_VELOCITY_NUM - 1]);
}

/*===========================================================================
  FUNCTION    : AngularVelocity_getMeanAngularVelocity
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 平均値を取得する
  MEMO        : 
===========================================================================*/
U16 AngularVelocity_getMeanAngularVelocity(AngularVelocity* this)
{
	U8 count;
	U16 meanValue = 0;
	
	/* 平均値を計算する */
	/* 平均値の平均を出すことで長い周期の平均を計算する(周期はANGULAR_VELOCITY_MEAN_NUM * ANGULAR_VELOCITY_MEAN_CYCLE) */
	for(count = 0; count < ANGULAR_VELOCITY_MEAN_NUM; count++)
	{
		meanValue += this->meanAngularVelocity[count];
	}
	meanValue /= ANGULAR_VELOCITY_MEAN_NUM;
	
	return meanValue;
}
