#include "easyx.h"
#include "Control.h"
#include "View.h"
#include "Blood.h"
Blood::Blood(int nRow, int nCol)
{
	m_nRow = nRow;
	m_nCol = nCol;
}

Blood::~Blood()
{

}

void Blood::ShowClear()
{
	putimage(m_nRow, m_nCol, &life1, SRCAND);
}

void Blood::Show()
{
	putimage(m_nRow, m_nCol, &life, SRCPAINT);
}

void Blood::ShowClearLife()
{

}

void Blood::ShowLife()
{

}

void Blood::GetNew()
{
	// 产生新小敌机
	m_nRow = rand() % (GAMEWIDTH - blood.getwidth());
	m_nCol = 0;
	m_Boom = 0;
}

void Blood::MoveDown()
{
	m_nCol += 10;
}






