/*************************************************************************

  Log.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "Log.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : Log_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void Log_init(
	Log* this,
	Pwm* pwmL,
	Pwm* pwmR,
	CommandValue* commandValue,
	CourseBrightness* courseBrightness,
	RunningPositionInfo* runningPositionInfo,
	SonarData* sonarData,
	MotorCount* motorCountL,
	MotorCount* motorCountR
)
{
	this->pwm[0] = pwmL;
	this->pwm[1] = pwmR;
	this->commandValue = commandValue;
	this->courseBrightness = courseBrightness;
	this->runningPositionInfo = runningPositionInfo;
	this->sonarData = sonarData;
	this->motorCount[0] = motorCountL;
	this->motorCount[1] = motorCountR;
}

/*===========================================================================
  FUNCTION    : Log_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 
  MEMO        : 
===========================================================================*/
void Log_finish(Log* this)
{
	
}

/*===========================================================================
  FUNCTION    : Log_get
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ログゲット
  MEMO        : 
===========================================================================*/
void Log_get(Log* this)
{
	/* ログ出力 */
	ecrobot_bt_adc_data_logger
	(
/*		(S8)CommandValue_getTurn(this->commandValue),
		(S8)CommandValue_getForward(this->commandValue),
		(S16)Pwm_getPwm(this->pwm[0]),
		(S16)Pwm_getPwm(this->pwm[1]),
		(S16)x,
		(S16)y
*/		(S8)CommandValue_getTurn(this->commandValue),
		(S8)CommandValue_getForward(this->commandValue),
//		MotorCount_getMotorCount(this->motorCount[0]),
//		MotorCount_getMotorCount(this->motorCount[1]),
//		MotorCount_getStartMotorCount(this->motorCount[0]),
//		MotorCount_getStartMotorCount(this->motorCount[1])
		RunningPositionInfo_getStartDirection(this->runningPositionInfo),
		RunningPositionInfo_getDirection(this->runningPositionInfo),
		RunningPositionInfo_getStartMileage(this->runningPositionInfo),
//		RunningPositionInfo_getMileage(this->runningPositionInfo)
		CourseBrightness_getBrightness(this->courseBrightness)
/*		ecrobot_get_sonar_sensor(PORT_SONAR_SENSOR)*/
	);
}

