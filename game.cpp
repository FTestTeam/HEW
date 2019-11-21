#include<d3dx9.h>
#include"cube.h"
#include"model.h"
#include"mydirect3d.h"
#include"hammer.h"
#include"player.h"

void Game_Init()
{
	Player_Init();
	Hammer_Init();
}

void Game_UnInit()
{
	Player_UnInit();
	Hammer_Uninit();
}

void Game_Update()
{
	Player_Update();
	Hammer_Update();
}

void Game_Draw() 
{
	Player_Draw();
	Hammer_Draw();
}