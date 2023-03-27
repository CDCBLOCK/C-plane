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
	mciSendString(_T("open res\\music.mp3 alias mysong"), NULL, 0, NULL);		// ������
	mciSendString(_T("play MySong repeat"), NULL, 0, NULL);         			// ѭ������


	// ���طɻ�
	loadimage(&ship, _T("res\\ufo.png"));
	loadimage(&ship1, _T("res\\ufo2.png"));

	// ���صл�
	loadimage(&enemy, _T("res\\enemy.png"));	
	loadimage(&enemy1, _T("res\\enemy1.png"));
	// ����С�л�
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
	// ��ʾ�ɴ��ӵ�
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

	// ��ʾ�л��ӵ�
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
	putimage(0, 0, &background);		// ��ʼ����
	
	
}
void Showbk1(){
	loadimage(&background, _T("res\\background6.bmp"), GAMEWIDTH, GAMEHIGHT, true);
	putimage(0, 0, &background);		// ��ʼ����

}



bool button(int a, int b, wchar_t str[])
{
	static int x, y;																// �������

	setfillcolor(RGB(100, 100, 100));
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);					// ���Ʊ߿�

	x = m_msg.x;
	y = m_msg.y;																	// ��ȡ����

	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 30) // ��ý�����ʾ
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
	wcscpy_s(f.lfFaceName, L"΢���ź� Light");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);	// �������

	return 0;
	
}


void game(){
	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	while (1)
	{
		if (_kbhit())		// ������Ϣ��ȡ
		{
			ch = _getch();	// ������Ϣ��ȡ
			if (ch == 27)	// �� Esc �˳�
			{
				break;
			}
		}


		while (MouseHit())	// �����Ϣ��ȡ
			m_msg = GetMouseMsg();

		loadimage(&background, _T("res\\lzyback.jpg"), GAMEWIDTH, GAMEHIGHT, true);
		putimage(0, 0, &background);		// ��ʼ����

		for (int i = 0; i <= 3; i++)
		{
			settextcolor(RGB(100, 100, 100));
			settextstyle(70, 0, L"΢���ź�");
			outtextxy(375 + i, 100 + i, L"�� �� �� ս");
		}
		settextcolor(WHITE);
		settextstyle(70, 0, L"΢���ź�");
		outtextxy(375 + 3, 100 + 3, L"�� �� �� ս");		// �������

		if (button(475, 250, L"�� ��"))		// �ƻ�ϵ�а�ť
		{
			play0(); 

		}
		if (button(475, 300, L"�� ҹ")){
			play1();
		}

		if (button(475, 350, L"����")){
			while (1)
			{

				while (MouseHit())							// �����Ϣ��ȡ
					m_msg = GetMouseMsg();

												// ���Ʊ���

				for (int i = 0; i <= 3; i++)
				{
					settextcolor(RGB(100, 100, 100));
					settextstyle(52, 0, L"����");
					outtextxy(475 + i, 50 + i, L"�� ��");
				}
				settextcolor(WHITE);
				settextstyle(52, 0, L"����");
				outtextxy(475 + 3, 50 + 3, L"�� ��");		// �������

				setfillcolor(RGB(100, 100, 100));
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID, 5);
				fillrectangle(425, 110, 900, 390);			// ���Ʊ߿�


				LOGFONT f;
				gettextstyle(&f);
				f.lfHeight = 25;
				wcscpy_s(f.lfFaceName, L"΢���ź� Light");
				f.lfQuality = ANTIALIASED_QUALITY;
				settextstyle(&f);
				settextcolor(WHITE);
				outtextxy(600, 130, L"��ӭ�Ķ�����");
				outtextxy(500, 170, L"���ǵ���Ϸ����");
				outtextxy(500, 200, L"�־�����Ϸ");
				outtextxy(500, 230, L"�������ע�����ͼ���");
				outtextxy(500, 260, L"WSAD �������ң���k�����");
				outtextxy(500, 290, L"������Ϸ");
				outtextxy(500, 320, L"��ʼ���ð�հɣ�");	// ��Ϣ���

				if (button(600, 400, L"�ص���ҳ"))					// �ص���ҳ��ť
					break;

				FlushBatchDraw();
			}
		}
		
		LOGFONT f;
		gettextstyle(&f);
		f.lfWidth = 10;
		wcscpy_s(f.lfFaceName, L"΢���ź� Light");
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		settextcolor(WHITE);


		outtextxy(425, 200, L"�� Esc �˳���Ϸ");	// �������

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



			GetOrder();							// ��ȡ����ָ��
			ShowInPut();						// ����ǰ�ڸǷɴ�
			DealInPut();						// �������
			EnemyMove();				        // �л��ƶ�
			Showbk0();
			// ������Ϸ������ɫ
			for (size_t i = 0; i < RoleVector.size(); i++)
			{
				RoleVector[i]->ShowClearLife();
				RoleVector[i]->ShowLife();
				RoleVector[i]->ShowClear();
				RoleVector[i]->Show();
				RoleVector[i]->ShowBoom();
			}

			ShowBullet();						// ��ʾ�ɴ����л��ӵ�		
			mygamecontrol.ShowScore();			// ��ʾ����

			DeleteMemory();						 
			MakeEnemyBullet0();					// �����л��ӵ�



			IsEnenmyHurt();						// �жϵл��Ƿ��е�
			IsShipHurt();						// �жϷɴ��Ƿ��е�					
			SmallHitShip();						// �ж�С�л��Ƿ�ײ���ɴ�		
			IsBullertHitSmall();				// С�л��Ƿ񱻻���
			HandleBoom();  // ����ը״̬	
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



			GetOrder();							// ��ȡ����ָ��
			ShowInPut();						// ����ǰ�ڸǷɴ�
			DealInPut();						// �������
			EnemyMove();				        // �л��ƶ�
			Showbk1();
			// ������Ϸ������ɫ
			for (size_t i = 0; i < RoleVector.size(); i++)
			{
				RoleVector[i]->ShowClearLife();
				RoleVector[i]->ShowLife();
				RoleVector[i]->ShowClear();
				RoleVector[i]->Show();
				RoleVector[i]->ShowBoom();
			}

			ShowBullet();						// ��ʾ�ɴ����л��ӵ�		
			mygamecontrol.ShowScore();			// ��ʾ����

			MakeEnemyBullet1();					// �����л��ӵ�

			DeleteMemory();						// �ͷ��ڴ�


			IsEnenmyHurt();						// �жϵл��Ƿ��е�				
			SmallHitShip();						// �ж�С�л��Ƿ�ײ���ɴ�		
			IsBullertHitSmall();				// С�л��Ƿ񱻻���
			IsShipHurt();						// �жϷɴ��Ƿ��е�	
			HandleBoom();  // ����ը״̬	
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

