#include "Lcd_Driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
//BLK��Ӧ1,RES��Ӧ2����̬Ϊ1����λ��Ϊ0��Ϊ1,DC��Ӧ3,Ϊ1�����ݣ�Ϊ0��ָ��
//SCL��Ӧ0+4����̬Ϊ1��CS��Ӧ1+4����̬Ϊ1��SDA��Ӧ2+4

void SPI_WriteData_8(uint8_t Data)//д����
{
	unsigned int i = 0;
	for(i=8;i>0;i--){
		if(Data & 0x80)EnableSDA();
		else ClearSDA();
		ClearSCLK();
		EnableSCLK();
		Data = Data<<1;
	}
}

void Lcd_WriteIndex(uint8_t Index)//дָ��
{
	ClearCS();
	ClearDC();
	SPI_WriteData_8(Index);
	EnableCS();
}
void Lcd_WriteData(uint8_t Data)//д����
{
	ClearCS();
	EnableDC();
	SPI_WriteData_8(Data);
	EnableCS();
}

void Lcd_WriteData_16Bit(uint16_t Data)
{
	ClearCS();
	EnableDC();
	SPI_WriteData_8(Data>>8);
	SPI_WriteData_8(Data);
	EnableCS();
}

void Lcd_WriteReg(uint8_t Index,uint8_t Data)
{
	Lcd_WriteIndex(Index);
	Lcd_WriteData(Data);
}

void Lcd_Reset()
{
	ClearRES();
	delay_ms(1);
	EnableRES();
	delay_ms(120);
}

void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)//����lcd��ʾ�����ڴ�����д�������Զ�����
{
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x02);
	Lcd_WriteData(x_start);//Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x02);
	Lcd_WriteData(x_end);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x01);
	Lcd_WriteData(y_start);
	Lcd_WriteData(0x01);
	Lcd_WriteData(y_end);

	Lcd_WriteIndex(0x2c);
}
//дһ�����أ���ڲ����ֱ�Ϊx��ʼ�������꣬y�����������,��ɫ
void DrawPixel(uint16_t x_start,uint16_t y_start,uint16_t Color)
{
	Lcd_SetRegion(x_start,y_start,x_start+1,y_start+1);
	Lcd_WriteData_16Bit(Color);
}
//дһ������,��ڲ����ֱ�Ϊx��ʼ�������ꡢ���ֶ�Ӧ���顢Ҫ��ʾ�����֣������Ǽ���д��
void ShowNum(uint16_t x_start,uint16_t y_start,const unsigned char *p,uint16_t num)//��ʾ����
{
	unsigned char buff[16];
	int k=0;
	Lcd_Clear(WHITE);
	Lcd_SetRegion(x_start,y_start,x_start+15,y_start+15);
	for(int i=0;i<16;i++)
	{
		buff[i]=p[i+num*16];
	}
	for(uint16_t y=0;y<16;y++)
	{
		for(uint16_t x=0;x<8;x++)
		{
			k=x%8;
			if(buff[y]&(0x80>>k))
			{
				DrawPixel(x_start+x,y_start+y,RED);
			}
		}
	}
}
//дһ����ĸ,��ڲ����ֱ�Ϊx��ʼ�������ꡢ���ֶ�Ӧ���顢Ҫ��ʾ�����֣���д��ǰ��Сд�ں���ĸ��˳��,A��Ӧ1����
void ShowChar(uint16_t x_start,uint16_t y_start,const unsigned char *p,uint16_t charnum)
{
	unsigned char buff[16];
		int k=0;
		Lcd_Clear(WHITE);
		Lcd_SetRegion(x_start,y_start,x_start+15,y_start+15);
		for(int i=0;i<16;i++)
		{
			buff[i]=p[i+(charnum+9)*16];
		}
		for(uint16_t y=0;y<16;y++)
		{
			for(uint16_t x=0;x<8;x++)
			{
				k=x%8;
				if(buff[y]&(0x80>>k))
				{
					DrawPixel(x_start+x,y_start+y,RED);
				}
			}
		}
}
//��ʾͼ����ڲ����ֱ�Ϊx��ʼ�������ꡢy��ʼ�������ꡢx���򳤶ȡ�y���򳤶ȣ�ͼƬ��Ӧ����
void ShowImage(uint16_t x_start,uint16_t y_start,uint16_t x_len,uint16_t y_len,const unsigned char *p)//��ʾͼ��
{
	int i=0;
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //����
	Lcd_SetRegion(x_start,y_start,x_start+x_len-1,y_start+y_len-1);		//��������
	for(i=0;i<40*40;i++)
		{
			picL=*(p+i*2);	//���ݵ�λ��ǰ
			picH=*(p+i*2+1);
			Lcd_WriteData_16Bit(picH<<8|picL);
		}
}
void Lcd_SetXY(uint16_t x,uint16_t y)//����lcd��ʾ��ʼ��
{
	Lcd_SetRegion(x,y,x,y);
}

void Lcd_Clear(uint16_t Color)//ȫ����������
{
	unsigned int i,m;
	Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
	for(i=0;i<X_MAX_PIXEL;i++)
	    for(m=0;m<Y_MAX_PIXEL;m++)
	    {
		  	Lcd_WriteData_16Bit(Color);
	    }
}

void Lcd_Init()
{
	Lcd_Reset();
	Lcd_WriteIndex(0x11);
	delay_ms (120);

	//ST7735S Frame Rate
	Lcd_WriteIndex(0xB1);
	Lcd_WriteData(0x05);
	Lcd_WriteData(0x3C);
	Lcd_WriteData(0x3C);

	Lcd_WriteIndex(0xB2);
	Lcd_WriteData(0x05);
	Lcd_WriteData(0x3C);
	Lcd_WriteData(0x3C);

	Lcd_WriteIndex(0xB3);
	Lcd_WriteData(0x05);
	Lcd_WriteData(0x3C);
	Lcd_WriteData(0x3C);
	Lcd_WriteData(0x05);
	Lcd_WriteData(0x3C);
	Lcd_WriteData(0x3C);

	Lcd_WriteIndex(0xB4); //Column inversion
	Lcd_WriteData(0x03);

	//ST7735S Power Sequence
	Lcd_WriteIndex(0xC0);
	Lcd_WriteData(0x28);
	Lcd_WriteData(0x08);
	Lcd_WriteData(0x04);
	Lcd_WriteIndex(0xC1);
	Lcd_WriteData(0xC0);

	Lcd_WriteIndex(0xC2);
	Lcd_WriteData(0x0D);
	Lcd_WriteData(0x00);

	Lcd_WriteIndex(0xC3);
	Lcd_WriteData(0x8D);
	Lcd_WriteData(0x2A);
	Lcd_WriteIndex(0xC4);
	Lcd_WriteData(0x8D);
	Lcd_WriteData(0xEE);

	Lcd_WriteIndex(0xC5); //VCOM
	Lcd_WriteData(0x1A);

	Lcd_WriteIndex(0x36); //MX, MY, RGB mode
	Lcd_WriteData(0xC0);

	//ST7735S Gamma Sequence
	Lcd_WriteIndex(0xe0);
	Lcd_WriteData(0x04);
	Lcd_WriteData(0x22);
	Lcd_WriteData(0x07);
	Lcd_WriteData(0x0A);
	Lcd_WriteData(0x2E);
	Lcd_WriteData(0x30);
	Lcd_WriteData(0x25);
	Lcd_WriteData(0x2A);
	Lcd_WriteData(0x28);
	Lcd_WriteData(0x26);
	Lcd_WriteData(0x2E);
	Lcd_WriteData(0x3A);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x01);
	Lcd_WriteData(0x03);
	Lcd_WriteData(0x13);

	Lcd_WriteIndex(0xe1);
	Lcd_WriteData(0x04);
	Lcd_WriteData(0x16);
	Lcd_WriteData(0x06);
	Lcd_WriteData(0x0D);
	Lcd_WriteData(0x2D);
	Lcd_WriteData(0x26);
	Lcd_WriteData(0x23);
	Lcd_WriteData(0x27);
	Lcd_WriteData(0x27);
	Lcd_WriteData(0x25);
	Lcd_WriteData(0x2D);
	Lcd_WriteData(0x3B);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x01);
	Lcd_WriteData(0x04);
	Lcd_WriteData(0x13);


	Lcd_WriteIndex(0x3A); //65k mode
	Lcd_WriteData(0x05);

	Lcd_WriteIndex(0x29);//Display on

}

void EnableLED(void){//LED��1
	GPIO_SetBit(GPIO0,0x0001);
}
void ClearLED(void){//LED��0
	GPIO_ResetBit(GPIO0,0x0001);
}
void EnableBLK(void){//BLK��1
	GPIO_SetBit(GPIO0,0x0002);
}
void ClearBLK(void){//BLK��0
	GPIO_ResetBit(GPIO0,0x0002);
}
void EnableRES(void){//RES��1
	GPIO_SetBit(GPIO0,0x0004);
}
void ClearRES(void){//RES��0
	GPIO_ResetBit(GPIO0,0x0004);
}
void EnableDC(void){//DC��1
	GPIO_SetBit(GPIO0,0x0008);
}
void ClearDC(void){//DC��0
	GPIO_ResetBit(GPIO0,0x0008);
}
void EnableSCLK(void){//SCLK = 1
	GPIO_SetBit(GPIO0,0x0010);
}
void ClearSCLK(void){//SCK = 0
	GPIO_ResetBit(GPIO0,0x0010);
}
void EnableCS(void){//Ƭѡ�ź���1
	GPIO_SetBit(GPIO0,0x0020);
}
void ClearCS(void){//Ƭѡ�ź���0
	GPIO_ResetBit(GPIO0,0x0020);
}
void EnableSDA(void){//Ƭѡ�ź���1
	GPIO_SetBit(GPIO0,0x0040);
}
void ClearSDA(void){//Ƭѡ�ź���0
	GPIO_ResetBit(GPIO0,0x0040);
}

