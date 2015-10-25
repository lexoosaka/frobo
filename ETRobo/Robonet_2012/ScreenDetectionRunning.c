/*************************************************************************

  ScreenDetectionRunning.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "ScreenDetectionRunning.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : ScreenDetectionRunning_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : コンストラクタ
  MEMO        : 
===========================================================================*/
void ScreenDetectionRunning_init(
	ScreenDetectionRunning* this,
	BlindRunning* blindRunning,
	CommandValue* commandValue,
	SonarData* sonarData
)
{
	U8 count;
	
	/* 属性を初期化 */
	OperationMethod_init(&(this->inherit_operationMethod), commandValue);
	this->blindRunning = blindRunning;
	this->sonarData = sonarData;
	for(count = 0; count < SCREEN; count++)
	{
		this->screen[count] = 0;
	}
}

/*===========================================================================
  FUNCTION    : ScreenDetectionRunning_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : デストラクタ
  MEMO        : 
===========================================================================*/
void ScreenDetectionRunning_finish(ScreenDetectionRunning* this)
{

}

/*===========================================================================
  FUNCTION    : ScreenDetectionRunning_execution
  PARAMETERS  : 
  RETURN      : 1：ミステリーサークル通過ルートの変更無し
                2：ミステリーサークル通過ルートをパターンBに変更
                3：ミステリーサークル通過ルートをパターンCに変更
                4：ミステリーサークル通過ルートをパターンDに変更
  DESCRIPTION : 衝立の検出と命令値の設定
  MEMO        : ミステリーサークル通過ルートはデフォルトでパターンAに設定
                ⇒変更が1回もない場合、パターンAで走行する
===========================================================================*/
S8 ScreenDetectionRunning_execution(ScreenDetectionRunning* this, S8 screenId, S16 turningRadius)
{
	S32 sonarReturn = 0; /* ソナーセンサの戻り値 */
	S8 rtn = 1; /* リターン値 */
	
	/* ソナーセンサで障害物までの距離を測定 */
	sonarReturn = SonarData_get(this->sonarData);
	
	/* 障害物までの距離が設定値以下であれば、衝立があると判断する */
	if(sonarReturn <= MINDISTANCE)
	{
		/* 同じ衝立を何度も検出しても通過ルートを変更するのは最初の一回のみ */
		if(this->screen[screenId] == 0)
		{
			/* 衝立パターンを設定 */
			this->screen[screenId] = 1;
			
			/* 衝立パターンから通過ルートを判断し戻り値を設定 */
			if(this->screen[0] == 0)
			{
				/* パターンB */
				if(this->screen[1] == 1)
				{
					rtn = 2;
				}
			}
			else
			{
				/* パターンC */
				if(this->screen[1] == 0)
				{
					rtn = 3;
				}
				/* パターンD */
				else
				{
					rtn = 4;
				}
			}
		}
	}
	
	/* 命令値を設定 */
	if(turningRadius < (TRED / 2))
	{
		BlindRunning_execution(this->blindRunning, 0, (TRED / 2 + 10));
	}
	else
	{
		BlindRunning_execution(this->blindRunning, 30, turningRadius);
	}
/*	CommandValue_setCommandValue((this->inherit_operationMethod.commandValue), -30, speed);*/
	
	return rtn;
}


