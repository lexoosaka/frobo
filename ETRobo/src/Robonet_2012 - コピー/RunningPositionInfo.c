/*************************************************************************

  RunningPositionInfo.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
/*#include <math.h> */
#include "RunningPositionInfo.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : RunningPositionInfo_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �R���X�g���N�^
  MEMO        : 
===========================================================================*/
void RunningPositionInfo_init(
	RunningPositionInfo* this,
	MotorCount* motorCountL,
	MotorCount* motorCountR
)
{
	this->motorCount[0] = motorCountL;
	this->motorCount[1] = motorCountR;
	this->mileage = 0;
	this->direction = PI;
#if 0
	this->coordinateX = 0;
	this->coordinateY = 0;
	this->preCoordinateX = 0;
	this->preCoordinateY = 0;
#endif
	this->startMileage = 0;
	this->startDirection = this->direction;
	
}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void RunningPositionInfo_finish(RunningPositionInfo* this)
{

}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_presumptionPosition
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���Ȉʒu����
  MEMO        : 
===========================================================================*/
void RunningPositionInfo_presumptionPosition(RunningPositionInfo* this)
{
	int diffMotorCountL;
	int diffMotorCountR;
	float diffDirection;          /* 2ms�O���猻�݂܂łɕϓ������p�x */
	float move;                   /* 2ms�O���猻�݂܂ł̈ړ����� */
	
	MotorCount_updateMotorCount(this->motorCount[0]); /* ��]�p�擾 */
	MotorCount_updateMotorCount(this->motorCount[1]); /* ��]�p�擾 */
	diffMotorCountL = (MotorCount_getMotorCount(this->motorCount[0])) - (MotorCount_getPastMotorCount(this->motorCount[0], 1));
	diffMotorCountR = (MotorCount_getMotorCount(this->motorCount[1])) - (MotorCount_getPastMotorCount(this->motorCount[1], 1));
	diffDirection = ((diffMotorCountR * CIRCUMFERENCE / 360) - (diffMotorCountL * CIRCUMFERENCE / 360)) / TRED; /* 2ms�O���猻�݂܂łɕϓ������p�x���v�Z */
	this->direction += diffDirection; /* ���݂̑��s�̂̊p�x���v�Z */
#if 0
	this->preCoordinateX = this->coordinateX; /* 2ms�O��x���W���X�V */
	this->preCoordinateY = this->coordinateY; /* 2ms�O��y���W���X�V */
#endif
	move = (((float)diffMotorCountL + diffMotorCountR) / 2) * CIRCUMFERENCE / 360; /* 2ms�O���猻�݂܂ł̈ړ����� */
	this->mileage += move; /* ���s�J�n�����猻�݂܂ł̈ړ��������v�Z */
#if 0
	this->coordinateX = this->preCoordinateX + move * ((float)cos((double)this->direction + (diffDirection / 2))); /* ���݈ʒu��x���W���v�Z */
	this->coordinateY = this->preCoordinateY + move * ((float)sin((double)this->direction + (diffDirection / 2))); /* ���݈ʒu��y���W���v�Z */
#endif
}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_getMileage
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���s�������擾����
  MEMO        : 
===========================================================================*/
S32 RunningPositionInfo_getMileage(RunningPositionInfo* this)
{
	return (S32)this->mileage;
}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_getStartMileage
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �헪�J�n���̑��s�������擾����
  MEMO        : 
===========================================================================*/
S32 RunningPositionInfo_getStartMileage(RunningPositionInfo* this)
{
	return (S32)this->startMileage;
}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_getDirection
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���s�������擾����
  MEMO        : 
===========================================================================*/
S16 RunningPositionInfo_getDirection(RunningPositionInfo* this)
{
	float direction = this->direction;
	
	direction = direction / PI * 180;
/*	if(direction < 0)
	{
		direction *= -1;
	}
	direction = (S16)direction % 360;
*/	
	return (S16)direction;
}

/*===========================================================================
  FUNCTION    : RunningPositionInfo_getStartDirection
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �헪�J�n���̑��s�������擾����
  MEMO        : 
===========================================================================*/
S16 RunningPositionInfo_getStartDirection(RunningPositionInfo* this)
{
	float direction = this->startDirection;
	
	direction = direction / PI * 180;
/*	if(direction < 0)
	{
		direction *= -1;
	}
	direction = (S16)direction % 360;
*/	
	return (S16)direction;
}

#if 0
/*===========================================================================
  FUNCTION    : RunningPositionInfo_getCoordinate
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���W���擾����
  MEMO        : 
===========================================================================*/
void RunningPositionInfo_getCoordinate(RunningPositionInfo* this, S16* coordinateX, S16* coordinateY)
{
	*coordinateX = (S16)this->coordinateX;
	*coordinateY = (S16)this->coordinateY;
}
#endif

/*===========================================================================
  FUNCTION    : RunningPositionInfo_setStartPositionInfo
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���s�������擾����
  MEMO        : 
===========================================================================*/
void RunningPositionInfo_setStartPositionInfo(RunningPositionInfo* this)
{
	this->startMileage = this->mileage;
	this->startDirection = this->direction;
	
	MotorCount_setStartMotorCount(this->motorCount[1]);
	MotorCount_setStartMotorCount(this->motorCount[0]);
}

