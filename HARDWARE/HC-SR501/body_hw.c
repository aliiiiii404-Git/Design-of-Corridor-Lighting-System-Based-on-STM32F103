#include "body_hw.h"
#include "BODY_HW.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	������⴫����c�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.8.26
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/

void BODY_HW_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (BODY_HW_GPIO_CLK, ENABLE );	// ������ ������DO �ĵ�Ƭ�����Ŷ˿�ʱ��
		GPIO_InitStructure.GPIO_Pin = BODY_HW_GPIO_PIN;			// �������� ������DO �ĵ�Ƭ������ģʽ
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			// ����Ϊ��������
		GPIO_Init(BODY_HW_GPIO_PORT, &GPIO_InitStructure);				// ��ʼ�� 
	
}

uint16_t BODY_HW_GetData(void)
{
	uint16_t tempData;
	tempData = GPIO_ReadInputDataBit(BODY_HW_GPIO_PORT, BODY_HW_GPIO_PIN);
	return tempData;
}



