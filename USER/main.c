#include <Lcd_Driver.h>
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define NUM_GRIDS 9
//#define GAME_DURATION 10  // 游戏持续时间（秒）

unsigned int ALP_table[16]={3,2,1,7,6,5,11,10,9,12,12,12,12,12,12,12};


// 模拟检查 KeyRd 数组
bool isMoleHit(int id, int KeyRd[]) {
	unsigned int key_id=ALP_table[id];
    return KeyRd[key_id] == 1;
}

// 重置 KeyRd 数组
void resetKeyRd(int KeyRd[]) {
    for (int i = 0; i < NUM_GRIDS; i++) {
        KeyRd[i] = 0;
    }
}


int main(void)
{
	/*屏幕大小为128*160，以左上角为坐标原点，
	图像大小为40*40，格子为3*3，三个格子的坐标分别为，
	(4,20)   (44,20)   (84,20)
	(4,60)   (44,60)   (84,60)
	(4,100)  (44,100)  (84,100)*/


	uint16_t rd = 0,num=1;
	unsigned int KeyRd[16];
	int game_duration = 10;
	int i = 0;
	int seed=1;
	int sub_time =0;
	bool isContinue = true;
	int lives =3;
	unsigned int id_table[9][2]={{4,20},{44,20},{84,20},
								 {4,60},{44,60},{84,60},
								 {4,100},{44,100},{84,100}};


	delay_init();

	EnableCS();
	EnableBLK();
	Lcd_Init();

	//开始界面
	Lcd_Clear(BLACK);
	ShowChar(30,60,asc16,13);
	ShowChar(40,60,asc16,41);
	ShowChar(50,60,asc16,38);
	ShowChar(60,60,asc16,31);
	ShowChar(70,60,asc16,8);
	ShowChar(80,60,asc16,35);
	ShowChar(90,60,asc16,46);

	ShowChar(40,90,asc16,19);
	ShowChar(50,90,asc16,20);
	ShowChar(60,90,asc16,1);
	ShowChar(70,90,asc16,18);
	ShowChar(80,90,asc16,20);

	while(1)
	{
	gpio_read(&rd);		//read gpio0
	if(rd!=0)
	{
		delay_ms(20);//延时0.05s
		gpio_read(&rd);
		if(rd!=0)
		{
			break;
		}
	}
	}





	while(isContinue){
		int hitCount = 0;
			int mole_count = 0;
			isContinue=false;

			if(lives==0)
			{
				Lcd_Clear(BLACK);

				ShowChar(25,60,asc16,7);
				ShowChar(35,60,asc16,1);
				ShowChar(45,60,asc16,13);
				ShowChar(55,60,asc16,5);

				ShowChar(75,60,asc16,15);
				ShowChar(85,60,asc16,22);
				ShowChar(95,60,asc16,5);
				ShowChar(105,60,asc16,18);



				delay_ms(3000);

				seed=1;
				game_duration=10;
				sub_time =0;
				lives = 3;
							}

			// 初始化随机数生成器
			srand(seed);
			Lcd_Clear(BLACK);

			ShowChar(30,60,asc16,38);
			ShowChar(40,60,asc16,31);
			ShowChar(50,60,asc16,48);
			ShowChar(60,60,asc16,31);
			ShowChar(70,60,asc16,38);

			//ShowNum(90,60,asc16,seed);
			if (seed>=10)
			{
				ShowNum(100,60,asc16,(int)seed/10);
				ShowNum(90,60,asc16,seed%10);
			}
			else ShowNum(90,60,asc16,seed);

			delay_ms(1000);


			Lcd_Clear(BLACK);

			ShowChar(30,60,asc16,38);
			ShowChar(40,60,asc16,35);
			ShowChar(50,60,asc16,31);
			ShowChar(60,60,asc16,48);
			ShowChar(70,60,asc16,45);

			if (lives>=10)
			{
				ShowNum(100,60,asc16,(int)lives/10);
				ShowNum(90,60,asc16,lives%10);
			}
			else ShowNum(90,60,asc16,lives);


			delay_ms(1000);


			Lcd_Clear(WHITE);


			// 游戏主循环
			while ( mole_count  < game_duration) {
			    int id = rand() % NUM_GRIDS;  // 生成1到9之间的随机数

			    ShowImage(id_table[id][0],id_table[id][1],40,40,gImage_qq);
			    mole_count++;

			    int time_count = 300000 - sub_time;


			    //打击地鼠、键盘
			    while(time_count>0)
			    	{
			    		gpio_read(&rd);		//read gpio0
			    		if(rd!=0)
			    		{
			    			delay_ms(20);//延时0.05s
			    			gpio_read(&rd);
			    			if(rd!=0)
			    			{
			    				for(int i=0;i<16;i++)
			    				{
			    					KeyRd[i]=(unsigned int)((rd>>i)%0x02);
			    				}
			    				if (isMoleHit(id, KeyRd)) {
			    					//地鼠打击反馈
			    					ShowGrayImage(id_table[id][0],id_table[id][1],40,40,gImage_grayqq);
			    					hitCount++;
			    					id=10;
			    				}

			    			}

			    			time_count-=3000;

			    		}

			    		time_count--;

			    	}

			}

			Lcd_Clear(BLACK);

			ShowChar(40,60,asc16,19);
			ShowChar(50,60,asc16,3);
			ShowChar(60,60,asc16,15);
			ShowChar(70,60,asc16,18);
			ShowChar(80,60,asc16,5);
			if (hitCount>=10)
			{
				ShowNum(50,80,asc16,(int)hitCount/10);
				ShowNum(70,80,asc16,hitCount%10);
			}
			else ShowNum(60,80,asc16,hitCount);

			if(hitCount<(int)(game_duration/2))
			{
				ShowChar(45,100,asc16,6);
				ShowChar(55,100,asc16,27);
				ShowChar(65,100,asc16,35);
				ShowChar(75,100,asc16,38);
				lives--;
			}
			else
			{
				ShowChar(40,100,asc16,3);
				ShowChar(50,100,asc16,38);
				ShowChar(60,100,asc16,31);
				ShowChar(70,100,asc16,27);
				ShowChar(80,100,asc16,44);
				seed++;
				if(game_duration<=60){
					game_duration+=5;
				}
				if(seed<20){
					sub_time+=10000;
				}
				if(seed%5==0)
				{
					lives++;
				}

			}

			while(1)
			{
				gpio_read(&rd);		//read gpio0
				if(rd!=0)
				{
					delay_ms(20);//延时0.05s
					gpio_read(&rd);
					if(rd!=0)
					{

						isContinue = true;

						break;
					}
				}
			}
	}


}
