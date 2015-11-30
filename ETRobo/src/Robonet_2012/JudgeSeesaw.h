#ifndef JUDGESEESAW_H_
#define JUDGESEESAW_H_
/*************************************************************************

  JudgeSeesaw.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "JudgeDirection.h"
#include "JudgeMileage.h"
#include "MotorCount.h"
#include "Pwm.h"

/*===========================================================================
  define
===========================================================================*/
#define JUDGESEESAWSTOP 		0							/* 判定関数引数、これを渡すとシーソー上で停止を試みる。 */
#define JUDGESEESAWPASS 		1							/* 判定関数引数、これを渡すとシーソーを通過するだけ。 */


#define SEESAW_FIND_PARAM		-10							/* シーソーを見つけるときの値 */ /*ride_flag_set内にて使用 */
#define SEESAW_RIDE_PARAM		100							/* シーソーを見つけてから乗ったと判定するためのMileageの値 */
#define SEESAW_BALANCE_POINT	130							/* シーソー上で静止のため旋回を始める位置 [deg]0:左端 */
#define SEESAW_PASS_PARAM		400							/* シーソー通過戦略時のシーソーを通過したと見るMileageの値 */
#define SEESAW_STOP_TIME		14400						/* シーソー上で停止を試みる時間 */ /* 1ms : 250 */
#define SEESAW_LEAVE_PARAM		20							/* シーソーから降りたかどうか判定するための定数 */
#define SMOOTH_CTRL				0.020F						/* 路面が平坦なときの(角速度/PWM値) */

/*===========================================================================
  シーソー上のイベント管理クラス
===========================================================================*/
/* 属性 */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	判定方法クラス(スーパークラス) */
	MotorCount* motorCountL;	/* モータ回転角左 */
	MotorCount* motorCountR;	/* モータ回転角右*/
	Pwm* pwmL;
	Pwm* pwmR;
	JudgeDirection* judgeDirection;
	JudgeMileage* judgeMileage;
	U16 seesawTime;										/* シーソー上で静止を試みた時間 */

} JudgeSeesaw;

/* 操作 */
void JudgeSeesaw_init(
	JudgeSeesaw* this,
	MotorCount* motorCountL,
	MotorCount* motorCountR,
	Pwm* pwmL,
	Pwm* pwmR,
	JudgeDirection* judgeDirection,
	JudgeMileage* judgeMileage
);																		/* 初期化操作 */
void JudgeSeesaw_finish(JudgeSeesaw* this);						/* 終了操作 */
S8 JudgeSeesaw_execution(JudgeSeesaw* this, S16, S16);	/* 実行 */
S8 JudgeSeesaw_seesawLeave(JudgeSeesaw* this);		/* シーソー退場時の前後進命令値の決定 */
S8 JudgeSeesaw_seesawNormalPass(JudgeSeesaw* this);	/* シーソーを通過するだけのときの前後進命令値の決定 */

#endif

