#ifndef OPERATIONMETHOD_H_
#define OPERATIONMETHOD_H_
/*************************************************************************

  OperationMethod.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "CommandValue.h"


/*===========================================================================
  define
===========================================================================*/


/*===========================================================================
  ���s���@�N���X [OperationMethod]
===========================================================================*/
/* ���� */
typedef struct {
	CommandValue* commandValue; /* ���ߒl�N���X�̃|�C���^ */
} OperationMethod;

/* ���� */
void OperationMethod_init(
	OperationMethod* this,
	CommandValue* commandValue
);																	/* ���������� */
void OperationMethod_finish(OperationMethod* this);					/* �I������ */
S8 OperationMethod_executionOperationMethod(OperationMethod* this);	/* ���s */

#endif

