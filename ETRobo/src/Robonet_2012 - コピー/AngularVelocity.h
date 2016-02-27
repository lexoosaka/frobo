#ifndef ANGULARVELOCITY_H_
#define ANGULARVELOCITY_H_
/*************************************************************************

  AngularVelocity.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "port_define.h"


/*===========================================================================
  define
===========================================================================*/
#define ANGULAR_VELOCITY_NUM 10			/* �p���x���i�[����z��̑傫�� */
#define ANGULAR_VELOCITY_MEAN_NUM 10	/* ���ϒl���i�[����z��̑傫�� */
#define ANGULAR_VELOCITY_MEAN_CYCLE 10	/* ���ϒl���i�[������� */
#define DEFAULT_OFFSET 599				/* �W���C���Z���T�I�t�Z�b�g�l�̃f�t�H���g�l */


/*===========================================================================
  �p���x�N���X [AngularVelocity]
===========================================================================*/
/* ���� */
typedef struct {
	U16 offsetValue;								/* �W���C���Z���T�I�t�Z�b�g�l */
	U16 angularVelocity[ANGULAR_VELOCITY_NUM];		/* �p���x�l���i�[����z�� */
	U16 meanAngularVelocity[ANGULAR_VELOCITY_NUM];	/* �p���x�̕��ϒl���i�[����z�� */
	U8 meanCounter;									/* ���ϒl���X�V����������J�E���g */
} AngularVelocity;

/* ���� */
void AngularVelocity_init(AngularVelocity* this);					/* ���������� */
void AngularVelocity_finish(AngularVelocity* this); 				/* �I������ */
void AngularVelocity_Calibration(AngularVelocity* this);			/* �I�t�Z�b�g�l�L�����u���[�V���� */
U16 AngularVelocity_getOffsetValue(AngularVelocity* this);			/* �I�t�Z�b�g�l�擾 */
U16 AngularVelocity_updateAngularVelocity(AngularVelocity* this);	/* �p���x�X�V */
U16 AngularVelocity_getMeanAngularVelocity(AngularVelocity* this);	/* ���ϒl���擾 */

#endif

