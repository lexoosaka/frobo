/*************************************************************************

  CommandValue.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "CommandValue.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : CommandValue_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void CommandValue_init(CommandValue* this)
{
	/* 属性を初期化 */
	this->turn = 0;
	this->forward = 0;
}

/*===========================================================================
  FUNCTION    : CommandValue_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void CommandValue_finish(CommandValue* this)
{

}

/*===========================================================================
  FUNCTION    : CommandValue_setCommandValue
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 命令値を設定する
  MEMO        : 
===========================================================================*/
void CommandValue_setCommandValue(CommandValue* this, S8 turn, S8 forward)
{
	this->turn = turn;
	this->forward = forward;	
}

/*===========================================================================
  FUNCTION    :  CommandValue_getTurn
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 旋回命令値を取得する
  MEMO        : 
===========================================================================*/
S8 CommandValue_getTurn(CommandValue* this)
{
	return (this->turn);
}

/*===========================================================================
  FUNCTION    :  CommandValue_getForward
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 前後進命令値を取得する
  MEMO        : 
===========================================================================*/
S8 CommandValue_getForward(CommandValue* this)
{
	return (this->forward);
}

