#ifndef RUNNINGMACHINE_H_
#define RUNNINGMACHINE_H_
/*************************************************************************

  RunningMachine.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "Bluetooth.h"
#include "CourseBrightness.h"
#include "RunningPositionInfo.h"
#include "Strategy.h"
#include "Pwm.h"
#include "port_define.h"


/*===========================================================================
  define
===========================================================================*/
#define SP_STRATEGY_MIN_ID 125		/* ���̒l�ȏォ��SP_STRATEGY_MAX_ID�����̏ꍇ�A����헪�����s */
#define SP_STRATEGY_MAX_ID 255		/* ���̒l��������SP_STRATEGY_MIN_ID�ȏ�̏ꍇ�A����헪�����s */

/*===========================================================================
  ���s�̃N���X [RunningMachine]
===========================================================================*/
/* ���� */
typedef struct {
	RunningPositionInfo* runningPositionInfo;	/* ���s�ʒu���N���X�̃|�C���^ */
	Bluetooth* bluetooth;				/* Bluetooth�N���X�|�C���^ */
	CourseBrightness* courseBrightness;			/* �R�[�X�P�x�l�N���X�̃|�C���^ */
	Pwm* pwm[2];								/* Pwm�l�N���X�̃|�C���^ */
	Strategy* strategy[2];						/* �헪�N���X�̃|�C���^ */
} RunningMachine;

/* ���� */
void RunningMachine_init(
	RunningMachine* this,
	RunningPositionInfo* runningPositionInfo,
	CourseBrightness* courseBrightness,
	Bluetooth* bluetooth,
	Pwm* pwmL,
	Pwm* pwmR,
	Strategy* strategy,
	Strategy* spStrategy
); 													/* ���������� */
void RunningMachine_finish(RunningMachine* this);	/* �I������ */
void RunningMachine_waitStart(RunningMachine* this, S16);/* ���s�w���҂� */
S8 RunningMachine_judgeFall(RunningMachine* this);	/* �]�|���� */
S8 RunningMachine_run(RunningMachine* this); 		/* ���s */
void RunningMachine_stop(RunningMachine* this);		/* ��~ */

#endif


