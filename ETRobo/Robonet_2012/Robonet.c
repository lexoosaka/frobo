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
DeclareCounter(Cnt);					/* タスクのカウンタ宣言 */
DeclareAlarm(ALARM_RUNNING_CONTROL);	/* 走行方法制御タスクのアラーム宣言 */
DeclareAlarm(ALARM_BALANCE_CONTROL);	/* 倒立制御タスクのアラーム宣言 */
DeclareAlarm(ALARM_SONAR_CONTROL);		/* 超音波センサ制御タスクのアラーム宣言 */
DeclareEvent(EVENT_RUNNING_CONTROL);	/* 走行方法制御タスクのイベント宣言 */
DeclareEvent(EVENT_BALANCE_CONTROL);	/* 倒立制御タスクのイベント宣言 */
DeclareEvent(EVENT_SONAR_CONTROL);		/* 超音波センサ制御タスクのイベント宣言 */


/*===========================================================================
  define
===========================================================================*/
#define RUNNING_CONTROL_CYCLE 2		/* 走行方法制御タスクを実行する周期 */
#define BALANCE_CONTROL_CYCLE 4		/* 倒立制御タスクを実行する周期 */
#define SONAR_CONTROL_CYSLE 40		/* 超音波センサ制御タスクを実行する周期 */

/*===========================================================================
  global
===========================================================================*/
/* インスタンス生成 */
AngularVelocity angularVelocity;	/* 角速度 */
CommandValue commandValue;			/* 命令値 */
Pwm pwmL;							/* 左PWM */
Pwm pwmR;							/* 右PWM */
SonarData sonarData;				/* 超音波センサ測定データ */
Bluetooth bluetooth;
Log nxtLog; 						/* ログ */
S8 runningFlag;						/* 走行制御フラグ */

/* 戦略宣言 */
static strategyParam runningStrategy[] =
{

		////2011年度ETロボコンアウトコース攻略パラメータ////
		{JUDGE_MILEAGE,40,0,BLIND_RUNNING,30,0},										//ゴール後静止

		{JUDGE_DIRECTION, 50, DIRECTION_STABILITY, LINE_TRACE, 10, LEFT_SMALL},		//ライントレース_速度10_右エッジ_スタートミス回避
		{JUDGE_MILEAGE, 600, 0, LINE_TRACE, 100, LEFT_EDGE},								//ライントレース_速度80_右エッジ_坂道頂上まで走行
		{JUDGE_MILEAGE,2000,0,LINE_TRACE,70,LEFT_EDGE},									//ライントレース_速度40_右エッジ_坂道を下る
	//	{JUDGE_MILEAGE,500,0,LINE_TRACE,60,LEFT_EDGE},									//ライントレース_速度60_右エッジ_第1コーナー途中まで走る
	//	{JUDGE_DIRECTION,100,DIRECTION_STABILITY,LINE_TRACE,60,LEFT_EDGE},				//ライントレース_速度70_右エッジ_第1コーナーを抜けたかどうか判定
	//	{JUDGE_MILEAGE, 1000, 0, LINE_TRACE,80, LEFT_EDGE}	,							//ライントレース_速度80_右エッジ_第二ストレート走行
	//	{JUDGE_DIRECTION,188,0,LINE_TRACE,60,LEFT_EDGE},								//ライントレース_速度60_右エッジ_第二コーナー
	//	{JUDGE_DIRECTION,-150,0,LINE_TRACE,60,LEFT_EDGE},								//ライントレース_速度60_右エッジ_ヘアピン
	//	{JUDGE_DIRECTION,100,DIRECTION_STABILITY,LINE_TRACE,50,LEFT_EDGE},				//ライントレース_速度50_右エッジ_したコーナーを抜けたかどうか判定
		{JUDGE_SONAR,10,0,LINE_TRACE,100,LEFT_SMALL},									//障害検知
	//	{JUDGE_MILEAGE,150,0,BLIND_RUNNING,20,0},										//障害検知
		{JUDGE_TAIL,0,2,BLIND_RUNNING,10,0},											//ジャイロオフ
		{JUDGE_MILEAGE, 50, 0,0,0,0},													//のけぞる
		{JUDGE_TAIL,0,3,0,0,0},															//速度落とす											//尻尾倒す
		{JUDGE_MILEAGE,400,0,BLIND_RUNNING,20,0},										//ゲート通過
		{JUDGE_TAIL,30,0,BLIND_RUNNING,10,0},											//尻尾戻す
		{JUDGE_TAIL,1,2,BLIND_RUNNING,10,0},											//ジャイロオン
		{JUDGE_BRIGHTNESS,GRAY,OVER,BLIND_RUNNING,10,-125},								//ブラインド走行_速度10_右旋回_ライン探索
		{JUDGE_BRIGHTNESS,GRAY,STABILITY,LINE_TRACE,5,LEFT_EDGE},						//ライントレース_速度05_右エッジ_ライン復帰
		{JUDGE_MILEAGE, 2400, 0, LINE_TRACE,80, LEFT_EDGE},								//ライントレース_速度60_左エッジ_蛇行ルート走行
		{JUDGE_DIRECTION,100,DIRECTION_STABILITY,LINE_TRACE,50,LEFT_EDGE},				//ライントレース_速度50_左エッジ_蛇行ルートを抜けたかどうか判定
		{JUDGE_MILEAGE, 850, 0, LINE_TRACE,80, LEFT_EDGE},								//ライントレース_速度60_左エッジ_ゴールまで走行
		{JUDGE_MILEAGE, 50, 0, LINE_TRACE,20, LEFT_EDGE},								//ライントレース_速度60_左エッジ_ゴールまで走行
		{JUDGE_MILEAGE,1000,0,BLIND_RUNNING,0,0}										//ゴール後静止
}; /* 通常戦略 */

static strategyParam runningSPStrategy[] =
{
	{255,0,0,0,0,0}
}; /* ミステリーサークル戦略 */

/*===========================================================================
  FUNCTION：ecrobot_device_initialize
  MEMO：デバイス初期化フック関数
===========================================================================*/
void ecrobot_device_initialize(void)
{
//	ecrobot_set_bt_device_name("ET100");
	ecrobot_init_sonar_sensor(PORT_SONAR_SENSOR); /* ソナー通信準備  ※※※Inコースのみ※※※ */
	ecrobot_init_bt_slave("T00"); /* Bluetooth通信設定  ※※※ログ用※※※ */
	ecrobot_init_bt_slave(BT_PASS_KEY);	/* スレーブとして初期化 */
}

/*===========================================================================
  FUNCTION：ecrobot_device_terminate
  MEMO：OSシャットダウン時にコールされるフック関数
===========================================================================*/
void ecrobot_device_terminate(void)
{
//	ecrobot_set_light_sensor_inactive(PORT_LIGHT_SENSOR); /* 光センサスイッチOFF */
	nxt_motor_set_speed(PORT_RIGHT_MOTOR, 0, 1); /* 左モーターストップ */
	nxt_motor_set_speed(PORT_LEFT_MOTOR, 0, 1); /* 右モーターストップ */
	ecrobot_term_sonar_sensor(PORT_SONAR_SENSOR); /* ソナー通信終了  ※※※Inコースのみ※※※ */
	ecrobot_term_bt_connection(); /* Bluetooth通信終了  ※※※ログ用※※※*/

	systick_wait_ms(500);
}

/*===========================================================================
  FUNCTION：user_1ms_isr_type2
  MEMO：1ms周期の割り込み関数
===========================================================================*/
void user_1ms_isr_type2(void)
{
	StatusType ercd;

	ercd = SignalCounter(Cnt); /* カウンタの値を1増やす */
	if(ercd != E_OK)
	{
		ShutdownOS(ercd); /* エラーが起きた場合シャットダウン */
	}
}

/*===========================================================================
  FUNCTION：setSPStrategy
  MEMO：ミステリーサークル選択 ※テスト用 後で消す※
===========================================================================*/
void setSPStrategy()
{
	U8 count = 0;

	/* デフォルト値を表示 */
	display_clear(1);
	display_goto_xy(0, 3);
	display_string("set SPStrategy");
	display_goto_xy(7, 4);
	display_unsigned((U32)(runningStrategy[1].judgeId), 0);
	display_update();

	/* 取得した値を表示 */
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
  TASK：RUNNING_CONTROL
  MEMO：走行方法制御タスク
        2ms周期で実行される
===========================================================================*/
TASK(RUNNING_CONTROL)
{
	/* インスタンス生成 */
	BlindRunning blindRunning; /* ブラインド走行 */
	CourseBrightness courseBrightness; /* コース輝度 */
	JudgeBrightness judgeBrightness; /* 輝度判定 */
	JudgeDirection judgeDirection; /* 向き判定 */
	JudgeMarker judgeMarker;
	JudgeMileage judgeMileage; /* 走行距離判定 */
	JudgeSeesaw judgeSeesaw; /* シーソー判定 */
	JudgeSonar judgeSonar;  /* ソナー判定 */
	JudgeStepCapture judgeStepCapture; /* 階段判定 */
	JudgeTail judgeTail;  /* 尻尾判定 */
	LineTrace linetrace; /* ライントレース */
	MotorCount motorCountL; /* 左モータ回転角 */
	MotorCount motorCountR; /* 右モータ回転角 */
	RunningMachine runningMachine; /* 走行体 */
	RunningPositionInfo runningPositionInfo; /* 走行情報 */
	SeesawPass seesawPass;/* シーソー通過 */
	ScreenDetectionRunning screenDetectionRunning; /* 衝立検出走行 */
	StepCapture stepCapture; /* 階段走行 */
	Strategy strategy; /* 通常戦略 */
	Strategy spStrategy; /* ミステリーサークル戦略 */
	TailControl tailControl; /* 尻尾制御 */
	runningFlag = GYRO_RUN;

	/* 初期化操作 */
	BlindRunning_init(&blindRunning, &motorCountL, &motorCountR, &commandValue); /* ブラインド走行 */
	Bluetooth_init(&bluetooth); /* ブラインド走行 */
	CommandValue_init(&commandValue); /* 命令値 */
	CourseBrightness_init(&courseBrightness); /* コース輝度 */
	JudgeBrightness_init(&judgeBrightness, &courseBrightness); /* 輝度判定 */
	JudgeDirection_init(&judgeDirection, &runningPositionInfo); /* 向き判定 */
	JudgeMarker_init(&judgeMarker, &courseBrightness, &runningPositionInfo);
	JudgeMileage_init(&judgeMileage, &runningPositionInfo); /* 走行距離判定 */
	JudgeSeesaw_init(&judgeSeesaw, &motorCountL, &motorCountR,  &pwmL, &pwmR, &judgeDirection, &judgeMileage); /* シーソー判定 */
	JudgeSonar_init(&judgeSonar, &sonarData);
	JudgeStepCapture_init(&judgeStepCapture, &angularVelocity, &motorCountL, &motorCountR); /* 階段判定 */
	JudgeTail_init(&judgeTail, &tailControl);
	LineTrace_init(&linetrace, &courseBrightness, &commandValue); /* ライントレース */
	Log_init(&nxtLog, &pwmL, &pwmR, &commandValue, &courseBrightness, &runningPositionInfo, &sonarData, &motorCountL, &motorCountR); /* ログ */
	MotorCount_init(&motorCountL, PORT_LEFT_MOTOR); /* 左モータ回転角 */
	MotorCount_init(&motorCountR, PORT_RIGHT_MOTOR); /* 右モータ回転角 */
	Pwm_init(&pwmL); /* 左PWM */
	Pwm_init(&pwmR); /* 右PWM */
	RunningMachine_init(&runningMachine, &runningPositionInfo, &courseBrightness, &bluetooth, &pwmL, &pwmR, &strategy, &spStrategy); /* 走行体 */
	RunningPositionInfo_init(&runningPositionInfo, &motorCountL, &motorCountR); /* 走行情報 */
	ScreenDetectionRunning_init(&screenDetectionRunning, &blindRunning, &commandValue, &sonarData); /* 衝立検出走行 */
	SeesawPass_init(&seesawPass, &motorCountL, &motorCountR, &pwmL, &pwmR, &blindRunning);/* シーソー走行 */
	StepCapture_init(&stepCapture, &commandValue, &judgeStepCapture, &blindRunning); /* 階段走行 */
	Strategy_init(
		&strategy, &runningPositionInfo, runningStrategy, TOTAL_STRATEGY_ID, &judgeBrightness,
		&judgeMileage, &judgeDirection, &judgeMarker, &judgeSeesaw, &judgeSonar, &judgeStepCapture, &judgeTail,
		&linetrace, &blindRunning, &screenDetectionRunning, &seesawPass, &stepCapture, &runningFlag
	); /* 通常戦略 */
	Strategy_init(
		&spStrategy, &runningPositionInfo, runningSPStrategy, TOTAL_SP_STRATEGY_ID, &judgeBrightness,
		&judgeMileage, &judgeDirection, &judgeMarker, &judgeSeesaw, &judgeSonar, &judgeStepCapture, &judgeTail,
		&linetrace, &blindRunning, &screenDetectionRunning, &seesawPass, &stepCapture, &runningFlag
	); /* ミステリーサークル戦略 */
	TailControl_init(&tailControl, PORT_TAIL_MOTOR);

//	setSPStrategy();
	ecrobot_set_light_sensor_active(PORT_LIGHT_SENSOR); /* 光センサLEDをONにする */
	CourseBrightness_Calibration(&courseBrightness); /* 閾値をキャリブレーション */
	TailControl_Calibration(&tailControl);			/* 尻尾キャリブレーション */
	RunningMachine_waitStart(&runningMachine, (TailControl_Get_TailControlInit(&tailControl))); /* タッチセンサ押下待ち */

	/* アラームを設定 */
	SetRelAlarm(ALARM_RUNNING_CONTROL, 1, RUNNING_CONTROL_CYCLE); /* アラームを2msecに設定 */
	SetRelAlarm(ALARM_BALANCE_CONTROL, 2, BALANCE_CONTROL_CYCLE); /* アラームを4msecに設定 */
	SetRelAlarm(ALARM_SONAR_CONTROL, 3, SONAR_CONTROL_CYSLE); /* アラームを40msecに設定 */

		display_clear(1);
		display_goto_xy(0, 3);
		display_string("Excape Start");
		display_update();

	/* 走行方法制御 */
	while(1)
	{
		/* イベント処理(イベントはアラームに設定した周期ごとに起動する) */
		WaitEvent(EVENT_RUNNING_CONTROL); /* イベント待ち */
		ClearEvent(EVENT_RUNNING_CONTROL); /* イベントクリア */

		/*          	尻尾倒立        */
		TailControl_TailOperation(&tailControl);

		/* 走行方法制御 */
		if(0 == (RunningMachine_run(&runningMachine)))
		{
			/* 終了処理 */
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
  TASK：BALANCE_CONTROL
  MEMO：倒立制御タスク
        4ms周期で実行される
===========================================================================*/
TASK(BALANCE_CONTROL)
{
	/* インスタンス生成 */
	BalanceControl balanceControl; /* 倒立制御 */
	TailRunning tailRunning;		/* 尻尾走行 */

	/* 初期化処理 */
	AngularVelocity_init(&angularVelocity); /* 角速度 */
	AngularVelocity_Calibration(&angularVelocity); /* ジャイロセンサオフセット値キャリブレーション */
	BalanceControl_init(&balanceControl, &commandValue, &angularVelocity, &pwmL, &pwmR); /* 倒立制御 */

	display_clear(1);
	display_goto_xy(0, 3);
	display_string("Caluclate");
	display_update();


	/* 倒立制御 */
	while(1)
	{
		/* イベント処理(イベントはアラームに設定した周期ごとに起動する) */
		WaitEvent(EVENT_BALANCE_CONTROL);
		ClearEvent(EVENT_BALANCE_CONTROL);

		/* 走行方法制御 */
		if(runningFlag == TAIL_RUN)
		{
			/* 尻尾走行 */
			TailRunning_executionTailRunning(&tailRunning);
		}
		else if(runningFlag == GYRO_RUN)
		{
			/* 倒立制御 */
			BalanceControl_executionBalanceRunning(&balanceControl);
		}
		else
		{
			/* 倒立制御 */
			BalanceControl_executionBalanceRunning(&balanceControl);
		}
		/* ログ取得 */
		Log_get(&nxtLog);
	}

}

/*===========================================================================
  TASK：SONAR_CONTROL
  MEMO：超音波センサ制御タスク
        40ms周期で実行される
===========================================================================*/
TASK(SONAR_CONTROL)
{
	/* 初期化処理 */
	SonarData_init(&sonarData);

	while(1)
	{
		/* イベント処理(イベントはアラームに設定した周期ごとに起動する) */
		WaitEvent(EVENT_SONAR_CONTROL);
		ClearEvent(EVENT_SONAR_CONTROL);

		/* 超音波センサ制御 */
		SonarData_update(&sonarData);
	}
}

