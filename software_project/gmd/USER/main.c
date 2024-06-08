#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lcd_Driver.h"
int main(void)
{
	uint16_t rd = 0,num=1;
	unsigned int KeyRd[16];
	int i = 0;

	delay_init();

	EnableCS();
	EnableBLK();
	Lcd_Init();
	ShowNum(64,80,asc16,1);

	while(1)
	{
		gpio_read(&rd);		//read gpio0
		if(rd!=0)
		{
			delay_ms(50);//��ʱ0.05s
			gpio_read(&rd);
			if(rd!=0)
			{
				for(int i=0;i<16;i++)
				{
					KeyRd[i]=(unsigned int)((rd>>i)%0x02);//ͨ����λ+��������ȡrd�е�16λ���ݣ�ÿһλ����Ϊһ�����ݴ���KeyRd�У���ʾ��Ӧ�ļ�λ
				}
			}
		}
	}
}
