//ui.h
//First edited in 2017-1-7
//Author:q.t

#ifndef		__UI_H__
#define		__UI_H__

#include "stm32f0xx_hal.h"

#define		RC_STATUS_ON					(01)
#define		RC_STATUS_OFF					(00)

void ShowWelBmp(void);
void ShowRelayStatus(uint8_t n,uint8_t status);

#endif
