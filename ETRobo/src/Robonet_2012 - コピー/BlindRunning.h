#ifndef BLINDRUNNING_H_
#define BLINDRUNNING_H_
/*************************************************************************

  BlindRunning.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "OperationMethod.h"
#include "MotorCount.h"
#include "CommandValue.h"
#include "RunningPositionInfo.h"


/*===========================================================================
  define
===========================================================================*/


/*===========================================================================
  �u���C���h���s�N���X [BlindRunning]
===========================================================================*/
/* ���� */
typedef struct {
	OperationMethod inherit_operationMethod;	/* ���s���@�N���X(�X�[�p�[�N���X) */
	MotorCount* motorCount[2];					/* ���[�^��]�p�N���X�̃|�C���^(���E) */
}BlindRunning;

/* ���� */
void BlindRunning_init(
	BlindRunning* this,
	MotorCount* motorCountL,
	MotorCount* motorCountR,
	CommandValue* commandValue
);																			/* ���������� */
void BlindRunning_finish(BlindRunning* this);								/* �I������ */
S8 BlindRunning_execution(BlindRunning* this, S8 speed, S16 turningRadius);	/* ���s */

#endif

