#ifndef COURSEBRIGHTNESS_H_
#define COURSEBRIGHTNESS_H_
/*************************************************************************

  CourseBrightness.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "port_define.h"

/*===========================================================================
  define
===========================================================================*/
#define BRIGHTNESS_NUM 20				/* �P�x�l���i�[����z��̑傫�� */
#define BRIGHTNESS_MEAN_NUM 10			/* �P�x�l�̕��ϒl���i�[����z��̑傫�� */
#define BRIGHTNESS_MOVING_AVE_CYCLE 5 	/* �P�x�l���i�[����z��̑傫�� */
#define BRIGHTNESS_MOVING_AVE_NUM 2		/* �ړ����ϒl���i�[����z��̑傫�� */
#define BRIGHTNESS_MEAN_CYCLE 20		/* �P�x�l�̕��ϒl���i�[������� */
#define BLACK 0							/* �����Ŏw�肷��F */
#define WHITE 1							/* �����Ŏw�肷��F */
#define GRAY 2							/* �����Ŏw�肷��F */
#define WHITE_GRAY 3					/* �����Ŏw�肷��F */
#define MARKER 4						/* �����Ŏw�肷��F */
/*===========================================================================
  param
===========================================================================*/

/*===========================================================================
  �R�[�X�P�x�l�N���X [CourseBrightness]
===========================================================================*/
/* ���� */
typedef struct {
	int blackThreshold;									/* ���l */
	int whiteThreshold;									/* ���l */
	int grayThreshold;									/* �D�F(�G�b�W)�l */
	int markerThreshold;								/* �}�[�J�[���m臒l */
	int brightness[BRIGHTNESS_NUM];						/* �P�x�l���i�[ */
/*	int brightnessMovingAveValue[BRIGHTNESS_MOVING_AVE_NUM];	�ړ����ϒl���i�[ */
	int brightnessMeanValue[BRIGHTNESS_MEAN_NUM];				/* ���ϒl���i�[ */
	U8 meanCounter;
} CourseBrightness;

/* ���� */
void CourseBrightness_init(CourseBrightness* this);				/* ���������� */
void CourseBrightness_finish(CourseBrightness* this);			/* �I������ */
int CourseBrightness_updateBrightness(CourseBrightness* this);	/* �P�x�l���X�V */
int CourseBrightness_getBrightness(CourseBrightness* this);		/* �P�x�l���擾 */
int CourseBrightness_getDiffEdge(CourseBrightness* this);		/* �G�b�W�Ƃ̍����擾 */
int CourseBrightness_getDiffPast(CourseBrightness* this);		/* �ߋ��Ƃ̍����擾 */
void CourseBrightness_Calibration(CourseBrightness* this);		/* �L�����u���[�V���� */
int CourseBrightness_getThreshold(CourseBrightness* this, U8 thresholdId);		/* 臒l���擾 */
int CourseBrightness_getMeanBrightness(CourseBrightness* this);		/* ���ϒl���擾 */

#endif

