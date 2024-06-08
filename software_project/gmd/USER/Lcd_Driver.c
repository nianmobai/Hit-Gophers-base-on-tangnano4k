#include "Lcd_Driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
//BLK对应1,RES对应2，常态为1，复位先为0后为1,DC对应3,为1读数据，为0读指令
//SCL对应0+4，常态为1，CS对应1+4，常态为1，SDA对应2+4

void SPI_WriteData_8(uint8_t Data)//写数据
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

void Lcd_WriteIndex(uint8_t Index)//写指令
{
	ClearCS();
	ClearDC();
	SPI_WriteData_8(Index);
	EnableCS();
}
void Lcd_WriteData(uint8_t Data)//写数据
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

void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)//设置lcd显示区域，在此区域写点数据自动换行
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
//写一个像素，入口参数分别为x开始像素坐标，y入口像素坐标,颜色
void DrawPixel(uint16_t x_start,uint16_t y_start,uint16_t Color)
{
	Lcd_SetRegion(x_start,y_start,x_start+1,y_start+1);
	Lcd_WriteData_16Bit(Color);
}
//写一个数字,入口参数分别为x开始像素坐标、数字对应数组、要显示的数字，数字是几就写几
void ShowNum(uint16_t x_start,uint16_t y_start,const unsigned char *p,uint16_t num)//显示数字
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
//写一个字母,入口参数分别为x开始像素坐标、数字对应数组、要显示的数字，大写在前，小写在后，字母表顺序,A对应1类推
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
//显示图像，入口参数分别为x开始像素坐标、y开始像素坐标、x方向长度、y方向长度，图片对应数组
void ShowImage(uint16_t x_start,uint16_t y_start,uint16_t x_len,uint16_t y_len,const unsigned char *p)//显示图像
{
	int i=0;
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //清屏
	Lcd_SetRegion(x_start,y_start,x_start+x_len-1,y_start+y_len-1);		//坐标设置
	for(i=0;i<40*40;i++)
		{
			picL=*(p+i*2);	//数据低位在前
			picH=*(p+i*2+1);
			Lcd_WriteData_16Bit(picH<<8|picL);
		}
}
void Lcd_SetXY(uint16_t x,uint16_t y)//设置lcd显示起始点
{
	Lcd_SetRegion(x,y,x,y);
}

void Lcd_Clear(uint16_t Color)//全屏清屏函数
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

void EnableLED(void){//LED置1
	GPIO_SetBit(GPIO0,0x0001);
}
void ClearLED(void){//LED置0
	GPIO_ResetBit(GPIO0,0x0001);
}
void EnableBLK(void){//BLK置1
	GPIO_SetBit(GPIO0,0x0002);
}
void ClearBLK(void){//BLK置0
	GPIO_ResetBit(GPIO0,0x0002);
}
void EnableRES(void){//RES置1
	GPIO_SetBit(GPIO0,0x0004);
}
void ClearRES(void){//RES置0
	GPIO_ResetBit(GPIO0,0x0004);
}
void EnableDC(void){//DC置1
	GPIO_SetBit(GPIO0,0x0008);
}
void ClearDC(void){//DC置0
	GPIO_ResetBit(GPIO0,0x0008);
}
void EnableSCLK(void){//SCLK = 1
	GPIO_SetBit(GPIO0,0x0010);
}
void ClearSCLK(void){//SCK = 0
	GPIO_ResetBit(GPIO0,0x0010);
}
void EnableCS(void){//片选信号置1
	GPIO_SetBit(GPIO0,0x0020);
}
void ClearCS(void){//片选信号置0
	GPIO_ResetBit(GPIO0,0x0020);
}
void EnableSDA(void){//片选信号置1
	GPIO_SetBit(GPIO0,0x0040);
}
void ClearSDA(void){//片选信号置0
	GPIO_ResetBit(GPIO0,0x0040);
}

