#pragma once
#include "control.h"
#include "Ship.h"
#include <time.h>		// 时间作为随机生成种子
#include <conio.h>		// 获取键盘信息用
#include <vector>		// 使用 STL vector
#include <algorithm>	// 使用 random_shuffle 函数
#include <graphics.h>	// 引用图形库头文件

void InitGame();// 初始化游戏
void ShowBullet();				// 显示子弹
void ShowInPut();				// 根据操作显示
void LoadBoom();
void Showbk0();
void Showbk1();
void game();
bool button(int , int , wchar_t);
void play0();
void play1();

extern IMAGE boom1, boom2, boom3, boom4, background;
extern IMAGE smallboom1, smallboom2, smallboom3, smallboom4;