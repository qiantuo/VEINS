//relay_conrol.h
//First edited in 2017-1-7
//Author:q.t

#ifndef		__RELAY_CONTROL_H__
#define		__RELAY_CONTROL_H__

#include "stm32f0xx_hal.h"

#define		RELAY_MAX							(10)
#define		RELAY_NULL						(15)		//NULL contral,reserved

#define		USE_74595							(1)

#ifndef USE_74595
//74138
//pins
#define		RC_SEL_PORT0					GPIOA
#define		RC_SEL_PORT_PIN0			GPIO_PIN_0
#define		RC_SEL_PORT1					GPIOA
#define		RC_SEL_PORT_PIN1			GPIO_PIN_1
#define		RC_SEL_PORT2					GPIOA
#define		RC_SEL_PORT_PIN2			GPIO_PIN_2
#define		RC_SEL_PORT3					GPIOA
#define		RC_SEL_PORT_PIN3			GPIO_PIN_3

void RelaySel(uint8_t n);
int8_t RelayOn(uint8_t n);
void RelayTest(void);
void RelayAllOff(void);
	
#else
//74595
#define		RC_KEY_MODE_HOLD			(0x01)
#define		RC_KEY_MODE_ONLY			(0x02)
#define		RC_KEY_MODE_ALL				(0x03)

#define		RC_RCLK_PORT					GPIOA
#define		RC_RCLK_PIN						GPIO_PIN_1
#define		RC_OE_PORT						GPIOA
#define		RC_OE_PIN							GPIO_PIN_2

void RelaySel(uint16_t list);
int16_t RelayOn(uint8_t n,uint8_t mode);
int16_t RelayOff(uint8_t n,uint8_t mode);
void RelayTest(void);

#endif

#endif
