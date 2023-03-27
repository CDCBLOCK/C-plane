#include "view.h"
#include "easyx.h"
#include "Enemy.h"
#include "SmallEnemy.h"
#include"graphics.h"
#include "blood.h"
#pragma warning(disable:4996);
#pragma warning(disable:4081);

IMAGE boom1, boom2, boom3, boom4;
IMAGE smallboom1, smallboom2, smallboom3, smallboom4;
MOUSEMSG m_msg;
char ch;

void LoadBoom()
{	
	loadimage(&boom1, _T("res\\boom\\boom1.png"));
	loadimage(&boom2, _T("res\\boom\\boom2.png"));
	loadimage(&boom3, _T("res\\boom\\boom3.png"));
	loadimage(&boom4, _T("res\\boom\\boom4.png"));

	loadimage(&smallboom1, _T("res\\boom\\smallboom1.png"));
	loadimage(&smallboom2, _T("res\\boom\\smallboom2.png"));
	loadimage(&smallboom3, _T("res\\boom\\smallboom3.png"));
	loadimage(&smallboom4, _T("res\\boom\\smallboom4.png"));
}

void InitGame()
{
	LoadBoom();
	mciSendString(_T("open res\\music.mp3 alias mysong"), NULL, 0, NULL);		// 打开音乐
	mciSendString(_T("play MySong repeat"), NULL, 0, NULL);         			// 循环播放


	// 加载飞机
	loadimage(&ship, _T("res\\ufo.png"));
	loadimage(&ship1, _T("res\\ufo2.png"));

	// 加载敌机
	loadimage(&enemy, _T("res\\enemy.png"));	
	loadimage(&enemy1, _T("res\\enemy1.png"));
	// 加载小敌机
	loadimage(&smallenemy, _T("res\\smallenemy.png"));
	loadimage(&smallenemy1, _T("res\\smallenemy1.png"));
	loadimage(&life, _T("res\\life.png"));
	loadimage(&life1, _T("res\\life1.png"));
	myenemy.direction = DOWN;
	myenemy.m_nStartHight = 0;
	myenemy.m_Move = 0;
	myenemy.m_Fire = 0;
	myenemy.m_Boom = 0;	
}






void ShowBullet()
{
	// 显示飞船子弹
	for (Iter = VectorBullets.begin(); Iter != VectorBullets.end(); Iter++)
	{
		if (VectorBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		(*Iter)->ShowClear();
		(*Iter)->MoveUp();
		(*Iter)->ShowYellow();
	}

	// 显示敌机子弹
	for (Iter = VectorEnenyBullets.begin(); Iter != VectorEnenyBullets.end(); Iter++)
	{
		if (VectorEnenyBullets.size() == 0)
		{
			break;
		}
		if (*Iter == nullptr)
		{
			break;
		}
		(*Iter)->ShowClear();
		(*Iter)->MoveDown();
		(*Iter)->ShowRed();
	}
}

void ShowInPut()
{
	if (myinput & UPINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & DOWNINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & LEFTINPUT)
	{
		myship.ShowClear();
	}

	if (myinput & RIGHTINPUT)
	{
		myship.ShowClear();
	}
}
void Showbk0(){
	loadimage(&background, _T("res\\bg2.jpg"), GAMEWIDTH, GAMEHIGHT, true);
	putimage(0, 0, &background);		// 开始界面
	
	
}
void Showbk1(){
	loadimage(&background, _T("res\\background6.bmp"), GAMEWIDTH, GAMEHIGHT, true);
	putimage(0, 0, &background);		// 开始界面

}



bool button(int a, int b, wchar_t str[])
{
	static int x, y;																// 鼠标坐标

	setfillcolor(RGB(100, 100, 100));
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);					// 绘制边框

	x = m_msg.x;
	y = m_msg.y;																	// 获取坐标

	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 30) // 获得焦点显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);

		if (m_msg.uMsg == WM_LBUTTONUP)
		{
			m_msg.uMsg = WM_MOUSEMOVE;

			return 1;
		}
	}
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 25;
	wcscpy_s(f.lfFaceName, L"微软雅黑 Light");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);	// 输出文字

	return 0;
	
}


void game(){
	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	while (1)
	{
		if (_kbhit())		// 键盘消息获取
		{
			ch = _getch();	// 键盘消息获取
			if (ch == 27)	// 按 Esc 退出
			{
				break;
			}
		}


		while (MouseHit())	// 鼠标消息获取
			m_msg = GetMouseMsg();

		loadimage(&background, _T("res\\lzyback.jpg"), GAMEWIDTH, GAMEHIGHT, true);
		putimage(0, 0, &background);		// 开始界面

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(70, 0, L"微软雅黑");
			outtextxy(375 + i, 100 + i, L"飞 机 大 战");
		}
		settextcolor(WHITE);
		settextstyle(70, 0, L"微软雅黑");
		outtextxy(375 + 3, 100 + 3, L"飞 机 大 战");		// 标题输出

		if (button(475, 250, L"黄 昏"))		// 黄昏系列按钮
		{
			play0(); 

		}
		if (button(475, 300, L"黑 夜")){
			play1();
		}

		if (button(475, 350, L"规则")){
			while (1)
			{

				while (MouseHit())							// 鼠标消息获取
					m_msg = GetMouseMsg();

												// 绘制背景

				for (int i = 0; i <= 3; i++)
				{
					settextcolor(RGB(100, 100, 100));
					settextstyle(52, 0, L"黑体");
					outtextxy(475 + i, 50 + i, L"帮 助");
				}
				settextcolor(WHITE);
				settextstyle(52, 0, L"黑体");
				outtextxy(475 + 3, 50 + 3, L"帮 助");		// 标题输出

				setfillcolor(RGB(100, 100, 100));
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID, 5);
				fillrectangle(425, 110, 900, 390);			// 绘制边框


				LOGFONT f;
				gettextstyle(&f);
				f.lfHeight = 25;
				wcscpy_s(f.lfFaceName, L"微软雅黑 Light");
				f.lfQuality = ANTIALIASED_QUALITY;
				settextstyle(&f);
				settextcolor(WHITE);
				outtextxy(600, 130, L"欢迎阅读规则");
				outtextxy(500, 170, L"我们的游戏属于");
				outtextxy(500, 200, L"持久性游戏");
				outtextxy(500, 230, L"考验玩家注意力和技术");
				outtextxy(500, 260, L"WSAD 上下左右，按k键射击");
				outtextxy(500, 290, L"进入游戏");
				outtextxy(500, 320, L"开始你的冒险吧！");	// 信息输出

				if (button(600, 400, L"回到主页"))					// 回到主页按钮
					break;

				FlushBatchDraw();
			}
		}
		
		LOGFONT f;
		gettextstyle(&f);
		f.lfWidth = 10;
		wcscpy_s(f.lfFaceName, L"微软雅黑 Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		settextcolor(WHITE);


		outtextxy(425, 200, L"按 Esc 退出游戏");	// 输出其他

		FlushBatchDraw();
		Sleep(5);

		
	}
	EndBatchDraw();
}


void play0(){
	int nSign = 1;
	

	while (nSign != -1)
	{
		InitGame();
		GetNewShip();
		GetNewEnemy();
		GetNewSmallEnemy();
		mygamecontrol.m_nScore = 0;
		RoleVector.push_back(&myship);
		RoleVector.push_back(&myenemy);
		RoleVector.push_back(&mysmallenemy);
		while (nSign > 0)
		{

			nSign = HandleGameOver();



			GetOrder();							// 获取键盘指令
			ShowInPut();						// 操作前掩盖飞船
			DealInPut();						// 处理操作
			EnemyMove();				        // 敌机移动
			Showbk0();
			// 绘制游戏各个角色
			for (size_t i = 0; i < RoleVector.size(); i++)
			{
				RoleVector[i]->ShowClearLife();
				RoleVector[i]->ShowLife();
				RoleVector[i]->ShowClear();
				RoleVector[i]->Show();
				RoleVector[i]->ShowBoom();
			}

			ShowBullet();						// 显示飞船、敌机子弹		
			mygamecontrol.ShowScore();			// 显示分数

			DeleteMemory();						 
			MakeEnemyBullet0();					// 产生敌机子弹



			IsEnenmyHurt();						// 判断敌机是否中弹
			IsShipHurt();						// 判断飞船是否中弹					
			SmallHitShip();						// 判断小敌机是否撞到飞船		
			IsBullertHitSmall();				// 小敌机是否被击中
			HandleBoom();  // 处理爆炸状态	
			nSign = HandleGameOver();
			HpSleep(1);
			FlushBatchDraw();

		}

		RoleVector.pop_back();
		RoleVector.pop_back();
		RoleVector.pop_back();
		nSign = 1;

	}
}


void play1(){
	int nSign = 1;

	while (nSign != -1)
	{
		if (nSign == -3){
			game();
			break;
		}
		InitGame();
		GetNewShip();
		GetNewEnemy();
		GetNewSmallEnemy();
		mygamecontrol.m_nScore = 0;
		RoleVector.push_back(&myship);
		RoleVector.push_back(&myenemy);
		RoleVector.push_back(&mysmallenemy);

		while (nSign > 0)
		{

			nSign = HandleGameOver();



			GetOrder();							// 获取键盘指令
			ShowInPut();						// 操作前掩盖飞船
			DealInPut();						// 处理操作
			EnemyMove();				        // 敌机移动
			Showbk1();
			// 绘制游戏各个角色
			for (size_t i = 0; i < RoleVector.size(); i++)
			{
				RoleVector[i]->ShowClearLife();
				RoleVector[i]->ShowLife();
				RoleVector[i]->ShowClear();
				RoleVector[i]->Show();
				RoleVector[i]->ShowBoom();
			}

			ShowBullet();						// 显示飞船、敌机子弹		
			mygamecontrol.ShowScore();			// 显示分数

			MakeEnemyBullet1();					// 产生敌机子弹

			DeleteMemory();						// 释放内存


			IsEnenmyHurt();						// 判断敌机是否中弹				
			SmallHitShip();						// 判断小敌机是否撞到飞船		
			IsBullertHitSmall();				// 小敌机是否被击中
			IsShipHurt();						// 判断飞船是否中弹	
			HandleBoom();  // 处理爆炸状态	
			nSign = HandleGameOver();
			
		
			HpSleep(1);
			FlushBatchDraw();

		}

		RoleVector.pop_back();
		RoleVector.pop_back();
		RoleVector.pop_back();
		nSign = 1;

	}
}

