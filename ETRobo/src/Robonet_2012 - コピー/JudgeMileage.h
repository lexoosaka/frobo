#ifndef JUDGEMILEAGE_H_
#define JUDGEMILEAGE_H_
/*************************************************************************

  JudgeMileaget.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "RunningPositionInfo.h"


/*===========================================================================
  define
===========================================================================*/


/*===========================================================================
  ���s��������N���X
===========================================================================*/
/* ���� */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	������@�N���X(�X�[�p�[�N���X) */
	RunningPositionInfo* runningPositionInfo; /* ���s�ʒu���N���X�̃|�C���^ */
} JudgeMileage;

/* ���� */
void JudgeMileage_init(
	JudgeMileage* this,
	RunningPositionInfo* runningPositionInfo
);																		/* ���������� */
void JudgeMileage_finish(JudgeMileage* this);							/* �I������ */
S8 JudgeMileage_execution(JudgeMileage* this, S16 mileage, S16 non);	/* ���s */

#endif

