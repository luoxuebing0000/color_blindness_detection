#ifndef MMAP_LCD_H
#define MMAP_LCD_H
extern int lcd_init(void);
extern int lcd_uninit(void);
extern int lcd_draw_point(int x,int y,unsigned int color);
extern int lcd_show_block(int x0,int y0,int w,int h,unsigned int color);

#endif