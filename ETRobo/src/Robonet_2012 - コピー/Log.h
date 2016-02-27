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
  ���O�N���X [Log]
===========================================================================*/
/* ���� */
typedef struct {
	Pwm* pwm[2];								/* Pwm�N���X�̃|�C���^ */
	CommandValue* commandValue;					/* ���ߒl�N���X�̃|�C���^ */
	RunningPositionInfo* runningPositionInfo;	/* ���s���N���X�̃|�C���^ */
	SonarData* sonarData;						/* �����g�Z���T�N���X�̃|�C���^ */
	MotorCount* motorCount[2];					/* ���[�^��]�p�N���X�̃|�C���^ */
	CourseBrightness* courseBrightness;			/* �R�[�X�P�x�l�N���X�̃|�C���^ */
} Log;

/* ���� */
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
);												/* ���������� */
void Log_finish(Log* this);						/* �I������ */
void Log_get(Log* this);						/* ���O�擾 */

#endif

