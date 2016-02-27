#ifndef STEPCAPTURE_H
#define STEPCAPTURE_H
/*************************************************************************

  StepCapture.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include <string.h>
#include "ecrobot_interface.h"
#include "balancer.h"
#include "CommandValue.h"
#include "OperationMethod.h"
#include "JudgeStepCapture.h"
#include "BlindRunning.h"

/*===========================================================================
  define
===========================================================================*/
#define VOLSTAN 90			// �d���l�̊�l
#define FIRSTFORWARD 40		// �K�i�ɓ���O��forward
#define FIRSTF1 30			// �헪�ړ�����forward�̏����l(GoUpStep1)
#define FIRSTF2 20			// �헪�ړ�����forward�̏����l(LevelRun1)
#define FIRSTF3 30			// �헪�ړ�����forward�̏����l(GoUpStep2)
#define FIRSTF4 20			// �헪�ړ�����forward�̏����l(LevelRun2)
#define FIRSTF5 30			// �헪�ړ�����forward�̏����l(LevelRun3)
#define LIMIT1 50			// �㏸����forward�̏��(GoUpStep1)
#define LIMIT2 30			// �㏸����forward�̏��(LevelRun1)
#define LIMIT3 55			// �㏸����forward�̏��(GoUpStep2)
#define LIMIT4 40			// �㏸����forward�̏��(LevelRun2)
#define LIMIT5 50			// �㏸����forward�̏��(LevelRun3)
#define CNT1 30				// forward�̏㏸�Ԋu(GoUpStep1)
#define CNT2 1000			// forward�̏㏸�Ԋu(LevelRun1)
#define CNT3 30				// forward�̏㏸�Ԋu(GoUpStep2)
#define CNT4 40				// forward�̏㏸�Ԋu(LevelRun2)
#define CNT5 30				// forward�̏㏸�Ԋu(LevelRun3)

/*===========================================================================
  �K�i�U���N���X [StepCapture]
===========================================================================*/
/* ���� */
typedef struct
{
	OperationMethod inherit_operationMethod;	// �ĉ��̂���
	JudgeStepCapture* judgeStepCapture; 
	BlindRunning* blindRunning;
	S8 forward;
	U32 time_cnt;			// ���Ԃ��J�E���g����
	S8 flag;				// forward�̏����l��ݒ肵�����̃t���O
	S8 shift_check;			// �헪���ڍs�������̃t���O
} StepCapture;

/* ���� */
void StepCapture_init
(
	StepCapture* this,
	CommandValue* commandValue,
	JudgeStepCapture* judgeStepCapture,
	BlindRunning* blindRunning
);
S8 StepCaptureExecution
(
	StepCapture* this,
	S8 stage,
	S16 noParam2
);
void GoUpStep1(StepCapture* this, S8 vol);
void LevelRun1(StepCapture* this);
void GoUpStep2(StepCapture* this, S8 vol);
void LevelRun2(StepCapture* this);
void LevelRun3(StepCapture* this);

#endif

