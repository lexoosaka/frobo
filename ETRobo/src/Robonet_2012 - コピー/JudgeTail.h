#ifndef JUDGETAIL_H_
#define JUDGETAIL_H_
/*************************************************************************

  JudgeTail.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "TailControl.h"

/*===========================================================================
  define
===========================================================================*/
#define JUDGETAILSTABILITY 3
/*===========================================================================
  �K������N���X
===========================================================================*/
/* ���� */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	������@�N���X(�X�[�p�[�N���X) */
	TailControl tailControl;
	S16 SetTailDir;
} JudgeTail;

/* ���� */
void JudgeTail_init(JudgeTail* this, TailControl* tailControl);				/* ���������� */
void JudgeTail_finish(JudgeTail* this);						/* �I������ */
S8 JudgeTail_execution(JudgeTail* this, S16, S16);			/* ���s */

#endif

