#include "drv_timer.h"

uint32_t fac_us=0;							//us��ʱ������
uint32_t fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

void delay_init(void)
{
	SystemInit();
	SystemCoreClockUpdate();        //����ʡ��
}
void SysTick_Handler(void)
{
	if(fac_us) fac_us--;
	if(fac_ms) fac_ms--;
}
void delay_us(uint32_t nus)
{
	SysTick_Config(SystemCoreClock / 1000000);  //��ʱ1us
	fac_us = nus;
	while(fac_us != 0);
}

void delay_ms(uint32_t nms)
{
	SysTick_Config(SystemCoreClock / 1000);     //��ʱ1ms
	fac_ms = nms;
	while(fac_ms != 0);
}
