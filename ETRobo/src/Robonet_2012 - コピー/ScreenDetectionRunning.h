#ifndef ENIGMADECODING_H_
#define ENIGMADECODING_H_
/*************************************************************************

  ScreenDetectionRunning.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "OperationMethod.h"
#include "BlindRunning.h"
#include "CommandValue.h"
#include "SonarData.h"

/*===========================================================================
  define
===========================================================================*/
#define MINDISTANCE 60
#define SCREEN 2
#define SCREEN_A 0
#define SCREEN_B 1

/*===========================================================================
  �՗����o���s�N���X [ScreenDetectionRunning]
===========================================================================*/
/* ���� */
typedef struct {
	OperationMethod inherit_operationMethod;	/* ���s���@�N���X(�X�[�p�[�N���X) */
	BlindRunning* blindRunning;					/* �u���C���h���s�N���X�̃|�C���^ */
	SonarData* sonarData;						/* �����g�Z���T����f�[�^�N���X�̃|�C���^ */
	U8 screen[SCREEN];							/* �՗��p�^�[�����i�[ */
} ScreenDetectionRunning;

/* ���� */
void ScreenDetectionRunning_init(
	ScreenDetectionRunning* this,
	BlindRunning* blindRunning,
	CommandValue* commandValue,
	SonarData* sonarData
);														/* ���������� */
void ScreenDetectionRunning_finish(ScreenDetectionRunning* this);		/* �I������ */
S8 ScreenDetectionRunning_execution(ScreenDetectionRunning* this, S8 screenId, S16 turningRadius);	/* ���s */

#endif

