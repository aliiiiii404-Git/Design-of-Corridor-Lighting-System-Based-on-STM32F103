#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "adc.h"
#include "lsens.h"
#include "usmart.h"
#include "rtc.h"
#include "stm32f10x.h"
#include "body_hw.h"
#include "adcx.h"
#include "usart3.h"
#include "gizwits_product.h"
#include "gizwits_protocol.h"
#include "timer.h"

#define LIGHT_THRESHOLD 50
int current_hour = 0;
int kaiguan;
#define DAY_START_HOUR 6
#define DAY_END_HOUR 18
u16 value = 0;

u16 pre_value = 0;

u8 light_value;

u8 t;

u8 adcx;

void update_display_info(void);
void control_leds(void);

void Gizwits_Init(void)
{
	
	TIM3_Int_Init(9,7199);//1MS系统定时
    usart3_init(9600);//WIFI初始化
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//设备状态结构体初始化
	gizwitsInit();//缓冲区初始化
}

int main(void)
{   
    delay_init();      
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
    uart_init(115200);    
    LED_Init();          
    LCD_Init();          
    Lsens_Init();        
    RTC_Init();          
    RTC_Set(2025, 1, 3, 19, 00, 00);
    SystemInit();   
    BODY_HW_Init();
	  userInit();
    Gizwits_Init();
	  delay_ms(500);
	  gizwitsSetMode(WIFI_AIRLINK_MODE);
	  BODY_HW_Init();
	  
    POINT_COLOR = RED;
    LCD_ShowString(30, 20, 200, 16, 16, "Elite STM32");
    LCD_ShowString(30, 40, 200, 16, 16, "Multi-Function TEST");

    POINT_COLOR = BLUE;
    LCD_ShowString(30, 70, 200, 16, 16, "RTC Information:");
    LCD_ShowString(30, 110, 200, 16, 16, "Year:");
    LCD_ShowString(110, 110, 200, 16, 16, "Month:");
    LCD_ShowString(190, 110, 200, 16, 16, "Date:");
    LCD_ShowString(30, 170, 200, 16, 16, "Hour:");
    LCD_ShowString(110, 170, 200, 16, 16, "Min:");
    LCD_ShowString(190, 170, 200, 16, 16, "Sec:");
    LCD_ShowString(30, 300, 200, 16, 16, "LSENS_VAL:");

    while (1)
    {
		userHandle();
    gizwitsHandle((dataPoint_t *)&currentDataPoint);
		light_value = Lsens_Get_Val();
		value = BODY_HW_GetData();
		
			if(kaiguan==1)
			{
				if(value != pre_value)
		{
			if(value == 1)
			{	
				 LCD_ShowString(30, 250, 200, 16, 16, "there have people");
			}
			else
			{
				LCD_ShowString(30, 250, 200, 16, 16, "there no people");
			}
		}
		pre_value = value;
        delay_ms(200);
        update_display_info();
        control_leds();
        adcx = Lsens_Get_Val();
        LCD_ShowxNum(30 + 10 * 8, 300, adcx, 3, 16, 0);
        delay_ms(10);
		}
			}
		
}

void update_display_info(void)
{
    if (t!= calendar.sec)  
    {
        t = calendar.sec;

        LCD_ShowNum(30, 110 + 20, calendar.w_year, 4, 16);
        LCD_ShowNum(110, 110 + 20, calendar.w_month, 2, 16);
        LCD_ShowNum(190, 110 + 20, calendar.w_date, 2, 16);

        current_hour = calendar.hour;
        LCD_ShowNum(30, 170 + 20, calendar.hour, 2, 16);

        LCD_ShowNum(110, 170 + 20, calendar.min, 2, 16);
        LCD_ShowNum(190, 170 + 20, calendar.sec, 2, 16);
    }
}

void control_leds(void)
{
    if (calendar.hour >= DAY_START_HOUR && calendar.hour < DAY_END_HOUR)
    {
        if (light_value <= LIGHT_THRESHOLD)
        {
					
					  GPIO_ResetBits(GPIOB, GPIO_Pin_5);
            GPIO_ResetBits(GPIOE, GPIO_Pin_5);
              
        }
        else if (light_value > LIGHT_THRESHOLD)
        {

					  GPIO_SetBits(GPIOB, GPIO_Pin_5);
            GPIO_ResetBits(GPIOE, GPIO_Pin_5);
        }
		}
    else
		{
			if(light_value > LIGHT_THRESHOLD)
			{
			  GPIO_SetBits(GPIOB, GPIO_Pin_5);
        GPIO_SetBits(GPIOE, GPIO_Pin_5);
			}
			else
      {
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
        GPIO_ResetBits(GPIOE, GPIO_Pin_5);
      }
     }
}