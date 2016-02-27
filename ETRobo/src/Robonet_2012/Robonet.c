/*************************************************************************

  Robonet.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "balancer.h" /* NXTway-GS C API header file */
#include "AngularVelocity.h"
#include "BalanceControl.h"
#include "BlindRunning.h"
#include "Bluetooth.h"
#include "CommandValue.h"
#include "CourseBrightness.h"
#include "JudgeBrightness.h"
#include "JudgeDirection.h"
#include "JudgeMethod.h"
#include "JudgeMileage.h"
#include "JudgeSeesaw.h"
#include "JudgeSonar.h"
#include "JudgeStepCapture.h"
#include "JudgeTail.h"
#include "LineTrace.h"
#include "Log.h"
#include "MotorCount.h"
#include "OperationMethod.h"
#include "PDControlParameter.h"
#include "port_define.h"
#include "Pwm.h"
#include "RunningMachine.h"
#include "RunningPositionInfo.h"
#include "SeesawPass.h"
#include "ScreenDetectionRunning.h"
#include "SonarData.h"
#include "StepCapture.h"
#include "Strategy.h"
#include "StrategyParam.h"
#include "TailControl.h"
#include "TailRunning.h"


/*===========================================================================
  Declare
===========================================================================*/
DeclareCounter(Cnt);					/* �^�X�N�̃J�E���^�錾 */
DeclareAlarm(ALARM_RUNNING_CONTROL);	/* ���s���@����^�X�N�̃A���[���錾 */
DeclareAlarm(ALARM_BALANCE_CONTROL);	/* �|������^�X�N�̃A���[���錾 */
DeclareAlarm(ALARM_SONAR_CONTROL);		/* �����g�Z���T����^�X�N�̃A���[���錾 */
DeclareEvent(EVENT_RUNNING_CONTROL);	/* ���s���@����^�X�N�̃C�x���g�錾 */
DeclareEvent(EVENT_BALANCE_CONTROL);	/* �|������^�X�N�̃C�x���g�錾 */
DeclareEvent(EVENT_SONAR_CONTROL);		/* �����g�Z���T����^�X�N�̃C�x���g�錾 */


/*===========================================================================
  define
===========================================================================*/
#define RUNNING_CONTROL_CYCLE 2		/* ���s���@����^�X�N�����s������� */
#define BALANCE_CONTROL_CYCLE 4		/* �|������^�X�N�����s������� */
#define SONAR_CONTROL_CYSLE 40		/* �����g�Z���T����^�X�N�����s������� */

/*===========================================================================
  global
===========================================================================*/
/* �C���X�^���X���� */
AngularVelocity angularVelocity;	/* �p���x */
CommandValue commandValue;			/* ���ߒl */
Pwm pwmL;							/* ��PWM */
Pwm pwmR;							/* �EPWM */
SonarData sonarData;				/* �����g�Z���T����f�[�^ */
Bluetooth bluetooth;
Log nxtLog; 						/* ���O */
S8 runningFlag;						/* ���s����t���O */

/* �헪�錾 */
static strategyParam runningStrategy[] =
{

		////2011�N�xET���{�R���A�E�g�R�[�X�U���p�����[�^////
		//{JUDGE_MILEAGE,40,0,BLIND_RUNNING,30,0},										//�S�[����Î~
		{JUDGE_MILEAGE,1000000,0,LINE_TRACE,20,LEFT_EDGE}				//test
		//{JUDGE_DIRECTION, 50, DIRECTION_STABILITY, LINE_TRACE, 10, LEFT_SMALL},		//���C���g���[�X_���x10_�E�G�b�W_�X�^�[�g�~�X���
		//{JUDGE_MILEAGE, 600, 0, LINE_TRACE, 100, LEFT_EDGE},								//���C���g���[�X_���x80_�E�G�b�W_�⓹����܂ő��s
		//{JUDGE_MILEAGE,2000,0,LINE_TRACE,70,LEFT_EDGE},									//���C���g���[�X_���x40_�E�G�b�W_�⓹������
	//	{JUDGE_MILEAGE,500,0,LINE_TRACE,60,LEFT_EDGE},									//���C���g���[�X_���x60_�E�G�b�W_��1�R�[�i�[�r���܂ő���
	//	{JUDGE_DIRECTION,100,DIRECTION_STABILITY,LINE_TRACE,60,LEFT_EDGE},				//���C���g���[�X_���x70_�E�G�b�W_��1�R�[�i�[�𔲂������ǂ�������
	//	{JUDGE_MILEAGE, 1000, 0, LINE_TRACE,80, LEFT_EDGE}	,							//���C���g���[�X_���x80_�E�G�b�W_���X�g���[�g���s
	//	{JUDGE_DIRECTION,188,0,LINE_TRACE,60,LEFT_EDGE},								//���C���g���[�X_���x60_�E�G�b�W_���R�[�i�[
	//	{JUDGE_DIRECTION,-150,0,LINE_TRACE,60,LEFT_EDGE},								//���C���g���[�X_���x60_�E�G�b�W_�w�A�s��
	//	{JUDGE_DIRECTION,100,DIRECTION_STABILITY,LINE_TRACE,50,LEFT_EDGE},				//���C���g���[�X_���x50_�E�G�b�W_�����R�[�i�[�𔲂������ǂ�������
		//{JUDGE_SONAR,10,0,LINE_TRACE,100,LEFT_SMALL},									//��Q���m
	//	{JUDGE_MILEAGE,150,0,BLIND_RUNNING,20,0},										//��Q���m
		//{JUDGE_TAIL,0,2,BLIND_RUNNING,10,0},											//�W���C���I�t
		//{JUDGE_MILEAGE, 50, 0,0,0,0},													//�̂�����
		//{JUDGE_TAIL,0,3,0,0,0},															//���x���Ƃ�											//�K���|��
		//{JUDGE_MILEAGE,400,0,BLIND_RUNNING,20,0},										//�Q�[�g�ʉ�
		//{JUDGE_TAIL,30,0,BLIND_RUNNING,10,0},											//�K���߂�
		//{JUDGE_TAIL,1,2,BLIND_RUNNING,10,0},											//�W���C���I��
		//{JUDGE_BRIGHTNESS,GRAY,OVER,BLIND_RUNNING,10,-125},								//�u���C���h���s_���x10_�E����_���C���T��
		//JUDGE_BRIGHTNESS,GRAY,STABILITY,LINE_TRACE,5,LEFT_EDGE},						//���C���g���[�X_���x05_�E�G�b�W_���C�����A
		//{JUDGE_MILEAGE, 2400, 0, LINE_TRACE,80, LEFT_EDGE},								//���C���g���[�X_���x60_���G�b�W_�֍s���[�g���s
		//{JUDGE_DIRECTION,100,DIRECTION_STABILITY,LINE_TRACE,50,LEFT_EDGE},				//���C���g���[�X_���x50_���G�b�W_�֍s���[�g�𔲂������ǂ�������
		//{JUDGE_MILEAGE, 850, 0, LINE_TRACE,80, LEFT_EDGE},								//���C���g���[�X_���x60_���G�b�W_�S�[���܂ő��s
		//{JUDGE_MILEAGE, 50, 0, LINE_TRACE,20, LEFT_EDGE},								//���C���g���[�X_���x60_���G�b�W_�S�[���܂ő��s
		//{JUDGE_MILEAGE,1000,0,BLIND_RUNNING,0,0}										//�S�[����Î~
}; /* �ʏ�헪 */

static strategyParam runningSPStrategy[] =
{
	{255,0,0,0,0,0}
}; /* �~�X�e���[�T�[�N���헪 */

/*===========================================================================
  FUNCTION�Fecrobot_device_initialize
  MEMO�F�f�o�C�X�������t�b�N�֐�
===========================================================================*/
void ecrobot_device_initialize(void)
{
//	ecrobot_set_bt_device_name("ET100");
	ecrobot_init_sonar_sensor(PORT_SONAR_SENSOR); /* �\�i�[�ʐM����  ������In�R�[�X�̂݁����� */
	ecrobot_init_bt_slave("T00"); /* Bluetooth�ʐM�ݒ�  ���������O�p������ */
	ecrobot_init_bt_slave(BT_PASS_KEY);	/* �X���[�u�Ƃ��ď����� */
}

/*===========================================================================
  FUNCTION�Fecrobot_device_terminate
  MEMO�FOS�V���b�g�_�E�����ɃR�[�������t�b�N�֐�
===========================================================================*/
void ecrobot_device_terminate(void)
{
//	ecrobot_set_light_sensor_inactive(PORT_LIGHT_SENSOR); /* ���Z���T�X�C�b�`OFF */
	nxt_motor_set_speed(PORT_RIGHT_MOTOR, 0, 1); /* �����[�^�[�X�g�b�v */
	nxt_motor_set_speed(PORT_LEFT_MOTOR, 0, 1); /* �E���[�^�[�X�g�b�v */
	ecrobot_term_sonar_sensor(PORT_SONAR_SENSOR); /* �\�i�[�ʐM�I��  ������In�R�[�X�̂݁����� */
	ecrobot_term_bt_connection(); /* Bluetooth�ʐM�I��  ���������O�p������*/

	systick_wait_ms(500);
}

/*===========================================================================
  FUNCTION�Fuser_1ms_isr_type2
  MEMO�F1ms�����̊��荞�݊֐�
===========================================================================*/
void user_1ms_isr_type2(void)
{
	StatusType ercd;

	ercd = SignalCounter(Cnt); /* �J�E���^�̒l��1���₷ */
	if(ercd != E_OK)
	{
		ShutdownOS(ercd); /* �G���[���N�����ꍇ�V���b�g�_�E�� */
	}
}

/*===========================================================================
  FUNCTION�FsetSPStrategy
  MEMO�F�~�X�e���[�T�[�N���I�� ���e�X�g�p ��ŏ�����
===========================================================================*/
void setSPStrategy()
{
	U8 count = 0;

	/* �f�t�H���g�l��\�� */
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set SPStrategy");
	display_goto_xy(7, 4);
	display_unsigned((U32)(runningStrategy[1].judgeId), 0);
	display_update();

	/* �擾�����l��\�� */
	while(0== (ecrobot_is_ENTER_button_pressed()))
	{
		if(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR))
		{
			count = (count + 1) % 4;
			switch(count)
			{
			case 0:
				runningStrategy[1].judgeId = PATTERN_1;
				break;
			case 1:
				runningStrategy[1].judgeId = PATTERN_2;
				break;
			case 2:
				runningStrategy[1].judgeId = PATTERN_3;
				break;
			case 3:
				runningStrategy[1].judgeId = PATTERN_4;
				break;
			default:
				break;
			}
			display_goto_xy(7, 4);
			display_unsigned((U32)(runningStrategy[1].judgeId), 0);
			display_update();
			while(1 == ecrobot_get_touch_sensor(PORT_TOUCH_SENSOR));
		}
	}
}

/*===========================================================================
  TASK�FRUNNING_CONTROL
  MEMO�F���s���@����^�X�N
        2ms�����Ŏ��s�����
===========================================================================*/
TASK(RUNNING_CONTROL)
{
	/* �C���X�^���X���� */
	BlindRunning blindRunning; /* �u���C���h���s */
	CourseBrightness courseBrightness; /* �R�[�X�P�x */
	JudgeBrightness judgeBrightness; /* �P�x���� */
	JudgeDirection judgeDirection; /* �������� */
	JudgeMarker judgeMarker;
	JudgeMileage judgeMileage; /* ���s�������� */
	JudgeSeesaw judgeSeesaw; /* �V�[�\�[���� */
	JudgeSonar judgeSonar;  /* �\�i�[���� */
	JudgeStepCapture judgeStepCapture; /* �K�i���� */
	JudgeTail judgeTail;  /* �K������ */
	LineTrace linetrace; /* ���C���g���[�X */
	MotorCount motorCountL; /* �����[�^��]�p */
	MotorCount motorCountR; /* �E���[�^��]�p */
	RunningMachine runningMachine; /* ���s�� */
	RunningPositionInfo runningPositionInfo; /* ���s��� */
	SeesawPass seesawPass;/* �V�[�\�[�ʉ� */
	ScreenDetectionRunning screenDetectionRunning; /* �՗����o���s */
	StepCapture stepCapture; /* �K�i���s */
	Strategy strategy; /* �ʏ�헪 */
	Strategy spStrategy; /* �~�X�e���[�T�[�N���헪 */
	TailControl tailControl; /* �K������ */
	runningFlag = GYRO_RUN;

	/* ���������� */
	BlindRunning_init(&blindRunning, &motorCountL, &motorCountR, &commandValue); /* �u���C���h���s */
	Bluetooth_init(&bluetooth); /* �u���C���h���s */
	CommandValue_init(&commandValue); /* ���ߒl */
	CourseBrightness_init(&courseBrightness); /* �R�[�X�P�x */
	JudgeBrightness_init(&judgeBrightness, &courseBrightness); /* �P�x���� */
	JudgeDirection_init(&judgeDirection, &runningPositionInfo); /* �������� */
	JudgeMarker_init(&judgeMarker, &courseBrightness, &runningPositionInfo);
	JudgeMileage_init(&judgeMileage, &runningPositionInfo); /* ���s�������� */
	JudgeSeesaw_init(&judgeSeesaw, &motorCountL, &motorCountR,  &pwmL, &pwmR, &judgeDirection, &judgeMileage); /* �V�[�\�[���� */
	JudgeSonar_init(&judgeSonar, &sonarData);
	JudgeStepCapture_init(&judgeStepCapture, &angularVelocity, &motorCountL, &motorCountR); /* �K�i���� */
	JudgeTail_init(&judgeTail, &tailControl);
	LineTrace_init(&linetrace, &courseBrightness, &commandValue); /* ���C���g���[�X */
	Log_init(&nxtLog, &pwmL, &pwmR, &commandValue, &courseBrightness, &runningPositionInfo, &sonarData, &motorCountL, &motorCountR); /* ���O */
	MotorCount_init(&motorCountL, PORT_LEFT_MOTOR); /* �����[�^��]�p */
	MotorCount_init(&motorCountR, PORT_RIGHT_MOTOR); /* �E���[�^��]�p */
	Pwm_init(&pwmL); /* ��PWM */
	Pwm_init(&pwmR); /* �EPWM */
	RunningMachine_init(&runningMachine, &runningPositionInfo, &courseBrightness, &bluetooth, &pwmL, &pwmR, &strategy, &spStrategy); /* ���s�� */
	RunningPositionInfo_init(&runningPositionInfo, &motorCountL, &motorCountR); /* ���s��� */
	ScreenDetectionRunning_init(&screenDetectionRunning, &blindRunning, &commandValue, &sonarData); /* �՗����o���s */
	SeesawPass_init(&seesawPass, &motorCountL, &motorCountR, &pwmL, &pwmR, &blindRunning);/* �V�[�\�[���s */
	StepCapture_init(&stepCapture, &commandValue, &judgeStepCapture, &blindRunning); /* �K�i���s */
	Strategy_init(
		&strategy, &runningPositionInfo, runningStrategy, TOTAL_STRATEGY_ID, &judgeBrightness,
		&judgeMileage, &judgeDirection, &judgeMarker, &judgeSeesaw, &judgeSonar, &judgeStepCapture, &judgeTail,
		&linetrace, &blindRunning, &screenDetectionRunning, &seesawPass, &stepCapture, &runningFlag
	); /* �ʏ�헪 */
	Strategy_init(
		&spStrategy, &runningPositionInfo, runningSPStrategy, TOTAL_SP_STRATEGY_ID, &judgeBrightness,
		&judgeMileage, &judgeDirection, &judgeMarker, &judgeSeesaw, &judgeSonar, &judgeStepCapture, &judgeTail,
		&linetrace, &blindRunning, &screenDetectionRunning, &seesawPass, &stepCapture, &runningFlag
	); /* �~�X�e���[�T�[�N���헪 */
	TailControl_init(&tailControl, PORT_TAIL_MOTOR);

//	setSPStrategy();
	ecrobot_set_light_sensor_active(PORT_LIGHT_SENSOR); /* ���Z���TLED��ON�ɂ��� */
	CourseBrightness_Calibration(&courseBrightness); /* 臒l���L�����u���[�V���� */
	TailControl_Calibration(&tailControl);			/* �K���L�����u���[�V���� */
	RunningMachine_waitStart(&runningMachine, (TailControl_Get_TailControlInit(&tailControl))); /* �^�b�`�Z���T�����҂� */

	/* �A���[����ݒ� */
	SetRelAlarm(ALARM_RUNNING_CONTROL, 1, RUNNING_CONTROL_CYCLE); /* �A���[����2msec�ɐݒ� */
	SetRelAlarm(ALARM_BALANCE_CONTROL, 2, BALANCE_CONTROL_CYCLE); /* �A���[����4msec�ɐݒ� */
	SetRelAlarm(ALARM_SONAR_CONTROL, 3, SONAR_CONTROL_CYSLE); /* �A���[����40msec�ɐݒ� */

		display_clear(1);
		display_goto_xy(0, 3);
		display_string("Excape Start");
		display_update();

	/* ���s���@���� */
	while(1)
	{
		/* �C�x���g����(�C�x���g�̓A���[���ɐݒ肵���������ƂɋN������) */
		WaitEvent(EVENT_RUNNING_CONTROL); /* �C�x���g�҂� */
		ClearEvent(EVENT_RUNNING_CONTROL); /* �C�x���g�N���A */

		/*          	�K���|��        */
		TailControl_TailOperation(&tailControl);

		/* ���s���@���� */
		if(0 == (RunningMachine_run(&runningMachine)))
		{
			/* �I������ */
			CancelAlarm(ALARM_RUNNING_CONTROL);
			CancelAlarm(ALARM_BALANCE_CONTROL);
			RunningMachine_stop(&runningMachine);
		}

	}
		display_clear(1);
		display_goto_xy(0, 3);
		display_string("EoP");
		display_update();

}

/*===========================================================================
  TASK�FBALANCE_CONTROL
  MEMO�F�|������^�X�N
        4ms�����Ŏ��s�����
===========================================================================*/
TASK(BALANCE_CONTROL)
{
	/* �C���X�^���X���� */
	BalanceControl balanceControl; /* �|������ */
	TailRunning tailRunning;		/* �K�����s */

	/* ���������� */
	AngularVelocity_init(&angularVelocity); /* �p���x */
	AngularVelocity_Calibration(&angularVelocity); /* �W���C���Z���T�I�t�Z�b�g�l�L�����u���[�V���� */
	BalanceControl_init(&balanceControl, &commandValue, &angularVelocity, &pwmL, &pwmR); /* �|������ */

	display_clear(1);
	display_goto_xy(0, 3);
	display_string("Caluclate");
	display_update();


	/* �|������ */
	while(1)
	{
		/* �C�x���g����(�C�x���g�̓A���[���ɐݒ肵���������ƂɋN������) */
		WaitEvent(EVENT_BALANCE_CONTROL);
		ClearEvent(EVENT_BALANCE_CONTROL);

		/* ���s���@���� */
		if(runningFlag == TAIL_RUN)
		{
			/* �K�����s */
			TailRunning_executionTailRunning(&tailRunning);
		}
		else if(runningFlag == GYRO_RUN)
		{
			/* �|������ */
			BalanceControl_executionBalanceRunning(&balanceControl);
		}
		else
		{
			/* �|������ */
			BalanceControl_executionBalanceRunning(&balanceControl);
		}
		/* ���O�擾 */
		Log_get(&nxtLog);
	}

}

/*===========================================================================
  TASK�FSONAR_CONTROL
  MEMO�F�����g�Z���T����^�X�N
        40ms�����Ŏ��s�����
===========================================================================*/
TASK(SONAR_CONTROL)
{
	/* ���������� */
	SonarData_init(&sonarData);

	while(1)
	{
		/* �C�x���g����(�C�x���g�̓A���[���ɐݒ肵���������ƂɋN������) */
		WaitEvent(EVENT_SONAR_CONTROL);
		ClearEvent(EVENT_SONAR_CONTROL);

		/* �����g�Z���T���� */
		SonarData_update(&sonarData);
	}
}

