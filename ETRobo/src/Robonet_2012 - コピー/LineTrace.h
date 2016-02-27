#ifndef LINETRACE_H_
#define LINETRACE_H_
/*************************************************************************

  LineTrace.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "OperationMethod.h"
#include "CourseBrightness.h"
#include "CommandValue.h"


/*===========================================================================
  define
===========================================================================*/
#define LEFT_EDGE 0				/* ���G�b�W�𑖍s */
#define RIGHT_EDGE 1			/* �E�G�b�W�𑖍s */
#define DIFF_CTRL_OFF_LEFT 2	/* ���G�b�W�𑖍s(��ᐧ��̂�) */
#define DIFF_CTRL_OFF_RIGHT 3	/* �E�G�b�W�𑖍s(��ᐧ��̂�) */
#define LEFT_SMALL 4			/* �ڕW�l���������������C���g���[�X */
#define RIGHT_SMALL 5			/* �ڕW�l���������������C���g���[�X */
#define LEFT_BIG 6			/* �ڕW�l���������������C���g���[�X */
#define RIGHT_BIG 7			/* �ڕW�l���������������C���g���[�X */
#define SMOOTHNESS_LEFT 8		/* ����ʂ�}�������G�b�W���s */
#define SMOOTHNESS_RIGHT 9		/* ����ʂ�}�����E�G�b�W���s */
#define P_PARAM 1.2F			/* ��ᐧ��p�����[�^ */
#define D_PARAM 4.0F			/* ��������p�����[�^ */


/*===========================================================================
  ���C���g���[�X�N���X [LineTrace]
===========================================================================*/
/* ���� */
typedef struct {
	OperationMethod inherit_operationMethod;		/* ���s���@�N���X(�X�[�p�[�N���X) */
	CourseBrightness* courseBrightness;				/* �R�[�X�P�x�N���X�̃|�C���^ */
} LineTrace;

/* ���� */
void LineTrace_init(
	LineTrace* this,
	CourseBrightness* courseBrightness,
	CommandValue* commandValue
);															/* ���������� */
void LineTrace_finish(LineTrace* this);						/* �I������ */
S8 LineTrace_execution(LineTrace* this, S8 speed, S16 mode);	/* ���s */

#endif

