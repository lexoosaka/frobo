#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
/*************************************************************************

  Bluetooth.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"


/*===========================================================================
  define
===========================================================================*/
#define BT_PASS_KEY		"1234"	/* bluetoothパスキー */
#define BT_RCV_BUF_SIZE 32		/* bluetooth受信パケットの大きさ */
/*===========================================================================
  尻尾判定クラス
===========================================================================*/
/* 属性 */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	判定方法クラス(スーパークラス) */
	U32 bt_receive_buf[BT_RCV_BUF_SIZE];
} Bluetooth;

/* 操作 */
void Bluetooth_init(Bluetooth* this);				/* 初期化操作 */
void Bluetooth_finish(Bluetooth* this);						/* 終了操作 */
void Bluetooth_execution(Bluetooth* this);			/* 実行 */
S8 Bluetooth_waitStart(Bluetooth* this);
#endif

