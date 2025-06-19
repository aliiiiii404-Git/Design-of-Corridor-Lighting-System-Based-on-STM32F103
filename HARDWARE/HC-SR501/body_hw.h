#ifndef __BODY_HW_H
#define	__BODY_HW_H
#include "stm32f10x.h"
#include "adcx.h"
#include "delay.h"
#include "math.h"

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	HC-SR501������⴫����h�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.8.26
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/


/***************�����Լ��������****************/
// BODY_HW GPIO�궨��

#define		BODY_HW_GPIO_CLK								RCC_APB2Periph_GPIOA
#define 	BODY_HW_GPIO_PORT								GPIOA
#define 	BODY_HW_GPIO_PIN								GPIO_Pin_5	

/*********************END**********************/


void BODY_HW_Init(void);
uint16_t BODY_HW_GetData(void);

#endif /* __BODY_HW_H */

