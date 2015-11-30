/*************************************************************************

  LineTrace.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "LineTrace.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : LineTrace_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void LineTrace_init(
	LineTrace* this,
	CourseBrightness* courseBrightness,
	CommandValue* commandValue
)
{
	/* 初期化 */
	this->courseBrightness = courseBrightness;
	OperationMethod_init(&(this->inherit_operationMethod), commandValue);
}

/*===========================================================================
  FUNCTION    : LineTrace_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void LineTrace_finish(LineTrace* this)
{

}

/*===========================================================================
  FUNCTION    : LineTrace_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : 
  MEMO        : 
===========================================================================*/
S8 LineTrace_execution(LineTrace* this, S8 speed, S16 mode)
{
	float turn; /* 旋回命令値 */
	
	/* 比例制御操作量を計算 */
	if((mode == LEFT_SMALL) || (mode == RIGHT_SMALL) || (mode == LEFT_BIG) || (mode == RIGHT_BIG))
	{
		if((mode == LEFT_SMALL) || (mode == RIGHT_SMALL))
		{
			turn = ((CourseBrightness_getThreshold(this->courseBrightness, GRAY) * 2) + (CourseBrightness_getThreshold(this->courseBrightness, WHITE))) / 3;
		}
		else
		{
			turn = ((CourseBrightness_getThreshold(this->courseBrightness, GRAY) * 2) + (CourseBrightness_getThreshold(this->courseBrightness, BLACK))) / 3;
		}
		turn -= CourseBrightness_getBrightness(this->courseBrightness);
		turn *= P_PARAM;
	}
	else
	{
		turn = (float)(CourseBrightness_getDiffEdge(this->courseBrightness)) * P_PARAM;
	}

#if 0
	/* 微分制御操作量を計算 */
	if((mode == LEFT_EDGE) || (mode == RIGHT_EDGE) || (mode == SMOOTHNESS_LEFT) || (mode == SMOOTHNESS_RIGHT) || (mode == LEFT_SMALL) || (mode == RIGHT_SMALL))
	{	
		turn += (float)(CourseBrightness_getDiffPast(this->courseBrightness)) * D_PARAM;
	}	
	turn = (((turn) >= (100)) ? (100) : (((turn) <= (-100)) ? (-100) : (turn))); /* turnの範囲は100～-100 */
	
	/* 右エッジ走行の場合旋回命令値を反転 */
	if((mode == RIGHT_EDGE) || (mode == DIFF_CTRL_OFF_RIGHT) || (mode == SMOOTHNESS_RIGHT) || (mode == RIGHT_SMALL))
	{
		turn *= -1;
	}
#endif
	
	/* 滑らか走行の場合旋回命令値を通常の3分の1にする */
	if((mode == SMOOTHNESS_LEFT) || (mode == SMOOTHNESS_RIGHT))
	{
		turn /= 3;
	}
	
	/* 微分制御操作量を計算 */
	if((mode == LEFT_EDGE) || (mode == RIGHT_EDGE) || (mode == LEFT_SMALL) || (mode == RIGHT_SMALL) || (mode == LEFT_BIG) || (mode == RIGHT_BIG))
	{	
		turn += (float)(CourseBrightness_getDiffPast(this->courseBrightness)) * D_PARAM;
	}	
	turn = (((turn) >= (100)) ? (100) : (((turn) <= (-100)) ? (-100) : (turn))); /* turnの範囲は100～-100 */
	
	/* 右エッジ走行の場合旋回命令値を反転 */
	if((mode == RIGHT_EDGE) || (mode == DIFF_CTRL_OFF_RIGHT) || (mode == RIGHT_SMALL) || (mode == RIGHT_BIG))
	{
		turn *= -1;
	}
	
	/* 命令値を設定 */
	CommandValue_setCommandValue((this->inherit_operationMethod.commandValue), (S8)turn, speed);

	return (S8)1;
}

