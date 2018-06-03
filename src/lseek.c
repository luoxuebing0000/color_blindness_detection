#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "mmap_lcd.h"

/*解析bmp图片*/
int seek(char *file1)
{
	int fd = open(file1,O_RDWR);
	if(fd == -1)
	{
		perror("open bmp error");
		return -1;
	}

	/*解析长度 0x02      4个字节*/
	int i = 0;
	unsigned char ch[4] = {0};
	/*定位文件偏移量到指定位置*/
	lseek(fd,0x02,SEEK_SET);
	/*读取对应大小的数据量*/
	read(fd,ch,4);
	/*按一定顺序组合 小端模式*/
	int len = ch[3]<<24 | ch[2]<<16 | ch[1]<<8 | ch[0];
	//printf("file size is: %d\n",len);

	/*宽度    0x12   4字节*/
	lseek(fd,0x12,SEEK_SET);
	read(fd,ch,4);
	int w = ch[3]<<24 | ch[2]<<16 | ch[1]<<8 | ch[0];
	//printf("宽度:%d\n",w);

	/*高度    0x16   4字节*/
	lseek(fd,0x16,SEEK_SET);
	read(fd,ch,4);
	int h = ch[3]<<24 | ch[2]<<16 | ch[1]<<8 | ch[0];
	//printf("高度:%d\n",h);

	/*色深    0x1c   2字节*/
	lseek(fd,0x1c,SEEK_SET);
	read(fd,ch,2);
	int bits_pix =  ch[1]<<8 | ch[0];
	//printf("色深:%d\n",bits_pix);

	/*位图数据偏移地址          0x0a  4字节*/
	lseek(fd,0x0a,SEEK_SET);
	read(fd,ch,4);
	int d_off = ch[3]<<24 | ch[2]<<16 | ch[1]<<8 | ch[0];
	//printf("地址偏移:%d\n",d_off);

	int pix_size = w*h*bits_pix/8; //像素数组存放的字节数
	
	unsigned char *data = (unsigned char *)malloc(pix_size);
	lseek(fd,d_off,SEEK_SET);
	read(fd,data,pix_size);
	unsigned char a,r,g,b;
	unsigned int color;
	unsigned char * tmp = data; //用临时变量保存空间首地址
	int x,y;
	int m=0,n=0;
	if(w==110)
	{
		m=690;
		n=155;
	}
	else if(w==250)
	{
		m=225;
		n=440;
	}
	for(y=h-1+n;y>=n;y--)
	{
		for(x=m;x<w+m;x++)
		{
			b = *tmp++;
			g = *tmp++;
			r = *tmp++;
			a = bits_pix==24?0:*tmp++;
			color = a<<24 | r<<16 | g<<8 | b;
			//printf("(%d,%d) 0x%x\n",x,y,color);
			lcd_draw_point(x,y,color);
		}
	}
	m=n=0;
	free(data);
	close(fd);

	return 0;
}

