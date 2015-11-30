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
  DESCRIPTION : コンストラクタ
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
  DESCRIPTION : デストラクタ
  MEMO        :
===========================================================================*/
void Bluetooth_finish(Bluetooth* this)
{

}

/*===========================================================================
  FUNCTION    : Bluetooth_execution
  PARAMETERS  : 実行
  RETURN      : 判定値
  DESCRIPTION : 尻尾が目標値付近か
  MEMO        :
===========================================================================*/
void Bluetooth_execution(Bluetooth* this){
	ecrobot_read_bt(this -> bt_receive_buf, BT_RCV_BUF_SIZE, BT_RCV_BUF_SIZE);	//masterから、データ受取
	ecrobot_send_bt(this -> bt_receive_buf, BT_RCV_BUF_SIZE, BT_RCV_BUF_SIZE);	//masterから、データ受取

}

S8 Bluetooth_waitStart(Bluetooth* this){

	if(this -> bt_receive_buf[8] != 0){
		return 1;
	}
	return 0;
}

