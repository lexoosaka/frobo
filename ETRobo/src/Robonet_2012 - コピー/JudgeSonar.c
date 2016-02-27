/*************************************************************************

  JudgeSonar.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "JudgeSonar.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : JudgeSonar_init
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �R���X�g���N�^
  MEMO        :
===========================================================================*/
void JudgeSonar_init(
	JudgeSonar* this,
	SonarData* sonarData
)
{
	this -> sonarData = sonarData;
	return ;

}

/*===========================================================================
  FUNCTION    : JudgeSonar_finish
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �f�X�g���N�^
  MEMO        :
===========================================================================*/
void JudgeSonar_finish(JudgeSonar* this)
{

}

/*===========================================================================
  FUNCTION    : JudgeSonar_execution
  PARAMETERS  : ���s
  RETURN      : ����l
  DESCRIPTION : �K�����ڕW�l�t�߂�
  MEMO        :
===========================================================================*/
S8 JudgeSonar_execution(JudgeSonar* this, S16 GeatLeng, S16 non){

	if(SonarData_get(this -> sonarData) < GeatLeng)
	{
			display_clear(1);
			display_goto_xy(0, 3);
			display_string("SONAR");
			display_goto_xy(7, 4);
			display_unsigned((U32)(this -> sonarData), 0);
			display_update();



		ecrobot_set_light_sensor_inactive(PORT_LIGHT_SENSOR); /* ���Z���TLED��ON�ɂ��� */
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}



