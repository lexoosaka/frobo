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
  DESCRIPTION : �R���X�g���N�^
  MEMO        : 
===========================================================================*/
void CommandValue_init(CommandValue* this)
{
	/* ������������ */
	this->turn = 0;
	this->forward = 0;
}

/*===========================================================================
  FUNCTION    : CommandValue_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void CommandValue_finish(CommandValue* this)
{

}

/*===========================================================================
  FUNCTION    : CommandValue_setCommandValue
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : ���ߒl��ݒ肷��
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
  DESCRIPTION : ���񖽗ߒl���擾����
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
  DESCRIPTION : �O��i���ߒl���擾����
  MEMO        : 
===========================================================================*/
S8 CommandValue_getForward(CommandValue* this)
{
	return (this->forward);
}

