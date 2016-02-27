#ifndef MOTORCOUNT_H_
#define MOTORCOUNT_H_
/*************************************************************************

  MotorCount.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"

/*===========================================================================
  define
===========================================================================*/
#define MOTOR_COUNT_NUM 20

/*===========================================================================
  ���[�^��]�p�N���X [MotorCount]
===========================================================================*/
/* ���� */
typedef struct {
	U32 port;						/* ���[�^���ڑ�����Ă���|�[�g */
	int motorCount[MOTOR_COUNT_NUM];	/* ���[�^��]�p���i�[����z�� */
	int startMotorCount;			/* �헪�J�n���̃��[�^��]�p */
} MotorCount;

/* ���� */
void MotorCount_init(MotorCount* this, U32 port);				/* ���������� */
void MotorCount_finish(MotorCount* this);						/* �I������ */
void MotorCount_updateMotorCount(MotorCount* this);				/* ��]�p���X�V */
int MotorCount_getMotorCount(MotorCount* this);					/* ��]�p���擾 */
int MotorCount_getPastMotorCount(MotorCount* this, U8 countId);	/* �ߋ��̉�]�p���擾 */
void MotorCount_setStartMotorCount(MotorCount* this);			/* �헪�J�n���̃��[�^��]�p��ݒ� */
int MotorCount_getStartMotorCount(MotorCount* this);			/* �헪�J�n���̃��[�^��]�p���擾 */

#endif

