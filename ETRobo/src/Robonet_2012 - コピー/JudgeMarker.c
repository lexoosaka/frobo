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
  DESCRIPTION : �R���X�g���N�^
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
  DESCRIPTION : �f�X�g���N�^
  MEMO        :
===========================================================================*/
void JudgeMarker_finish(JudgeMarker* this)
{

}

/*===========================================================================
  FUNCTION    : JudgeMarker_execution
  PARAMETERS  : �����A�D�F�}�[�J�[�̋����A臒l���[�g
  RETURN      : ���茋��
  DESCRIPTION : ������s
  MEMO        :
===========================================================================*/
S8 JudgeMarker_execution(
	JudgeMarker* this,
	S16 targetMileage,
	S16 rate
)
{
	S8 rtn = 0;
	/* 臒l�v�Z */
	int threshold = (CourseBrightness_getThreshold(this -> courseBrightness, MARKER) * (rate / 100)) +
					(CourseBrightness_getThreshold(this -> courseBrightness, BLACK) * (1-(rate / 100)));

	/* 臒l�𒴂��Ă��Ȃ����ǂ��� || ���̐헪�ɂȂ��ď�����s���ǂ���*/
	if((threshold < (CourseBrightness_getBrightness(this->courseBrightness))) || this->searchStart == 0){	//�����Ă���B
		this -> searchStart = (RunningPositionInfo_getMileage(this->runningPositionInfo));
	}else{							//�����Ă��Ȃ�
		if(targetMileage <= (RunningPositionInfo_getMileage(this->runningPositionInfo) - this -> searchStart)){ //targetMileage�ȏ�臒l�ȏ�𒴂��Ȃ�
//		if(targetMileage =< ){ //targetMileage�ȏ�臒l�ȏ�𒴂��Ȃ�
			rtn = 1;				//���̐헪��
			this -> searchStart = 0;	//������s���̂��ߕϐ�������
		}
	}
	return rtn;
}

