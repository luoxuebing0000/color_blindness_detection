#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>//mmap/munmap
#include <sys/ioctl.h> //ioctl
#include <linux/fb.h>  //fb_var_screeninfo

int lcd_fd;
int *plcd;

/*
	lcd屏初始化函数：用来打开lcd屏，并将lcd屏映射到内存
*/
int lcd_init(void)
{
	/*1.打开要映射的那个文件 ---》获得文件描述符*/
	lcd_fd = open("/dev/fb0",O_RDWR);
	if(lcd_fd == -1)
	{
		perror("open lcd error");
		return -1;
	}

	/*获取屏幕信息*/
	struct fb_var_screeninfo fbinfo;
	int ret = ioctl(lcd_fd,FBIOGET_VSCREENINFO,&fbinfo); //fbinfo中就存放了lcd屏幕的信息了
	//屏幕文件的大小 = w*h*pixel/8 字节
	/*2.映射  将文件映射到内存空间中----》映射内存首地址*/
	plcd = mmap(
			NULL,//映射空间地址，NULL表示让系统选择
			fbinfo.xres*fbinfo.yres*fbinfo.bits_per_pixel/8,//映射空间大小,单位字节
			PROT_READ|PROT_WRITE,//映射空间的权限，可读可写
			MAP_SHARED,//映射标识位，共享映射
			lcd_fd,//文件描述符
			0//文件偏移量，映射起始位置
			);
	if(plcd == MAP_FAILED)
	{
		perror("mmap error");
		return -1;
	}
	
}

/*
	lcd屏解除函数：用来解除lcd屏的映射，关闭lcd屏
*/
int lcd_uninit(void)
{
	munmap(plcd,800*480*32/8);
	close(lcd_fd);
}


/*
	画点函数：根据传递的(x,y)坐标点，上色color
		x,y  	 点坐标
		color    点颜色值
*/
int lcd_draw_point(int x,int y,unsigned int color)
{
	*(plcd+x+y*800) = color;
}

/*
	清屏函数:将从(x0，y0)开始的w宽，h高的区域清空成color颜色
		x0,y0 		清屏起点
		w			清屏宽 像素点
		h			清屏高    像素点
		color       清屏颜色
*/
int lcd_show_block(int x0,int y0,int w,int h,unsigned int color)
{
	int x,y;
	for(y=y0;y<y0+1;y++)
	{
		for(x=x0;x<x0+1;x++)
		{
			lcd_draw_point(x, y, color);
		}
	}
}




