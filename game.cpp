#include<d3dx9.h>
#include"cube.h"
#include"model.h"
#include"mydirect3d.h"
#include"hammer.h"
#include"player.h"
#include"stage.h"
#include"wall.h"
#include"Scene.h"
#include"input.h"
#include"score.h"
#include"common.h"
#include"background.h"
#include"syutyusen.h"
#include"effect.h"
#include"fade.h"

void Game_Init()
{
	Score_Init();
	Player_Init();
	Hammer_Init();
	Stage_Init();
	Wall_Init();
	
	BackGround_Init();
}

void Game_UnInit()
{
	BackGround_UnInit();
	Player_UnInit();
	Hammer_Uninit();
	Stage_UnInit();
	Wall_UnInit();
}

void Game_Update()
{
	Player_Update();
	Hammer_Update();
	Stage_Update();
	Wall_Update();
	BackGround_Update();

	if (Keyboard_IsTrigger(DIK_1)) {
		Fade_Stert(120, D3DCOLOR_RGBA(255, 255, 255, 255), true);
	}
}

void Game_Draw() 
{
	Stage_Draw();
	BackGround_Draw();
	Player_Draw();
	Hammer_Draw();

	//Score_Draw(Score_GetScore() , Window_GetWidth() -48, 0, 7, false, true);
}