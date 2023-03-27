#pragma comment(lib, "WINMM.LIB")
#include <stdio.h>
#include <easyx.h>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <mmsystem.h>
#include <conio.h>
#include "Enemy.h"
#include "Ship.h"
#include "Bullet.h"
#include "control.h"
#include "view.h"
#include "GameRole.h"
#define RAND_MAX 0x7fff


int main()
{
	srand((unsigned)time(NULL));
	initgraph(GAMEWIDTH, GAMEHIGHT);
	game();
	closegraph;
	return 0;
}
