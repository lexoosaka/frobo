#ifndef PDCONTROLPARAMETER_H_
#define PDCONTROLPARAMETER_H_
/*************************************************************************

  PDControlParameter.h

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
  PD����p�����[�^�N���X
===========================================================================*/
/* ���� */
typedef struct {
	float pControlParameter;	/* P����p�����[�^ */
	float dControlParameter;	/* D����p�����[�^ */
} PDControlParameter;

/* ���� */
void PDControlParameter_init(PDControlParameter* this);				/* ���������� */
void PDControlParameter_finish(PDControlParameter* this);			/* �I������ */
void PDControlParameter_setParameter(PDControlParameter* this);		/* �p�����[�^�Z�b�g */
float PDControlParameter_getPParameter(PDControlParameter* this);	/* P�p�����[�^�Q�b�g */
float PDControlParameter_getDParameter(PDControlParameter* this);	/* D�p�����[�^�Q�b�g */

#endif

