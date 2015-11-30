#ifndef PDCONTROLPARAMETER_H_
#define PDCONTROLPARAMETER_H_
/*************************************************************************

  PDControlParameter.h

*************************************************************************/
/*===========================================================================
  include
===========================================================================*/
#include "ecrobot_interface.h"
#include "port_define.h"


/*===========================================================================
  define
===========================================================================*/


/*===========================================================================
  PD制御パラメータクラス
===========================================================================*/
/* 属性 */
typedef struct {
	float pControlParameter;	/* P制御パラメータ */
	float dControlParameter;	/* D制御パラメータ */
} PDControlParameter;

/* 操作 */
void PDControlParameter_init(PDControlParameter* this);				/* 初期化操作 */
void PDControlParameter_finish(PDControlParameter* this);			/* 終了操作 */
void PDControlParameter_setParameter(PDControlParameter* this);		/* パラメータセット */
float PDControlParameter_getPParameter(PDControlParameter* this);	/* Pパラメータゲット */
float PDControlParameter_getDParameter(PDControlParameter* this);	/* Dパラメータゲット */

#endif

