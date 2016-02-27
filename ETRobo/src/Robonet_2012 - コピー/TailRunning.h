#ifndef TAILRUNNING_H_
#define TAILRUNNING_H_
/*************************************************************************

  TailRunning.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "balancer.h"
#include "CommandValue.h"
#include "Pwm.h"
#include "TailControl.h"
#include "port_define.h"


/*===========================================================================
  define
===========================================================================*/
#define PWM_MOVE 0.625F				/* turn(���񖽗ߒl)1�ɑ΂���PWM�̕ω��� */
#define MOVE_PARAM 10 * PWM_MOVE	/* ���E�̃��[�^�ɏo�͂���PWM�̒����l */



/*===========================================================================
  �|������N���X [TailRunning]
===========================================================================*/
/* ���� */
typedef struct {
	CommandValue* commandValue;			/* ���ߒl�N���X�̃|�C���^ */
	Pwm* pwm[2];						/* PWM�N���X�̃|�C���^(���E) */
	TailControl* tailControl;
	signed char motorLeft;				/* �����[�^�o�� */
	signed char motorRight;				/* �E���[�^�o�� */
} TailRunning;

/* ���� */
void TailRunning_init(
	TailRunning* this,
	CommandValue* commandValue,
	TailControl* tailControl,
	Pwm* pwmL,
	Pwm* pwmR
);																	/* ���������� */
void TailRunning_finish(TailRunning* this);							/* �I������ */
void TailRunning_executionTailRunning(TailRunning* this);		/* �|�����s */

#endif

