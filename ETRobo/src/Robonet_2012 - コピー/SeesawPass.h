#ifndef SEESAWPASS_H_
#define SEESAWPASS_H_
/*************************************************************************

  JudgeSeesaw.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "BlindRunning.h"
#include "MotorCount.h"
#include "Pwm.h"

/*===========================================================================
  define
===========================================================================*/
#define EXECUTIONSEESAWSTOP 	0							/* 判定関数引数、これを渡すとシーソー上で停止を試みる。 */
#define EXECUTIONSEESAWPASS 	1							/* 判定関数引数、これを渡すとシーソーを通過するだけ。 */

#define SEESAW_START_PARAM		20							/* シーソー入場時の前進命令値 */
#define SEESAW_INCR_PARAM		40							/* シーソーを見つけたときの前進値をインクリメントする間隔 */
#define SEESAW_STOP_FORWARD		50							/* シーソー上で横向き静止を試みるときの前後進命令値 */
#define SEESAW_STOP_DIG			30							/* 静止時に揺れる間隔を時間ではなくタイヤの回転角で調べるときに使う */
#define SEESAW_SQUARE_DIG		180							/* タイヤ回転角で調べるときの往復タイヤ回転角 */
#define SEESAW_SQUARE_TIME		200							/* 静止時に揺れる間隔をタイヤの回転角ではなく時間で調べるときに使う */
#define SEESAW_LEAVE_MAX		20							/* シーソーから降りるときの前後進命令最大値 */
#define SEESAW_DIFF_PARAM		3000.0F						/* シーソー微分制御パラメータ */
#define SEESAW_PROPO_PARAM		2500.0F						/* シーソー比例制御パラメータ */
#define SEESAW_INTEG_PARAM		500.0F						/* シーソー積分制御パラメータ */
#define SEESAW_MAX_FORWARD		30							/* シーソー上での前後進命令の最大値 */
#define SEESAW_MIN_FORWARD		0							/* シーソー上での前後進命令の最小値 */
#define SMOOTH_CTRL				0.020F						/* 路面が平坦なときの(角速度/PWM値) */

/*===========================================================================
  シーソー上のイベント管理クラス
===========================================================================*/
/* 属性 */
typedef struct {
	MotorCount* motorCountL;
	MotorCount* motorCountR;
	Pwm* pwmL;
	Pwm* pwmR;
	BlindRunning* blindRunning;
	U16 seesawTime;
	F32 past_param;
} SeesawPass;

/* 操作 */
void SeesawPass_init(
	SeesawPass* this,
	MotorCount*,
	MotorCount*,
	Pwm*,
	Pwm*,
	BlindRunning*;
);															/* 初期化操作 */
void SeesawPass_finish(SeesawPass* this);					/* 終了操作 */
S8 SeesawPass_execution(SeesawPass* this, S16, S16);		/* 実行 */
S8 SeesawPass_seesawNormalPass(SeesawPass* this);
S8 SeesawPass_seesawLeave(SeesawPass* this);
#endif

