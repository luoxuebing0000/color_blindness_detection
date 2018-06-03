#include <stdio.h>
#include "pthread.h"
#include "play_music.h"
#include "mmap_lcd.h"
#include "lseek.h"
#include "input.h"
#include "random_num.h"


#define IF(a,b,c,d) if(x>a && x<b && y>c && y<d)
#define judgeFlag if(flag_judge == 0) flag_judge++;
#define CLEAR for(i=0;i<3;i++){arr2[i] = 0;}

int f=0, x=0,y=0;
int flag_judge = 0;
int arr2[3] = {0};

int judge(int flag);



int main(void)
{	
	pthread_t p1,p2;
	int result_return=0;
	int i=0;
	int flag_start=0,flag_introduction = 0;

	char filename[5][20]={"./imgs/0.bmp","./imgs/1.bmp","./imgs/2.bmp","./imgs/3.bmp","./imgs/4.bmp"};

	char bmps[7][30] = {"./imgs/main.bmp","./imgs/introduction.bmp","./imgs/err.bmp","./imgs/normal.bmp","./imgs/red.bmp","./imgs/green.bmp","./imgs/redGreen.bmp"};
	lcd_init();


main_img: 
	/*
	pthread_exit(&p1);
	pthread_exit(&p2);
	*/
    pthread_create(&p1, NULL, play_music, NULL);
	seek(bmps[0]);
	CLEAR;
	flag_judge = 0;
	while(1)
	{
		input();
		//printf("x1 = %d\ty1 = %d\n",x,y);
		//主界面“说明”按钮
		IF(409,582,23,173)
		{
			pthread_create(&p1, NULL, play_music, NULL);
			seek(bmps[1]);
			
			while(1)
			{
				input();
				printf("x2 = %d\ty2 = %d\n",x,y);
				IF(159,331,18,171)//说明界面 “主界面” 按钮
				{
					pthread_create(&p1, NULL, play_music, NULL);
					goto main_img;
				}
				IF(452,623,18,171)//说明界面 “开始” 按钮
				{
					pthread_create(&p1, NULL, play_music, NULL);
					goto start;
					
				}
			}
		}
		IF(201,371,23,173)//主界面“开始”按钮
		{
			pthread_create(&p1, NULL, play_music, NULL);
			break;
		}
	}
	
start:
	
	while(1)
	{
		f=rand_num_fun(f);
		seek(filename[f]);
		//x=y=999;
		input();
		/*if((x>680 && x<800) && ((y>330 && y<380) || (y>245 && y<295) || (y>156 && y<206) || (y>430 && y<480))){
			printf("fjlskdajflksadjfkl\n");
		}*/
		
		if((x>680 && x<800) && ((y>330 && y<380) || (y>245 && y<295) || (y>156 && y<206) || (y>430 && y<480)))
		{
			pthread_create(&p1, NULL, play_music, NULL);
			//printf("jflskdajlkfsdjfkljdslkf\n");
			switch(f)
			{
				case 0:
					while(1){
						IF(680,800,330,380){
							judgeFlag;
							arr2[0]++;
							break;
						}else IF(680,800,245,295){
							judgeFlag;
							break;
						}else IF(680,800,156,206){
							judgeFlag;
							arr2[0]++;
							break;
						}else IF(680,800,430,480){
							goto result_img;
						}
					}
					break;	
				case 1:
					while(1){
						IF(680,800,330,380){
							judgeFlag;
							arr2[0]++;
							break;
						}else IF(680,800,245,295){
							judgeFlag;
							arr2[0]++;
							break;
						}else IF(680,800,156,206){
							judgeFlag;
							break;
						}else IF(680,800,430,480){
							goto result_img;
						}
					}
					break;
				case 2:
					while(1){
						IF(680,800,330,380){
							judgeFlag;
							break;
						}else IF(680,800,245,295){
							judgeFlag;
							arr2[1]++;
							break;
						}else IF(680,800,156,206){
							judgeFlag;
							arr2[1]++;
							break;
						}else IF(680,800,430,480){
							goto result_img;
						}
					}
					break;
				case 3:
					while(1){
						IF(680,800,330,380){
							judgeFlag;
							arr2[0]++;
							break;
						}else IF(680,800,245,295){
							judgeFlag;
							arr2[0]++;
							break;
						}else IF(680,800,156,206){
							judgeFlag;
							break;
						}else IF(680,800,430,480){
							goto result_img;
						}
					}
					break;
				case 4:
					while(1){
						IF(680,800,330,380){
							judgeFlag;
							arr2[2]++;
							break;
						}else IF(680,800,245,295){
							judgeFlag;
							arr2[2]++;
							break;
						}else IF(680,800,156,206){
							judgeFlag;
							break;
						}else IF(680,800,430,480){
							goto result_img;
						}
					}
					break;
				default:
					break;
			}
		}
		else
			pthread_create(&p1, NULL, play_music, NULL);
		
		
	}

	

result_img:
	result_return = judge(flag_judge);
	if(result_return == -1){
		
	}else if(result_return == 1){

	}
	switch(result_return){
		case -1:
			seek(bmps[2]);
			while(1){
				input();
				IF(191,360,37,188)
				{
					pthread_create(&p1, NULL, play_music, NULL);
					goto main_img;
				}else IF(455,615,37,188)
				{
					CLEAR;
					flag_judge = 0;
					pthread_create(&p1, NULL, play_music, NULL);
					goto start;
				}
			}
			break;
		case 0:
			seek(bmps[3]);
			while(1){
				input();
				IF(325,495,43,190)
				{
					CLEAR;
					pthread_create(&p1, NULL, play_music, NULL);
					goto main_img;
				}
			}
			break;
		case 1:
			seek(bmps[4]);
			while(1){
				input();
				IF(327,496,43,190)
				{
					CLEAR;
					pthread_create(&p1, NULL, play_music, NULL);
					goto main_img;
				}
			}
			break;
		case 2:
			seek(bmps[5]);
			while(1){
				input();
				IF(325,495,38,191)
				{
					CLEAR;
					pthread_create(&p1, NULL, play_music, NULL);
					goto main_img;
				}
			}
			break;
		case 3:
			seek(bmps[6]);
			while(1){
				input();
				IF(325,495,38,191)
				{
					CLEAR;
					pthread_create(&p1, NULL, play_music, NULL);
					goto main_img;
				}
			}
			break;
		default:
			break;
	}
	lcd_uninit();
	return 0;

}


int judge(int flag){

	if(flag == 0){
		return -1;
	}

	if(arr2[0] != 0){
		if(arr2[1] !=0){
			return 3;
		}else if(arr2[2] !=0){
			return 3;
		}else{
			return 1;
		}
	}else if(arr2[1] !=0){
		if(arr2[2] !=0){
			return 3;
		}else{
			return 2;
		}
	}else if(arr2[2] !=0){
		return 3;
	}else{
		return 0;
	}
}
