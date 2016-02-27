#ifndef JUDGESTEPCAPTURE_H_
#define JUDGESTEPCAPTURE_H_
/*************************************************************************

  JudgeStepCapturet.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include <string.h>
#include "ecrobot_interface.h"
#include "balancer.h"
#include "ecrobot_interface.h"
#include "RunningPositionInfo.h"
#include "OperationMethod.h"
#include "AngularVelocity.h"
#include "motorCount.h"

/*===========================================================================
  define
===========================================================================*/
#define STEP1MEANVALUE 22				// ��i�ڂɍ����|���������𔻒f����meanValue�́��ȏ�̒l
#define STEPJUDGE1 1					// ���肵�����𔻒f����meanValue�́��ȉ��̒l
#define STEPJUDGE2 3					// ���肵�����𔻒f����meanValue�́��ȏ�̒l
#define STEP1JUDGECNT 19				// ��i�ڂ�����Ĉ��肵�����𔻒f����̂ɕK�v�ȃJ�E���g��
#define STEP2JUDGECNT 39				// ��i�ڂ�����Ĉ��肵�����𔻒f����̂ɕK�v�ȃJ�E���g��
#define TIMEJUDGE 4000					// �K�i�ɓ˓����Ă���A�K�i��ʉ߂������Ƃɂ���܂ł̎���

/*===========================================================================
  ��������N���X
===========================================================================*/
/* ���� */
typedef struct 
{
	AngularVelocity* angularVelocity;
	MotorCount* motorCount[2];
	U32 time_cnt;						// ��ɓ˓����Ă���̎��ԃJ�E���g
	U32 stab_cnt;						// ���肵�����s�����Ă��邩������ϐ�
} JudgeStepCapture;

/* ���� */
void JudgeStepCapture_init
(
	JudgeStepCapture* this,
	AngularVelocity* angularVelocity,
	MotorCount* motorCountL,
	MotorCount* motorCountR
);
void JudgeStepCapture_finish(JudgeStepCapture* this);
S8 JudgeStepCapture_BalanceCheckC(JudgeStepCapture* this);
S8 JudgeStepCapture_BalanceCheckS1(JudgeStepCapture* this);
S8 JudgeStepCapture_BalanceCheckS2(JudgeStepCapture* this);
S8 JudgeStepCapture_TimeCount(JudgeStepCapture* this, S8 flag);
S8 JudgeStepCapture_execution(
	JudgeStepCapture* this,
	S16 prm1,
	S16 prm2
);

#endif

