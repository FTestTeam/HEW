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

void Game_Init()
{
	Score_Init();
	Player_Init();
	Hammer_Init();
	Stage_Init();
	Wall_Init();
}

void Game_UnInit()
{
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

	if(Keyboard_IsTrigger(DIK_RETURN))
	Scene_SetNextScene(SCENE_RESULT);
}

void Game_Draw() 
{
	Player_Draw();
	Hammer_Draw();
	Stage_Draw();
	Wall_Draw();

	Score_Draw(Score_GetScore() , SCREEN_WIDTH -48, 0, 7, false, true);
}