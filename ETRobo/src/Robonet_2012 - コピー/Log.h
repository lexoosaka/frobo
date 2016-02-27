#ifndef LOG_H_
#define LOG_H_
/*************************************************************************

  Log.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "MotorCount.h"
#include "Pwm.h"
#include "CourseBrightness.h"
#include "CommandValue.h"
#include "RunningPositionInfo.h"
#include "SonarData.h"
#include "port_define.h"


/*===========================================================================
  define
===========================================================================*/


/*===========================================================================
  ログクラス [Log]
===========================================================================*/
/* 属性 */
typedef struct {
	Pwm* pwm[2];								/* Pwmクラスのポインタ */
	CommandValue* commandValue;					/* 命令値クラスのポインタ */
	RunningPositionInfo* runningPositionInfo;	/* 走行情報クラスのポインタ */
	SonarData* sonarData;						/* 超音波センサクラスのポインタ */
	MotorCount* motorCount[2];					/* モータ回転角クラスのポインタ */
	CourseBrightness* courseBrightness;			/* コース輝度値クラスのポインタ */
} Log;

/* 操作 */
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
);												/* 初期化操作 */
void Log_finish(Log* this);						/* 終了操作 */
void Log_get(Log* this);						/* ログ取得 */

#endif

