#ifndef OPERATIONMETHOD_H_
#define OPERATIONMETHOD_H_
/*************************************************************************

  OperationMethod.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "CommandValue.h"


/*===========================================================================
  define
===========================================================================*/


/*===========================================================================
  走行方法クラス [OperationMethod]
===========================================================================*/
/* 属性 */
typedef struct {
	CommandValue* commandValue; /* 命令値クラスのポインタ */
} OperationMethod;

/* 操作 */
void OperationMethod_init(
	OperationMethod* this,
	CommandValue* commandValue
);																	/* 初期化操作 */
void OperationMethod_finish(OperationMethod* this);					/* 終了操作 */
S8 OperationMethod_executionOperationMethod(OperationMethod* this);	/* 実行 */

#endif

