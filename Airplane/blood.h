#pragma once
#include "GameRole.h"

class Blood : public CGameRole
{
public:
	Blood::Blood(int nRow, int nCol);
	~Blood();

	void ShowClear();				// �ڸǽ�ɫ
	void Show();					// ��ʾ��ɫ
	void ShowClearLife();			// �ڸǽ�ɫѪ��
	void ShowLife();				// ��ʾ��ɫѪ��
	void ShowBoom();				// ��ʾС�л���ը
	void GetNew();					// ��ȡ�µ�
	void MoveDown();				//����		
};

