/*************************************************************************

  JudgeMarker.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "JudgeMarker.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : JudgeMarker_init
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : コンストラクタ
  MEMO        :
===========================================================================*/
void JudgeMarker_init(
	JudgeMarker* this,
	CourseBrightness* courseBrightness,
	RunningPositionInfo* runningPositionInfo
)
{
	this->courseBrightness = courseBrightness;
	this->runningPositionInfo = runningPositionInfo;
	this->searchStart = 0;
}

/*===========================================================================
  FUNCTION    : JudgeMarker_finish
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : デストラクタ
  MEMO        :
===========================================================================*/
void JudgeMarker_finish(JudgeMarker* this)
{

}

/*===========================================================================
  FUNCTION    : JudgeMarker_execution
  PARAMETERS  : 自分、灰色マーカーの距離、閾値レート
  RETURN      : 判定結果
  DESCRIPTION : 判定実行
  MEMO        :
===========================================================================*/
S8 JudgeMarker_execution(
	JudgeMarker* this,
	S16 targetMileage,
	S16 rate
)
{
	S8 rtn = 0;
	/* 閾値計算 */
	int threshold = (CourseBrightness_getThreshold(this -> courseBrightness, MARKER) * (rate / 100)) +
					(CourseBrightness_getThreshold(this -> courseBrightness, BLACK) * (1-(rate / 100)));

	/* 閾値を超えていないかどうか || この戦略になって初回実行かどうか*/
	if((threshold < (CourseBrightness_getBrightness(this->courseBrightness))) || this->searchStart == 0){	//超えている。
		this -> searchStart = (RunningPositionInfo_getMileage(this->runningPositionInfo));
	}else{							//超えていない
		if(targetMileage <= (RunningPositionInfo_getMileage(this->runningPositionInfo) - this -> searchStart)){ //targetMileage以上閾値以上を超えない
//		if(targetMileage =< ){ //targetMileage以上閾値以上を超えない
			rtn = 1;				//次の戦略へ
			this -> searchStart = 0;	//次回実行時のため変数初期化
		}
	}
	return rtn;
}

