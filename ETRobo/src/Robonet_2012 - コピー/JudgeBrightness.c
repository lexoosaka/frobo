/*************************************************************************

  JudgeBrightness.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "JudgeBrightness.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : JudgeBrightness_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void JudgeBrightness_init(
	JudgeBrightness* this,
	CourseBrightness* courseBrightness
)
{
	this->courseBrightness = courseBrightness;
	this->stabilityCount = 0;
}

/*===========================================================================
  FUNCTION    : JudgeBrightness_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void JudgeBrightness_finish(JudgeBrightness* this)
{
	
}

/*===========================================================================
  FUNCTION    : JudgeBrightness_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コース輝度を判定する
  MEMO        : 
===========================================================================*/
S8 JudgeBrightness_execution(
	JudgeBrightness* this,
	S16 targetBrightness,
	S16 mode
)
{
	int meanValue; /* 平均値 */
	int black; /* 黒閾値 */
	int white; /* 白閾値 */
	int gray; /* 灰色閾値 */
	S8 rtn = 0; /* 戻り値 */
	
	/* 値を取得 */
	meanValue = CourseBrightness_getMeanBrightness(this->courseBrightness);
	black = CourseBrightness_getThreshold(this->courseBrightness, BLACK);
	white = CourseBrightness_getThreshold(this->courseBrightness, WHITE);
	gray = CourseBrightness_getThreshold(this->courseBrightness, GRAY);
	
	/* 比較値を設定 */
	switch(targetBrightness)
	{
	case BLACK:
		targetBrightness = (black + gray) / 2;
		break;
	case WHITE:
		targetBrightness = (white + gray) / 2;
		break;
	case GRAY:
		targetBrightness = gray;
	case WHITE_GRAY:
		targetBrightness = (gray * 2 + white) / 3;
		break;
	default:
		break;
	}
	
	/* 判定モードごとに判定 */
	switch(mode)
	{
	/* 比較値以上か判定 */
	case OVER:
		rtn = ((targetBrightness <= (CourseBrightness_getBrightness(this->courseBrightness))) ? (1) : (0));
		break;
	/* 比較値以下か判定 */
	case UNDER:
		rtn = (((CourseBrightness_getBrightness(this->courseBrightness)) <= targetBrightness) ? (1) : (0));
		break;
	/* 安定しているか判定 */
	case STABILITY:
		if((meanValue <= targetBrightness + RANGE) && (targetBrightness - RANGE <= meanValue))
		{
			rtn = 1;
		}
		break;
	case EDGE_CHANGE:
		this->stabilityCount++;
		if(STABILITY_COUNT < (this->stabilityCount))
		{
			this->stabilityCount = 0;
			rtn = 1;
		}
		break;
	/* コースアウトを判定 */
	case COURSEOUT:
		if(meanValue < (white + COURSEOUT_RANGE))
		{
			rtn = 1;
		}
		break;
	default:
		break;
	}
	
	return rtn;
}

