#ifndef RUNNINGPOSITIONINFO_H_
#define RUNNINGPOSITIONINFO_H_
/*************************************************************************

  RunningPositionInfo.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "MotorCount.h"

/*===========================================================================
  define
===========================================================================*/
#define TRED          155		/* �ԗւ̊Ԋu */
#define WHEEL_SIZE    81.6F		/* �^�C���̃T�C�Y */
#define CIRCUMFERENCE 256.224F	/* �^�C���̉~�� */
#define PI            3.14F		/* �~���� */

/*===========================================================================
  ���s�̃N���X [RunningMachine]
===========================================================================*/
/* ���� */
typedef struct {
	MotorCount* motorCount[2];	/* ���[�^��]�p�N���X�̃|�C���^ */
	float mileage;				/* ���s���� */
	float direction;			/* ���� */
#if 0
	float coordinateX;			/* x���W */
	float coordinateY;			/* y���W */
	float preCoordinateX;		/* ���O��x���W */
	float preCoordinateY;		/* ���O��y���W */
#endif
	float startMileage;			/* �헪�J�n���̑��s���� */
	float startDirection;		/* �헪�J�n���̌��� */
} RunningPositionInfo;

/* ���� */
void RunningPositionInfo_init(
	RunningPositionInfo* this,
	MotorCount* motorCountL,
	MotorCount* motorCountR
);																			/* ���������� */
void RunningPositionInfo_finish(RunningPositionInfo* this); 				/* �I������ */
void RunningPositionInfo_presumptionPosition(RunningPositionInfo* this);	/* ���Ȉʒu���� */
S32 RunningPositionInfo_getMileage(RunningPositionInfo* this);				/* ���s�����擾 */
S32 RunningPositionInfo_getStartMileage(RunningPositionInfo* this);			/* �헪�J�n���̑��s�������擾 */
S16 RunningPositionInfo_getDirection(RunningPositionInfo* this);			/* �����擾 */
S16 RunningPositionInfo_getStartDirection(RunningPositionInfo* this);		/* �헪�J�n���̌������擾 */
void RunningPositionInfo_getCoordinate(
	RunningPositionInfo* this,
	S16* coordinateX,
	S16* coordinateY
);																			/* ���W�擾 */
void RunningPositionInfo_setStartPositionInfo(RunningPositionInfo* this);	/* �헪�J�n���̑��s�ʒu����ݒ� */

#endif


