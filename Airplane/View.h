#pragma once
#include "control.h"
#include "Ship.h"
#include <time.h>		// ʱ����Ϊ�����������
#include <conio.h>		// ��ȡ������Ϣ��
#include <vector>		// ʹ�� STL vector
#include <algorithm>	// ʹ�� random_shuffle ����
#include <graphics.h>	// ����ͼ�ο�ͷ�ļ�

void InitGame();// ��ʼ����Ϸ
void ShowBullet();				// ��ʾ�ӵ�
void ShowInPut();				// ���ݲ�����ʾ
void LoadBoom();
void Showbk0();
void Showbk1();
void game();
bool button(int , int , wchar_t);
void play0();
void play1();

extern IMAGE boom1, boom2, boom3, boom4, background;
extern IMAGE smallboom1, smallboom2, smallboom3, smallboom4;