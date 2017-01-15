//relay_conrol.c
//First edited in 2017-1-7
//Author:q.t

#include 	"relay_control.h"
#include "oled.h"

extern SPI_HandleTypeDef hspi1;

uint16_t RelayTable[RELAY_MAX] = {0xFEFF,0xFDFF,0xFBFF,0xF7FF,0xEFFF,0xFFFE,0xFFFD,0xFFFB,0xFFF7,0xFFEF};

//Reset,All keys OFF.
uint16_t RelayStatus = 0xFFFF;

#ifndef USE_74595
//74138
void RelaySel(uint8_t n)
{
	//
	HAL_GPIO_WritePin(RC_SEL_PORT0,RC_SEL_PORT_PIN0,n & 0x01);
	HAL_GPIO_WritePin(RC_SEL_PORT1,RC_SEL_PORT_PIN1,(n>>1) & 0x01);
	HAL_GPIO_WritePin(RC_SEL_PORT2,RC_SEL_PORT_PIN2,(n>>2) & 0x01);
	HAL_GPIO_WritePin(RC_SEL_PORT3,RC_SEL_PORT_PIN3,(n>>3) & 0x01);
}

void RelayAllOff(void)
{
	RelaySel(RelayTable[0]);
}

void RelayTest(void)
{
	uint8_t i = 0;
	
	while(i < 16)
	{
		RelayOn(i++);
		HAL_Delay(1000);
	}
}

#else
//74595
void RelaySel(uint16_t list)
{
	//put CS High
	__OLED_CS_SET;
	
	HAL_GPIO_WritePin(RC_OE_PORT,RC_OE_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RC_RCLK_PORT,RC_RCLK_PIN,GPIO_PIN_RESET);
	
	HAL_SPI_Transmit(&hspi1,(uint8_t*)&list,sizeof(list),10);
	
	HAL_GPIO_WritePin(RC_RCLK_PORT,RC_RCLK_PIN,GPIO_PIN_SET);
	
	//put CS Low
	__OLED_CS_SET;
}

//Key1~Key10
int16_t RelayOn(uint8_t n,uint8_t mode)
{
	if(n > 0 && n <= RELAY_MAX)
	{
		if(mode == RC_KEY_MODE_ONLY)
		{
			RelayStatus = RelayTable[n-1];
		}
		else if(mode == RC_KEY_MODE_HOLD)
		{
			RelayStatus = RelayTable[n-1] & RelayStatus;
		}
		else if(mode == RC_KEY_MODE_ALL)
		{
			RelayStatus = 0x0000;
		}
		
		RelaySel(RelayStatus);
		return RelayStatus;
	}
	else
	{
		return -1;
	}
}

//Key1~Key10
int16_t RelayOff(uint8_t n,uint8_t mode)
{
	if(n > 0 && n <= RELAY_MAX)
	{
		if(mode == RC_KEY_MODE_ONLY)
		{
			RelayStatus = ~RelayTable[n-1];
		}
		else if(mode == RC_KEY_MODE_HOLD)
		{
			RelayStatus = ~RelayTable[n-1] | RelayStatus;
		}
		else if(mode == RC_KEY_MODE_ALL)
		{
			RelayStatus = 0xFFFF;
		}
		
		RelaySel(RelayStatus);
		return RelayStatus;
	}
	else
	{
		return -1;
	}
}

void RelayTest(void)
{
	uint16_t i = 1;
	
	while(i <= 10)
	{
		RelayOn(i++,RC_KEY_MODE_ONLY);
		HAL_Delay(1000);
	}
}

#endif

