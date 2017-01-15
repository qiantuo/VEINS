//oled.h
//First edited in 2016-07-22
//Author: Q.T
#ifndef		__OLED_H__
#define		__OLED_H__

#include "stm32f0xx_hal.h"

#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	 

#define 	OLED_USE_4WIRE_SPI 		0x01
#define 	OLED_SPI_HANDLE				hspi1

//SPI Wire mode
#ifdef OLED_USE_4WIRE_SPI
	#define		OLED_CS_PORT					GPIOA
	#define		OLED_CS_PIN						GPIO_PIN_6
	#define		OLED_DC_PORT					GPIOA
	#define		OLED_DC_PIN						GPIO_PIN_4
#endif


#define	__OLED_CS_CLR							HAL_GPIO_WritePin(OLED_CS_PORT,OLED_CS_PIN,GPIO_PIN_RESET)
#define	__OLED_CS_SET							HAL_GPIO_WritePin(OLED_CS_PORT,OLED_CS_PIN,GPIO_PIN_SET)

#define	__OLED_DC_CLR							HAL_GPIO_WritePin(OLED_DC_PORT,OLED_DC_PIN,GPIO_PIN_RESET)
#define	__OLED_DC_SET							HAL_GPIO_WritePin(OLED_DC_PORT,OLED_DC_PIN,GPIO_PIN_SET)

#define	__OLED_PUT_DATA(pdata,size) \
																	do{ \
																		HAL_SPI_Transmit(&OLED_SPI_HANDLE,pdata,1,10); \
																	}while(0)

#define	OLED_CMD									0x00
#define	OLED_DATA									0x01																	
	
void OLED_Init(void);																	
void OLED_WR_Byte(uint8_t data,uint8_t pin_dc);		
void OLED_Clear(void);
void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_ShowChar(uint8_t x,uint8_t y,char chr);
void OLED_ShowString(uint8_t x,uint8_t y,char *chr);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void ShowInverse(void);
void ShowNormal(void);
void OLED_ClearLine(uint8_t l);
#endif

