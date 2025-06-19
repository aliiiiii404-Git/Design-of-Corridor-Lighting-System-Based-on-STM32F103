#include "body_hw.h"
#include "BODY_HW.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/*****************辰哥单片机设计******************
											STM32
 * 文件			:	人体红外传感器c文件                   
 * 版本			: V1.0
 * 日期			: 2024.8.26
 * MCU			:	STM32F103C8T6
 * 接口			:	见代码							
 * BILIBILI	:	辰哥单片机设计
 * CSDN			:	辰哥单片机设计
 * 作者			:	辰哥

**********************BEGIN***********************/

void BODY_HW_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (BODY_HW_GPIO_CLK, ENABLE );	// 打开连接 传感器DO 的单片机引脚端口时钟
		GPIO_InitStructure.GPIO_Pin = BODY_HW_GPIO_PIN;			// 配置连接 传感器DO 的单片机引脚模式
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			// 设置为下拉输入
		GPIO_Init(BODY_HW_GPIO_PORT, &GPIO_InitStructure);				// 初始化 
	
}

uint16_t BODY_HW_GetData(void)
{
	uint16_t tempData;
	tempData = GPIO_ReadInputDataBit(BODY_HW_GPIO_PORT, BODY_HW_GPIO_PIN);
	return tempData;
}



