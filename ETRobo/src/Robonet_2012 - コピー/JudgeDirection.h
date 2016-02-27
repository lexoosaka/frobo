#ifndef JUDGEDIRECTION_H_
#define JUDGEDIRECTION_H_
/*************************************************************************

  JudgeDirectiont.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "RunningPositionInfo.h"


/*===========================================================================
  define
===========================================================================*/
#define DIFF 0					/* JudgeDirection_execution�̔��胂�[�h�ˌ��݂̌����Ɛ헪�J�n���̌����̍��Ɣ��肵�����l���r���� */
#define ABSOLUTE 1				/* JudgeDirection_execution�̔��胂�[�h�ˑ��s�J�n������v���������Ă�������Ɣ��肵�����l���r���� */
#define DIRECTION_STABILITY 2	/* JudgeDirection_execution�̔��胂�[�h�ˊp�x�����肵�Ă��邩���聁�����ɓ��������𔻒� */
#define DIRECTION_RANGE 3		/* DIRECTION_STABILITY�Ŕ��肷��p�x�̗h�ꕝ�̋��e�l */


/*===========================================================================
  ��������N���X
===========================================================================*/
/* ���� */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	������@�N���X(�X�[�p�[�N���X) */
	RunningPositionInfo* runningPositionInfo;	/* ���s�ʒu���N���X�̃|�C���^ */
	S32 stabilityMileage;						/* ���艻�v�������̊J�n���� */
	S8 diffCount;								/* �p�x�̕ω��� */
	S16 pastDirection;							/* ���O�̊p�x */
} JudgeDirection;

/* ���� */
void JudgeDirection_init(
	JudgeDirection* this,
	RunningPositionInfo* runningPositionInfo
);																					/* ���������� */
void JudgeDirection_finish(JudgeDirection* this);									/* �I������ */
S8 JudgeDirection_execution(JudgeDirection* this, S16 targetValue, S16 mode);	/* ���s */

#endif

