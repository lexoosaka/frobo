/*************************************************************************

  JudgeTail.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "JudgeTail.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : JudgeTail_init
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �R���X�g���N�^
  MEMO        :
===========================================================================*/
void JudgeTail_init(
	JudgeTail* this,
	TailControl* tailControl
)
{
	this -> SetTailDir = 0;
	this -> tailControl = *tailControl;
	return ;

}

/*===========================================================================
  FUNCTION    : JudgeTail_finish
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �f�X�g���N�^
  MEMO        :
===========================================================================*/
void JudgeTail_finish(JudgeTail* this)
{

}

/*===========================================================================
  FUNCTION    : JudgeTail__execution
  PARAMETERS  : ���s
  RETURN      : ����l
  DESCRIPTION : �K�����ڕW�l�t�߂�
  MEMO        :
===========================================================================*/
S8 JudgeTail_execution(JudgeTail* this, S16 SetDir, S16 TailTime){
	if(TailTime == 0)
	{
//		this -> tailControl -> TailMotorInit = this -> tailControl -> TailMotorInit + SetDir;
		return 1;
	}
	return 0;
}



