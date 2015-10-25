/*************************************************************************

  OperationMethod.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "OperationMethod.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : OperationMethod_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void OperationMethod_init(
	OperationMethod* this,
	CommandValue* commandValue
)
{
	this->commandValue = commandValue;	
}

/*===========================================================================
  FUNCTION    : Strategy_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void OperationMethod_finish(OperationMethod* this)
{
	
}

/*===========================================================================
  FUNCTION    : OperationMethod_executionOperationMethod
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 戦略の実行
  MEMO        : 
===========================================================================*/
S8 OperationMethod_executionOperationMethod(OperationMethod* this)
{
	return (S8)1;
}

