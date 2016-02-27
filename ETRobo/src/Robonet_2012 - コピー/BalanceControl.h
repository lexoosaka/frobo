#ifndef BALANCECONTROL_H_
#define BALANCECONTROL_H_
/*************************************************************************

  BalanceControl.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "balancer.h"
#include "CommandValue.h"
#include "AngularVelocity.h"
#include "Pwm.h"
#include "port_define.h"

/*===========================================================================
  define
===========================================================================*/
#define PWM_MOVE 0.625F				/* turn(���񖽗ߒl)1�ɑ΂���PWM�̕ω��� */
#define MOVE_PARAM 10 * PWM_MOVE	/* ���E�̃��[�^�ɏo�͂���PWM�̒����l */

/*===========================================================================
  �|������N���X [BalanceControl]
===========================================================================*/
/* ���� */
typedef struct {
	CommandValue* commandValue;			/* ���ߒl�N���X�̃|�C���^ */
	AngularVelocity* angularVelocity;	/* �p���x�N���X�̃|�C���^ */
	Pwm* pwm[2];						/* PWM�N���X�̃|�C���^(���E) */
	S8 gyroFlag;						/* �|�����䂷�邩�ǂ��� */
	S8 flagSpeed;						/* �|�����䂵�Ȃ����̃��[�^�[�ɒ�o����l */
} BalanceControl;

/* ���� */
void BalanceControl_init(
	BalanceControl* this,
	CommandValue* commandValue,
	AngularVelocity* angularVelocity,
	Pwm* pwmL,
	Pwm* pwmR
);																	/* ���������� */
void BalanceControl_finish(BalanceControl* this);					/* �I������ */
void BalanceControl_executionBalanceRunning(BalanceControl* this);	/* �|�����s */

#endif

