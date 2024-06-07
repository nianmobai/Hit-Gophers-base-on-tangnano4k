#include "drv_gpio.h"

int gpio_init(void)
{
//	GPIO_InitTypeDef init;
//	init.GPIO_Int = GPIO_Int_Rising_Edge;
//	init.GPIO_Mode = GPIO_Mode_OUT;
//	init.GPIO_Pin = GPIO_Pin_0;
//	GPIO_Init(GPIO0, &init);
	return 0;
}

int gpio_write(uint16_t data)
{
	int ret = 0;
	GPIO_WriteBits(GPIO0, data);
	return ret;
}

int gpio_read(uint16_t *data)
{
	int ret = 0;

	*data = GPIO_ReadBits(GPIO0) & 0xffff;

	return ret;
}

int gpio_setIn(uint16_t mask)
{
	int ret = 0;

	GPIO_ClrOutEnable(GPIO0, mask);//set input

	return ret;
}

int gpio_setOut(uint16_t mask)
{
	int ret = 0;

	GPIO_SetOutEnable(GPIO0, 0xffffffff);//set output

	return ret;
}

