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
  ���ߒl�N���X [CommandValue]
===========================================================================*/
/* ���� */
typedef struct {
	S8 turn;	/* ���񖽗ߒl */
	S8 forward;	/* �O��i���ߒl */
} CommandValue;

/* ���� */
void CommandValue_init(CommandValue* this);									/* ���������� */
void CommandValue_finish(CommandValue* this);								/* �I������ */
void CommandValue_setCommandValue(CommandValue* this, S8 turn, S8 forward);	/* ���ߒl�̐ݒ� */
S8 CommandValue_getTurn(CommandValue* this);								/* ���񖽗ߒl�擾 */
S8 CommandValue_getForward(CommandValue* this);								/* �O��i���ߒl�擾 */

#endif

