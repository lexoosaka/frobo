#ifndef JUDGEMARKER_H_
#define JUDGEMARKER_H_
/*************************************************************************

  JudgeMarker.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "CourseBrightness.h"
#include "RunningPositionInfo.h"

/*===========================================================================
  define
===========================================================================*/



/*===========================================================================
  �}�[�J�[����(�T�[�`)�N���X
===========================================================================*/
/* ���� */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	������@�N���X(�X�[�p�[�N���X) */
	CourseBrightness* courseBrightness; /* �R�[�X�P�x�N���X�̃|�C���^ */
	RunningPositionInfo* runningPositionInfo;
	S32 searchStart;					/* �Ō��臒l���ɂ����|�C���g */
} JudgeMarker;

/* ���� */
void JudgeMarker_init(
	JudgeMarker* this,
	CourseBrightness* courseBrightness,
	RunningPositionInfo* runningPositionInfo
);																						/* ���������� */
void JudgeMarker_finish(JudgeMarker* this);										/* �I������ */
S8 JudgeMarker_execution(JudgeMarker* this, S16 targetBrightness, S16 mode);	/* ���s */

#endif
