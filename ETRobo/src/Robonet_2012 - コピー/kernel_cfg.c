/*
 *  kernel_cfg.c
 *  Fri Sep 14 13:24:20 2012
 *  SG Version 2.00
 *  sg.exe ./nxt.oil -os=ECC2 -I../../ecrobot/../toppers_osek/sg/impl_oil -template=../../ecrobot/../toppers_osek/sg/lego_nxt.sgt
 */
#include "osek_kernel.h"
#include "kernel_id.h"
#include "alarm.h"
#include "interrupt.h"
#include "resource.h"
#include "task.h"

#define __STK_UNIT VP
#define __TCOUNT_STK_UNIT(sz) (((sz) + sizeof(__STK_UNIT) - 1) / sizeof(__STK_UNIT))

#define TNUM_ALARM     3
#define TNUM_COUNTER   1
#define TNUM_ISR2      0
#define TNUM_RESOURCE  0
#define TNUM_TASK      3
#define TNUM_EXTTASK   3

const UINT8 tnum_alarm    = TNUM_ALARM;
const UINT8 tnum_counter  = TNUM_COUNTER;
const UINT8 tnum_isr2     = TNUM_ISR2;
const UINT8 tnum_resource = TNUM_RESOURCE;
const UINT8 tnum_task     = TNUM_TASK;
const UINT8 tnum_exttask  = TNUM_EXTTASK;

 /****** Object OS ******/

 /****** Object TASK ******/

const TaskType RUNNING_CONTROL = 0;
const TaskType BALANCE_CONTROL = 1;
const TaskType SONAR_CONTROL = 2;

extern void TASKNAME( RUNNING_CONTROL )( void );
extern void TASKNAME( BALANCE_CONTROL )( void );
extern void TASKNAME( SONAR_CONTROL )( void );

static __STK_UNIT _stack_RUNNING_CONTROL[__TCOUNT_STK_UNIT(2560)];
static __STK_UNIT _stack_BALANCE_CONTROL[__TCOUNT_STK_UNIT(1024)];
static __STK_UNIT _stack_SONAR_CONTROL[__TCOUNT_STK_UNIT(512)];

const Priority tinib_inipri[TNUM_TASK] = { TPRI_MINTASK + 14, TPRI_MINTASK + 15, TPRI_MINTASK + 13, };
const Priority tinib_exepri[TNUM_TASK] = { TPRI_MINTASK + 14, TPRI_MINTASK + 15, TPRI_MINTASK + 13, };
const UINT8 tinib_maxact[TNUM_TASK] = { (1) - 1, (1) - 1, (1) - 1, };
const AppModeType tinib_autoact[TNUM_TASK] = { 0x00000001, 0x00000001, 0x00000001, };
const FP tinib_task[TNUM_TASK] = { TASKNAME( RUNNING_CONTROL ), TASKNAME( BALANCE_CONTROL ), TASKNAME( SONAR_CONTROL ), };
const __STK_UNIT tinib_stk[TNUM_TASK] = { (__STK_UNIT)_stack_RUNNING_CONTROL, (__STK_UNIT)_stack_BALANCE_CONTROL, (__STK_UNIT)_stack_SONAR_CONTROL, };
const UINT16 tinib_stksz[TNUM_TASK] = { 2560, 1024, 512, };

TaskType tcb_next[TNUM_TASK];
UINT8 tcb_tstat[TNUM_TASK];
Priority tcb_curpri[TNUM_TASK];
UINT8 tcb_actcnt[TNUM_TASK];
EventMaskType tcb_curevt[TNUM_EXTTASK];
EventMaskType tcb_waievt[TNUM_EXTTASK];
ResourceType tcb_lastres[TNUM_TASK];
DEFINE_CTXB(TNUM_TASK);

 /****** Object COUNTER ******/

const CounterType Cnt = 0;

const TickType cntinib_maxval[TNUM_COUNTER] = { 10000, };
const TickType cntinib_maxval2[TNUM_COUNTER] = { 20001, };
const TickType cntinib_tickbase[TNUM_COUNTER] = { 1, };
const TickType cntinib_mincyc[TNUM_COUNTER] = { 1, };

AlarmType cntcb_almque[TNUM_COUNTER];
TickType cntcb_curval[TNUM_COUNTER];

 /****** Object ALARM ******/

const AlarmType ALARM_RUNNING_CONTROL = 0;
const AlarmType ALARM_BALANCE_CONTROL = 1;
const AlarmType ALARM_SONAR_CONTROL = 2;

DeclareTask(RUNNING_CONTROL);
DeclareEvent(EVENT_RUNNING_CONTROL);
static void _setevent_alarm_ALARM_RUNNING_CONTROL( void );
static void _setevent_alarm_ALARM_RUNNING_CONTROL( void )
{ (void)SetEvent( RUNNING_CONTROL, EVENT_RUNNING_CONTROL ); }

DeclareTask(BALANCE_CONTROL);
DeclareEvent(EVENT_BALANCE_CONTROL);
static void _setevent_alarm_ALARM_BALANCE_CONTROL( void );
static void _setevent_alarm_ALARM_BALANCE_CONTROL( void )
{ (void)SetEvent( BALANCE_CONTROL, EVENT_BALANCE_CONTROL ); }

DeclareTask(SONAR_CONTROL);
DeclareEvent(EVENT_SONAR_CONTROL);
static void _setevent_alarm_ALARM_SONAR_CONTROL( void );
static void _setevent_alarm_ALARM_SONAR_CONTROL( void )
{ (void)SetEvent( SONAR_CONTROL, EVENT_SONAR_CONTROL ); }

const CounterType alminib_cntid[TNUM_ALARM] = { 0, 0, 0, };
const FP alminib_cback[TNUM_ALARM] = { _setevent_alarm_ALARM_RUNNING_CONTROL, _setevent_alarm_ALARM_BALANCE_CONTROL, _setevent_alarm_ALARM_SONAR_CONTROL, };
const AppModeType alminib_autosta[TNUM_ALARM] = { 0x00000000, 0x00000000, 0x00000000, };
const TickType alminib_almval[TNUM_ALARM] = { 0, 0, 0, };
const TickType alminib_cycle[TNUM_ALARM] = { 0, 0, 0, };

AlarmType almcb_next[TNUM_ALARM];
AlarmType almcb_prev[TNUM_ALARM];
TickType almcb_almval[TNUM_ALARM];
TickType almcb_cycle[TNUM_ALARM];

 /****** Object RESOURCE ******/


const Priority resinib_ceilpri[TNUM_RESOURCE+1] = { 0};

Priority rescb_prevpri[TNUM_RESOURCE+1];
ResourceType rescb_prevres[TNUM_RESOURCE+1];

 /****** Object EVENT ******/

const EventMaskType EVENT_RUNNING_CONTROL = (1UL << 0);
const EventMaskType EVENT_BALANCE_CONTROL = (1UL << 1);
const EventMaskType EVENT_SONAR_CONTROL = (1UL << 2);

 /****** Object ISR ******/


#define IPL_MAXISR2 0
const IPL ipl_maxisr2 = IPL_MAXISR2;


const Priority isrinib_intpri[TNUM_ISR2+1] = { 0};
ResourceType isrcb_lastres[TNUM_ISR2+1];

 /****** Object APPMODE ******/

void object_initialize( void )
{
	alarm_initialize();
	task_initialize();
}


/*
 *  TOPPERS/OSEK Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      OSEK Kernel
 * 
 *  Copyright (C) 2006 by Witz Corporation, JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 */




