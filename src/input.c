#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

extern int x,y;


/*获取触屏事件*/
int input(void)
{
	int xx,yy;
	int fd = open("/dev/event0",O_RDONLY);
	if(fd == -1)
	{
		perror("open event error");
		return -1;
	}
	struct input_event ev;
	while(1)
	{
		read(fd,&ev,sizeof(ev)); //获取输入事件
		if(ev.type == EV_ABS) //判断是不是触摸屏事件
		{
			
			if(ev.code == ABS_X) //判断是不是触摸点x轴
			{
				x=xx = ev.value;
				printf("ev.vlue-x: %d\t",ev.value);
			}
			if(ev.code == ABS_Y)
			{
				y=yy = ev.value;
				printf("ev.vlue-y: %d\n",ev.value);
			}
			else if(ev.code == ABS_PRESSURE)
			{
				
				if(ev.value > 0)
				{
					//printf("按下\n");
					
				}
				else
				{
					//printf("松开\n");
					
					break;
				}
			}
		}
	}
	

	close(fd);
	return 0;
}













