#ifndef STRATEGYPARAM_H_
#define STRATEGYPARAM_H_
/*************************************************************************

  StrategyParam.h

*************************************************************************/

/*===========================================================================
  define
===========================================================================*/
/* �헪ID */
#define TOTAL_STRATEGY_ID 15		/* �ʏ�헪�̐� */
#define TOTAL_SP_STRATEGY_ID 1		/* �~�X�e���[�T�[�N���헪�̐� */
#define MYSTERY_CIRCLE_ID 0			/* �ʏ�헪�̃~�X�e���[�T�[�N���헪�֑J�ڂ���헪�̔ԍ� */
#define PATTERN_1 125				/* �~�X�e���[�T�[�N���헪�̒ʉ߃p�^�[�� */
#define PATTERN_2 125				/* �~�X�e���[�T�[�N���헪�̒ʉ߃p�^�[�� */
#define PATTERN_3 125				/* �~�X�e���[�T�[�N���헪�̒ʉ߃p�^�[�� */
#define PATTERN_4 125				/* �~�X�e���[�T�[�N���헪�̒ʉ߃p�^�[�� */

/* ����̐� */
#define TOTAL_JUDGE_METHOD 8
#define TOTAL_OPERATION_METHOD 5

/* ������@ID */
#define JUDGE_MILEAGE 0
#define JUDGE_DIRECTION 1
#define JUDGE_BRIGHTNESS 2
#define JUDGE_SEESAW 3
#define JUDGE_STEPCAPTURE 4
#define JUDGE_TAIL 5
#define JUDGE_SONAR 6
#define JUDGE_MARKER 7


/* ���s���@ID */
#define LINE_TRACE 0
#define BLIND_RUNNING 1
#define SCREEN_DETECTION_RUNNING 2
#define STEP_CAPTURE 3
#define SEESAW_PASS 4
#define TAIL_BLIND 5

/*===========================================================================
  type
===========================================================================*/
/* �헪�\���� */
typedef struct {
	U8 judgeId;  /* ����֐�ID */
	S16 judgeParam1; /* ����֐�����1 */
	S16 judgeParam2; /* ����֐�����2 */
	U8 operationId;    /* ����֐�ID */
	S8 operationParam1;  /* ����֐�����1 */
	S16 operationParam2;  /* ����֐�����2 */
} strategyParam;


#endif
