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
  DESCRIPTION : �R���X�g���N�^
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
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void JudgeBrightness_finish(JudgeBrightness* this)
{
	
}

/*===========================================================================
  FUNCTION    : JudgeBrightness_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �R�[�X�P�x�𔻒肷��
  MEMO        : 
===========================================================================*/
S8 JudgeBrightness_execution(
	JudgeBrightness* this,
	S16 targetBrightness,
	S16 mode
)
{
	int meanValue; /* ���ϒl */
	int black; /* ��臒l */
	int white; /* ��臒l */
	int gray; /* �D�F臒l */
	S8 rtn = 0; /* �߂�l */
	
	/* �l���擾 */
	meanValue = CourseBrightness_getMeanBrightness(this->courseBrightness);
	black = CourseBrightness_getThreshold(this->courseBrightness, BLACK);
	white = CourseBrightness_getThreshold(this->courseBrightness, WHITE);
	gray = CourseBrightness_getThreshold(this->courseBrightness, GRAY);
	
	/* ��r�l��ݒ� */
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
	
	/* ���胂�[�h���Ƃɔ��� */
	switch(mode)
	{
	/* ��r�l�ȏォ���� */
	case OVER:
		rtn = ((targetBrightness <= (CourseBrightness_getBrightness(this->courseBrightness))) ? (1) : (0));
		break;
	/* ��r�l�ȉ������� */
	case UNDER:
		rtn = (((CourseBrightness_getBrightness(this->courseBrightness)) <= targetBrightness) ? (1) : (0));
		break;
	/* ���肵�Ă��邩���� */
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
	/* �R�[�X�A�E�g�𔻒� */
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

