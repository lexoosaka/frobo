#ifndef ENIGMADECODING_H_
#define ENIGMADECODING_H_
/*************************************************************************

  ScreenDetectionRunning.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "OperationMethod.h"
#include "BlindRunning.h"
#include "CommandValue.h"
#include "SonarData.h"

/*===========================================================================
  define
===========================================================================*/
#define MINDISTANCE 60
#define SCREEN 2
#define SCREEN_A 0
#define SCREEN_B 1

/*===========================================================================
  衝立検出走行クラス [ScreenDetectionRunning]
===========================================================================*/
/* 属性 */
typedef struct {
	OperationMethod inherit_operationMethod;	/* 走行方法クラス(スーパークラス) */
	BlindRunning* blindRunning;					/* ブラインド走行クラスのポインタ */
	SonarData* sonarData;						/* 超音波センサ測定データクラスのポインタ */
	U8 screen[SCREEN];							/* 衝立パターンを格納 */
} ScreenDetectionRunning;

/* 操作 */
void ScreenDetectionRunning_init(
	ScreenDetectionRunning* this,
	BlindRunning* blindRunning,
	CommandValue* commandValue,
	SonarData* sonarData
);														/* 初期化操作 */
void ScreenDetectionRunning_finish(ScreenDetectionRunning* this);		/* 終了操作 */
S8 ScreenDetectionRunning_execution(ScreenDetectionRunning* this, S8 screenId, S16 turningRadius);	/* 実行 */

#endif

