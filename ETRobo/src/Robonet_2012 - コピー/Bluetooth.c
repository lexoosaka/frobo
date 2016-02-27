/*************************************************************************

  Bluetooth.c

*************************************************************************/

/*===========================================================================
  include
===========================================================================*/
#include "Bluetooth.h"

/*===========================================================================
  function
===========================================================================*/
/*===========================================================================
  FUNCTION    : Bluetooth_init
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �R���X�g���N�^
  MEMO        :
===========================================================================*/
void Bluetooth_init(Bluetooth* this)
{
	U8 i;
	for(i=0; i<BT_RCV_BUF_SIZE; i++){
		this -> bt_receive_buf[i] = 0;
	}

}

/*===========================================================================
  FUNCTION    : Bluetooth_finish
  PARAMETERS  :
  RETURN      :
  DESCRIPTION : �f�X�g���N�^
  MEMO        :
===========================================================================*/
void Bluetooth_finish(Bluetooth* this)
{

}

/*===========================================================================
  FUNCTION    : Bluetooth_execution
  PARAMETERS  : ���s
  RETURN      : ����l
  DESCRIPTION : �K�����ڕW�l�t�߂�
  MEMO        :
===========================================================================*/
void Bluetooth_execution(Bluetooth* this){
	ecrobot_read_bt(this -> bt_receive_buf, BT_RCV_BUF_SIZE, BT_RCV_BUF_SIZE);	//master����A�f�[�^���
	ecrobot_send_bt(this -> bt_receive_buf, BT_RCV_BUF_SIZE, BT_RCV_BUF_SIZE);	//master����A�f�[�^���

}

S8 Bluetooth_waitStart(Bluetooth* this){

	if(this -> bt_receive_buf[8] != 0){
		return 1;
	}
	return 0;
}

