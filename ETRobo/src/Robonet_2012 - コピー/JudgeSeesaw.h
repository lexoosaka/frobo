#ifndef JUDGESEESAW_H_
#define JUDGESEESAW_H_
/*************************************************************************

  JudgeSeesaw.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "JudgeDirection.h"
#include "JudgeMileage.h"
#include "MotorCount.h"
#include "Pwm.h"

/*===========================================================================
  define
===========================================================================*/
#define JUDGESEESAWSTOP 		0							/* ����֐������A�����n���ƃV�[�\�[��Œ�~�����݂�B */
#define JUDGESEESAWPASS 		1							/* ����֐������A�����n���ƃV�[�\�[��ʉ߂��邾���B */


#define SEESAW_FIND_PARAM		-10							/* �V�[�\�[��������Ƃ��̒l */ /*ride_flag_set���ɂĎg�p */
#define SEESAW_RIDE_PARAM		100							/* �V�[�\�[�������Ă��������Ɣ��肷�邽�߂�Mileage�̒l */
#define SEESAW_BALANCE_POINT	130							/* �V�[�\�[��ŐÎ~�̂��ߐ�����n�߂�ʒu [deg]0:���[ */
#define SEESAW_PASS_PARAM		400							/* �V�[�\�[�ʉߐ헪���̃V�[�\�[��ʉ߂����ƌ���Mileage�̒l */
#define SEESAW_STOP_TIME		14400						/* �V�[�\�[��Œ�~�����݂鎞�� */ /* 1ms : 250 */
#define SEESAW_LEAVE_PARAM		20							/* �V�[�\�[����~�肽���ǂ������肷�邽�߂̒萔 */
#define SMOOTH_CTRL				0.020F						/* �H�ʂ����R�ȂƂ���(�p���x/PWM�l) */

/*===========================================================================
  �V�[�\�[��̃C�x���g�Ǘ��N���X
===========================================================================*/
/* ���� */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	������@�N���X(�X�[�p�[�N���X) */
	MotorCount* motorCountL;	/* ���[�^��]�p�� */
	MotorCount* motorCountR;	/* ���[�^��]�p�E*/
	Pwm* pwmL;
	Pwm* pwmR;
	JudgeDirection* judgeDirection;
	JudgeMileage* judgeMileage;
	U16 seesawTime;										/* �V�[�\�[��ŐÎ~�����݂����� */

} JudgeSeesaw;

/* ���� */
void JudgeSeesaw_init(
	JudgeSeesaw* this,
	MotorCount* motorCountL,
	MotorCount* motorCountR,
	Pwm* pwmL,
	Pwm* pwmR,
	JudgeDirection* judgeDirection,
	JudgeMileage* judgeMileage
);																		/* ���������� */
void JudgeSeesaw_finish(JudgeSeesaw* this);						/* �I������ */
S8 JudgeSeesaw_execution(JudgeSeesaw* this, S16, S16);	/* ���s */
S8 JudgeSeesaw_seesawLeave(JudgeSeesaw* this);		/* �V�[�\�[�ޏꎞ�̑O��i���ߒl�̌��� */
S8 JudgeSeesaw_seesawNormalPass(JudgeSeesaw* this);	/* �V�[�\�[��ʉ߂��邾���̂Ƃ��̑O��i���ߒl�̌��� */

#endif

