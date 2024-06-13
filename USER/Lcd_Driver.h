#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111

#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160

//图片数组在picture.c文件中，数字数组在num.c文件中
extern const unsigned char gImage_qq[3200];
extern const unsigned char asc16[];
extern const unsigned char gImage_grayqq[3200];

void SPI_WriteData_8(uint8_t Data);
void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData_16Bit(uint16_t Data);
void Lcd_WriteReg(uint8_t Index,uint8_t Data);
void Lcd_Reset();
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void Lcd_Init();
void Lcd_SetXY(uint16_t x,uint16_t y);
void Lcd_Clear(uint16_t Color);
void ShowNum(uint16_t x_start,uint16_t y_start,const unsigned char *p,uint16_t num);//
void ShowChar(uint16_t x_start,uint16_t y_start,const unsigned char *p,uint16_t charnum);//
void DrawPixel(uint16_t x_start,uint16_t y_start,uint16_t Color);
void ShowImage(uint16_t x_start,uint16_t y_start,uint16_t x_len,uint16_t y_len,const unsigned char *p);//
void ShowGrayImage(uint16_t x_start,uint16_t y_start,uint16_t x_len,uint16_t y_len,const unsigned char *p);

void EnableLED(void);
void ClearLED(void);

void EnableBLK(void);
void ClearBLK(void);

void EnableRES(void);
void ClearRES(void);

void EnableDC(void);
void ClearDC(void);

void EnableSCLK(void);
void ClearSCLK(void);

void EnableCS(void);
void ClearCS(void);

void EnableSDA(void);
void ClearSDA(void);
