#ifndef STRATEGY_H_
#define STRATEGY_H_
/*************************************************************************

  Strategy.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "RunningPositionInfo.h"
#include "OperationMethod.h"
#include "JudgeMethod.h"
#include "JudgeBrightness.h"
#include "JudgeMileage.h"
#include "JudgeDirection.h"
#include "JudgeBrightness.h"
#include "JudgeMarker.h"
#include "JudgeSeesaw.h"
#include "JudgeSonar.h"
#include "JudgeStepCapture.h"
#include "JudgeTail.h"
#include "LineTrace.h"
#include "BlindRunning.h"
#include "ScreenDetectionRunning.h"
#include "SeesawPass.h"
#include "StepCapture.h"
#include "StrategyParam.h"

/*===========================================================================
  define
===========================================================================*/
/* �헪���s��� */
#define RUN 0
#define INTERRUPTION 1

/* �߂�l */
#define END 0							/* �I�� */
#define CONTINUE 1						/* ���s */
#define EXECUTION_ANOTHER_STRATEGY 2	/* ����헪���s */
#define MAX_ID 124						/* �ő�ID */
#define MAX_NUM 255						/* �ő�l */

/* ���s���@�I�� */
#define TAIL_RUN 0					/* �K�����s */
#define GYRO_RUN 1					/* �|�����䑖�s */


/*===========================================================================
  �헪�N���X [Strategy]
===========================================================================*/
/* ���� */
typedef struct {
	RunningPositionInfo* runningPositionInfo;		/* ���s�ʒu���N���X�̃|�C���^ */
	JudgeBrightness* judgeBrightness;				/* �P�x����N���X�̃|�C���^ */
	JudgeMileage* judgeMileage;						/* ���s��������N���X�̃|�C���^ */
	JudgeDirection* judgeDirection;					/* ��������N���X�̃|�C���^ */
	JudgeMarker* judgeMarker;						/* �}�[�J�[����(���n)�N���X�̃|�C���^ */
	JudgeSeesaw* judgeSeesaw;						/* �V�[�\�[����N���X�̃|�C���^ */
	JudgeSonar* judgeSonar;							/* �\�i�[����N���X�̃|�C���^ */
	JudgeStepCapture* judgeStepCapture;				/* �K�i����N���X�̃|�C���^ */
	JudgeTail* judgeTail;							/* �K������N���X�̃|�C���^ */
	LineTrace* lineTrace;							/* ���C���g���[�X�N���X�̃|�C���^ */
	BlindRunning* blindRunning;						/* �u���C���h���s�N���X�̃|�C���^ */
	ScreenDetectionRunning* screenDetectionRunning;	/* �՗����o���s�N���X�̃|�C���^ */
	SeesawPass* seesawPass;							/* �V�[�\�[���s�N���X�̃|�C���^ */
	StepCapture* stepCapture;						/* �K�i���s�N���X�̃|�C���^ */
	strategyParam* strategy;						/* �헪 */
	U8 strategyId;									/* ���s���̐헪�ԍ� */
	U8 totalId;										/* �헪�̑��� */
	U8 state;
	S8* runningFlag;
} Strategy;

/* ���� */
void Strategy_init(
	Strategy* this,
	RunningPositionInfo* runningPositionInfo,
	strategyParam* strategy,
	S8 totalId,
	JudgeBrightness* judgeBrightness,
	JudgeMileage* judgeMileage,
	JudgeDirection* judgeDirection,
	JudgeMarker* judgeMarker,
	JudgeSeesaw* judgeSeesaw,
	JudgeSonar* judgeSonar,
	JudgeStepCapture* judgeStepCapture,
	JudgeTail* judgeTail,
	LineTrace* lineTrace,
	BlindRunning* blindRunning,
	ScreenDetectionRunning* screenDetectionRunning,
	SeesawPass* seesawPass,
	StepCapture* stepCapture,
	S8* runningFlag
); 													/* ���������� */
void Strategy_finish(Strategy* this);				/* �I������ */
U8 Strategy_execution(Strategy* this);				/* �헪�̎��s */
S8 Strategy_judge(Strategy* this);					/* ������@�̎��s */
S8 Strategy_operation(Strategy* this);				/* ���s���@�̎��s */
void Strategy_setStrategyId(Strategy* this, U8 id);	/* ���s����헪�̔ԍ���ݒ� */
void Strategy_setStrategy(Strategy* this, U8 id, U8 strategyId); /* �헪��ݒ�(�~�X�e���[�T�[�N����p) */

#endif

