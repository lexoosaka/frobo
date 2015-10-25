/*************************************************************************

  JudgeMileage.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "JudgeMileage.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : JudgeMileage_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void JudgeMileage_init(JudgeMileage* this, RunningPositionInfo* runningPositionInfo)
{
	this->runningPositionInfo = runningPositionInfo;
}

/*===========================================================================
  FUNCTION    : JudgeMileage_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void JudgeMileage_finish(JudgeMileage* this)
{
	
}

/*===========================================================================
  FUNCTION    : JudgeMileage_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 走行距離を判定
  MEMO        : 
===========================================================================*/
S8 JudgeMileage_execution(JudgeMileage* this, S16 mileage, S16 non)
{
	if(mileage < 0)
	{
		if((mileage * -1) < ((RunningPositionInfo_getStartMileage(this->runningPositionInfo)) -
			(RunningPositionInfo_getMileage(this->runningPositionInfo))))
		{
			return 1;
		}
	}
	else
	{
		if(mileage < ((RunningPositionInfo_getMileage(this->runningPositionInfo)) -
			(RunningPositionInfo_getStartMileage(this->runningPositionInfo))))
		{
			return 1;
		}
	}
	return 0;
}

