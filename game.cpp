#include<d3dx9.h>
#include"cube.h"
#include"model.h"
#include"mydirect3d.h"
#include"hammer.h"
#include"player.h"

void Game_Init()
{
	Hammer_Init();
	Player_Init();
}

void Game_UnInit()
{
	Hammer_Uninit();
	Player_UnInit();
}

void Game_Update()
{
	Hammer_Update();
	Player_Update();
}

void Game_Draw() 
{
	Hammer_Draw();
	Player_Draw();
}