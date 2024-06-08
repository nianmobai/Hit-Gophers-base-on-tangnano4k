#include "drv_timer.h"

uint32_t fac_us=0;							//us延时倍乘数
uint32_t fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数

void delay_init(void)
{
	SystemInit();
	SystemCoreClockUpdate();        //可以省略
}
void SysTick_Handler(void)
{
	if(fac_us) fac_us--;
	if(fac_ms) fac_ms--;
}
void delay_us(uint32_t nus)
{
	SysTick_Config(SystemCoreClock / 1000000);  //定时1us
	fac_us = nus;
	while(fac_us != 0);
}

void delay_ms(uint32_t nms)
{
	SysTick_Config(SystemCoreClock / 1000);     //定时1ms
	fac_ms = nms;
	while(fac_ms != 0);
}
