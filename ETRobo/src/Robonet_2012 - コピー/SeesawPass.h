#ifndef SEESAWPASS_H_
#define SEESAWPASS_H_
/*************************************************************************

  JudgeSeesaw.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "BlindRunning.h"
#include "MotorCount.h"
#include "Pwm.h"

/*===========================================================================
  define
===========================================================================*/
#define EXECUTIONSEESAWSTOP 	0							/* ����֐������A�����n���ƃV�[�\�[��Œ�~�����݂�B */
#define EXECUTIONSEESAWPASS 	1							/* ����֐������A�����n���ƃV�[�\�[��ʉ߂��邾���B */

#define SEESAW_START_PARAM		20							/* �V�[�\�[���ꎞ�̑O�i���ߒl */
#define SEESAW_INCR_PARAM		40							/* �V�[�\�[���������Ƃ��̑O�i�l���C���N�������g����Ԋu */
#define SEESAW_STOP_FORWARD		50							/* �V�[�\�[��ŉ������Î~�����݂�Ƃ��̑O��i���ߒl */
#define SEESAW_STOP_DIG			30							/* �Î~���ɗh���Ԋu�����Ԃł͂Ȃ��^�C���̉�]�p�Œ��ׂ�Ƃ��Ɏg�� */
#define SEESAW_SQUARE_DIG		180							/* �^�C����]�p�Œ��ׂ�Ƃ��̉����^�C����]�p */
#define SEESAW_SQUARE_TIME		200							/* �Î~���ɗh���Ԋu���^�C���̉�]�p�ł͂Ȃ����ԂŒ��ׂ�Ƃ��Ɏg�� */
#define SEESAW_LEAVE_MAX		20							/* �V�[�\�[����~���Ƃ��̑O��i���ߍő�l */
#define SEESAW_DIFF_PARAM		3000.0F						/* �V�[�\�[��������p�����[�^ */
#define SEESAW_PROPO_PARAM		2500.0F						/* �V�[�\�[��ᐧ��p�����[�^ */
#define SEESAW_INTEG_PARAM		500.0F						/* �V�[�\�[�ϕ�����p�����[�^ */
#define SEESAW_MAX_FORWARD		30							/* �V�[�\�[��ł̑O��i���߂̍ő�l */
#define SEESAW_MIN_FORWARD		0							/* �V�[�\�[��ł̑O��i���߂̍ŏ��l */
#define SMOOTH_CTRL				0.020F						/* �H�ʂ����R�ȂƂ���(�p���x/PWM�l) */

/*===========================================================================
  �V�[�\�[��̃C�x���g�Ǘ��N���X
===========================================================================*/
/* ���� */
typedef struct {
	MotorCount* motorCountL;
	MotorCount* motorCountR;
	Pwm* pwmL;
	Pwm* pwmR;
	BlindRunning* blindRunning;
	U16 seesawTime;
	F32 past_param;
} SeesawPass;

/* ���� */
void SeesawPass_init(
	SeesawPass* this,
	MotorCount*,
	MotorCount*,
	Pwm*,
	Pwm*,
	BlindRunning*;
);															/* ���������� */
void SeesawPass_finish(SeesawPass* this);					/* �I������ */
S8 SeesawPass_execution(SeesawPass* this, S16, S16);		/* ���s */
S8 SeesawPass_seesawNormalPass(SeesawPass* this);
S8 SeesawPass_seesawLeave(SeesawPass* this);
#endif

