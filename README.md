# 色盲检测系统

## 说明
	
	* 项目说明
		> 此项目仅适用于粤嵌提供的arm型嵌入式开发板，里面涉及到文件IO操作、
		> 偏移量操作、bmp图片解析、屏幕点击、滑动、按压事件的操作、随机数的生成。

	* 编译说明
		> 搭建了arm的交叉编译环境
		> 编译命令： arm-linux-gcc *.c -o main -lpthread (在./src目录里面)　	


## 5张色盲检测图片的正确按钮设定

1. 0.bmp 正确按钮是：第二个，用1表示
2. 1.bmp 正确按钮是：第三个，用2表示
3. 2.bmp 正确按钮是：第一个，用0表示
4. 3.bmp 正确按钮是：第三个，用2表示
5. 4.bmp 正确按钮是：第三个，用2表示

* 程序中的f变量代表啥
	> f代表的是图片的名字，不加后缀名，非别为0、1、2、3、4

* 那可以统计下共性
	> f = 0 的时候，返回第二个按钮
	> f = 2 的时候，返回第一个按钮
 	> f = 1/3/4 的时候，返回第三个按钮

## bmps数组记录

1. bmps[0] === 主界面
2. bmps[1] === 说明界面
3. bmps[2] === 错误处理界面
4. bmps[3] === 色觉正常界面
5. bmps[4] === 红色色盲界面
6. bmps[5] === 绿色色盲界面
7. bmps[6] === 红绿色盲界面


## 图片红绿色盲检测规定
1. 0.bmp、3.bmp：红色色盲检测

2. 1.bmp、2.bmp：绿色色盲

3. 4.bmp：红绿色盲

## arr2[3] 定义 === 红绿色盲存储定义

1. 第一个元素为红色色盲检测：0表示正常，>=1表示红色色盲
2. 第二个元素为红色色盲检测：0表示正常，>=1表示绿色色盲
3. 第三个元素为红色色盲检测：0表示正常，>=1表示红绿色盲


## 后期利用arr可完善功能
	
	* 利用arr2数组完善一些功能
		> 如果点击右边按钮至少点击右边按钮5次才能查看结果，可以通过求arr2里面的总和，
		> 如果>=5才可以点击查看结果按钮，如果没有，则点击查看结果无效，弹出一个对话框
		> 提示点击至少5次才有效果，提供继续检测和返回主界面按钮

## 感谢
1. 感谢邓清勇博士
2. 感谢粤嵌工程师欧阳华亮