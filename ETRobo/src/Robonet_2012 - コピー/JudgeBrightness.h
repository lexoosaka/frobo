#ifndef JUDGEBRIGHTNESS_H_
#define JUDGEBRIGHTNESS_H_
/*************************************************************************

  JudgeBrightness.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "CourseBrightness.h"


/*===========================================================================
  define
===========================================================================*/
#define OVER 0		/* JudgeBrightness_execution�̔��胂�[�h�˒l�ȏ�ɂȂ��������� */
#define UNDER 1		/* JudgeBrightness_execution�̔��胂�[�h�˒l�ȉ��ɂȂ��������� */
#define STABILITY 2	/* JudgeBrightness_execution�̔��胂�[�h�ˈ��肵�Ă��邩���� */
#define COURSEOUT 3	/* JudgeBrightness_execution�̔��胂�[�h�˃R�[�X�A�E�g�𔻒� */
#define EDGE_CHANGE 4
#define RANGE 3		/* JudgeBrightness_execution�ň���x�𔻒肷��ꍇ�́A�l�̗h��̃v���X�}�C�i�X�����̋��e�͈� */
#define COURSEOUT_RANGE 10
#define STABILITY_COUNT 250


/*===========================================================================
  �P�x����N���X
===========================================================================*/
/* ���� */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	������@�N���X(�X�[�p�[�N���X) */
	CourseBrightness* courseBrightness; /* �R�[�X�P�x�N���X�̃|�C���^ */
	U16 stabilityCount;
} JudgeBrightness;

/* ���� */
void JudgeBrightness_init(
	JudgeBrightness* this,
	CourseBrightness* courseBrightness
);																						/* ���������� */
void JudgeBrightness_finish(JudgeBrightness* this);										/* �I������ */
S8 JudgeBrightness_execution(JudgeBrightness* this, S16 targetBrightness, S16 mode);	/* ���s */

#endif

