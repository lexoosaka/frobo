#ifndef COMMANDVALUE_H_
#define COMMANDVALUE_H_

/*************************************************************************

  CommandValue.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"


/*===========================================================================
  define
===========================================================================*/


/*===========================================================================
  命令値クラス [CommandValue]
===========================================================================*/
/* 属性 */
typedef struct {
	S8 turn;	/* 旋回命令値 */
	S8 forward;	/* 前後進命令値 */
} CommandValue;

/* 操作 */
void CommandValue_init(CommandValue* this);									/* 初期化操作 */
void CommandValue_finish(CommandValue* this);								/* 終了操作 */
void CommandValue_setCommandValue(CommandValue* this, S8 turn, S8 forward);	/* 命令値の設定 */
S8 CommandValue_getTurn(CommandValue* this);								/* 旋回命令値取得 */
S8 CommandValue_getForward(CommandValue* this);								/* 前後進命令値取得 */

#endif

