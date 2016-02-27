/*************************************************************************

  MotorCount.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "MotorCount.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : MotorCount_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �R���X�g���N�^
  MEMO        : 
===========================================================================*/
void MotorCount_init(MotorCount* this, U32 port)
{
	int count;
	
	/* ������ */
	for(count = 0; count < MOTOR_COUNT_NUM; count++)
	{
		this->motorCount[count] = 0;
	}
	this->port = port;
	this->startMotorCount = 0;
}

/*===========================================================================
  FUNCTION    : MotorCount_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void MotorCount_finish(MotorCount* this)
{
	
}

/*===========================================================================
  FUNCTION    : MotorCount_updateMotorCount
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���[�^��]�p���X�V
  MEMO        : 
===========================================================================*/
void MotorCount_updateMotorCount(MotorCount* this)
{
	int count;
	
	/* 1���O�ɂ��炵�čŐV�̒l���Ō���Ɋi�[ */
	for(count = 0; count < (MOTOR_COUNT_NUM - 1); count++)
	{
		this->motorCount[count] = this->motorCount[count + 1];
	}
	this->motorCount[MOTOR_COUNT_NUM - 1] = nxt_motor_get_count(this->port);
}

/*===========================================================================
  FUNCTION    : MotorCount_getMotorCount
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���[�^��]�p���擾
  MEMO        : 
===========================================================================*/
int MotorCount_getMotorCount(MotorCount* this)
{
	return (this->motorCount[MOTOR_COUNT_NUM - 1]);
}

/*===========================================================================
  FUNCTION    : MotorCount_getPastMotorCount
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �ߋ��̃��[�^��]�p���擾
  MEMO        : 
===========================================================================*/
int MotorCount_getPastMotorCount(MotorCount* this, U8 countId)
{
	if((MOTOR_COUNT_NUM - 1) < countId)
	{
		countId = (MOTOR_COUNT_NUM - 1);
	}
	
	return (this->motorCount[MOTOR_COUNT_NUM - 1 - countId]);
}

/*===========================================================================
  FUNCTION    : MotorCount_setStartMotorCount
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �헪�J�n���̉�]�p��ݒ�
  MEMO        : 
===========================================================================*/
void MotorCount_setStartMotorCount(MotorCount* this)
{
	this->startMotorCount = (this->motorCount[MOTOR_COUNT_NUM - 1]);
}

/*===========================================================================
  FUNCTION    : MotorCount_getStartMotorCount
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �헪�J�n���̉�]�p���擾
  MEMO        : 
===========================================================================*/
int MotorCount_getStartMotorCount(MotorCount* this)
{
	return (this->startMotorCount);
}

