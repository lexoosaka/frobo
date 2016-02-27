#ifndef TAILCONTROL_H_
#define TAILCONTROL_H_
/*************************************************************************

  TailControl.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "port_define.h"

/*===========================================================================
  define
===========================================================================*/

/*===========================================================================
  �K���Ǘ��N���X
===========================================================================*/
/* ���� */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	������@�N���X(�X�[�p�[�N���X) */
	S16 TailMotorDir;					/* ���݂̊p�x */
	S16 TailMotorInit;					/* �L�����u���[�V�����l */
	S16 TailMotorNow;
//	S16 SetTailDir;
	U32 port;							/* ���[�^���ڑ�����Ă���|�[�g */
} TailControl;

/* ���� */
void TailControl_init(TailControl* this, U32 port);				/* ���������� */
void TailControl_finish(TailControl* this);						/* �I������ */
void TailControl_Set_TailControlDir(TailControl* this, S16);	/* ���݂̊p�x�Z�b�g */
S16 TailControl_Get_TailControlDir(TailControl* this);			/* ���݂̊p�x�擾 */
void TailControl_Set_TailControlInit(TailControl* this, S16);	/* �L�����u���[�V�������������l */
S16 TailControl_Get_TailControlInit(TailControl* this);			/* �����l�擾 */
void TailControl_Calibration(TailControl* this);				/* �L�����u���[�V���� */
void TailControl_TailOperation(TailControl* this);				/* �K������ */

#endif

