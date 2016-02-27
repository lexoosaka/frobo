#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
/*************************************************************************

  Bluetooth.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"


/*===========================================================================
  define
===========================================================================*/
#define BT_PASS_KEY		"1234"	/* bluetooth�p�X�L�[ */
#define BT_RCV_BUF_SIZE 32		/* bluetooth��M�p�P�b�g�̑傫�� */
/*===========================================================================
  �K������N���X
===========================================================================*/
/* ���� */
typedef struct {
/*	JudgeMethod inherit_judgeMethod;	������@�N���X(�X�[�p�[�N���X) */
	U32 bt_receive_buf[BT_RCV_BUF_SIZE];
} Bluetooth;

/* ���� */
void Bluetooth_init(Bluetooth* this);				/* ���������� */
void Bluetooth_finish(Bluetooth* this);						/* �I������ */
void Bluetooth_execution(Bluetooth* this);			/* ���s */
S8 Bluetooth_waitStart(Bluetooth* this);
#endif

