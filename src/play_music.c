#include<stdio.h>
#include "pthread.h"

void * play_music(void * arg)
{
	system("madplay ./mp3/keypress.mp3");//开始循环播放音乐
    return NULL;
}
