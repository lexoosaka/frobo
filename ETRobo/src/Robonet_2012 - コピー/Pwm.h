#ifndef PWM_H_
#define PWM_H_
/*************************************************************************

  Pwm.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"


/*===========================================================================
  define
===========================================================================*/
#define PWM_NUM 20		/* PWM�l���i�[����z��̑傫�� */
#define PWM_MEAN_NUM 10	/* ���ϒl���i�[����z��̑傫�� */
#define PWM_MEAN_CYCLE 40	/* ���ϒl���i�[������� */


/*===========================================================================
  Pwm�l�N���X [Pwm]
===========================================================================*/
/* ���� */
typedef struct {
	signed char pwmValue[PWM_NUM];			/* PWM�l���i�[����z�� */
	signed char pwmMeanValue[PWM_MEAN_NUM];	/* PWM�l�̕��ϒl���i�[����z�� */
	U8 meanCounter;							/* ���ϒl���擾����Ԋu���J�E���g */
} Pwm;

/* ���� */
void Pwm_init(Pwm* this);								/* ���������� */
void Pwm_finish(Pwm* this);								/* �I������ */
void Pwm_updatePwm(Pwm* this, signed char pwmValue);	/* PWM�l�̍X�V */
signed char Pwm_getPwm(Pwm* this);						/* PWM�l���擾 */
signed char Pwm_getMeanPwm(Pwm* this);					/* PWM�l�̕��ϒl���擾 */

#endif

