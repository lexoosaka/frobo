/*************************************************************************

  BlindRunning.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "BlindRunning.h"


/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : BlindRunning_init
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �R���X�g���N�^
  MEMO        : 
===========================================================================*/
void BlindRunning_init(
	BlindRunning* this,
	MotorCount* motorCountL,
	MotorCount* motorCountR,
	CommandValue* commandValue
)
{
	/* ������������ */
	OperationMethod_init(&(this->inherit_operationMethod), commandValue);
	this->motorCount[0] = motorCountL;
	this->motorCount[1] = motorCountR;
}

/*===========================================================================
  FUNCTION    : BlindRunning_finish
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �f�X�g���N�^
  MEMO        : 
===========================================================================*/
void BlindRunning_finish(BlindRunning* this)
{

}

/*===========================================================================
  FUNCTION    : BlindRunning_execution
  PARAMETERS  : 
  RETURN      : 
  DESCRIPTION : �u���C���h���s���̖��ߒl�����肷��
  MEMO        : 
===========================================================================*/
S8 BlindRunning_execution(BlindRunning* this, S8 speed, S16 turningRadius)
{
	S16 targetRatioL; /* �����[�^�̉�]�p�̖ڕW�� */
	S16 targetRatioR; /* �E���[�^�̉�]�p�̖ڕW�� */
	S32 targetCountR; /* �E���[�^�̖ڕW��]�p */
	S16 nowCountL; /* �u���C���h���s�J�n�ォ��̍����[�^�̉�]�p */
	S16 nowCountR; /* �u���C���h���s�J�n�ォ��̉E���[�^�̉�]�p */
	S16 turningRadiusCopy = turningRadius; /* ���񔼌a���R�s�[ */
	S32 turn; /* ���񖽗ߒl */
	
	/* �v�Z�̂��ߐ��񔼌a�����̒l�̏ꍇ�͐��̒l�ɕϊ����� */
	if(turningRadiusCopy < 0)
	{
		turningRadiusCopy *= -1;
	}
	/* �����[�^�̉�]�p�̖ڕW����v�Z */
	targetRatioL = turningRadiusCopy - (TRED / 2);
	if(targetRatioL < 0)
	{
		targetRatioL *= -1;
	}
	/* �E���[�^�̉�]�p�̖ڕW����v�Z */
	targetRatioR = turningRadiusCopy + (TRED / 2);
	
	/* ���񔼌a�����̒l�̏ꍇ���E�̃��[�^�̖ڕW������ւ��� */
	if(turningRadius < 0)
	{
		turningRadiusCopy = targetRatioL;
		targetRatioL = targetRatioR;
		targetRatioR = turningRadiusCopy;
	}
	
	/* �u���C���h���s�J�n�ォ��̂��ꂼ��̃��[�^�̉�]�p���擾 */
	nowCountL = (MotorCount_getMotorCount(this->motorCount[0])) - (MotorCount_getStartMotorCount(this->motorCount[0]));
	nowCountR = (MotorCount_getMotorCount(this->motorCount[1])) - (MotorCount_getStartMotorCount(this->motorCount[1]));
	
	/* ���݂̍����[�^�̉�]�p����E���[�^�̖ڕW��]�p���v�Z */
	targetCountR = nowCountL * targetRatioR / targetRatioL;
	
	/* �E���[�^�̖ڕW��]�p�ƌ��݂̉�]�p�̍�������񖽗ߒl������ */
	turn = (nowCountR - targetCountR) * 2;
	
	turn = (((turn) >= (50)) ? (50) : (((turn) <= (-50)) ? (-50) : (turn)));
	
	/* ���ߒl��ݒ� */
	CommandValue_setCommandValue((this->inherit_operationMethod.commandValue), (S8)turn, speed);
	
	return (S8)1;
}




