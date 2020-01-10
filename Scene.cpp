#include "Scene.h"
#include "Title.h"
#include "game.h"
#include "texture.h"
#include "Result.h"
#include "model.h"
#include "score.h"
#include "raid.h"
#include "zako.h"
#include "camera.h"
#include "wall.h"
#include "syutyusen.h"

SCENE g_NextScene = SCENE_TITLE;		//最初の画面 完成版はタイトルにする
SCENE g_Scene = g_NextScene;

void Scene_Init(void)
{
	switch (g_NextScene)
	{
	case SCENE_TITLE:
		Title_Init();
		break;
	case SCENE_RAID:
		Game_Init();
		Camera_Init();
		Wall_Init();
		Raid_Init();
		break;
	case SCENE_ZAKO:
		Game_Init();
		Camera_Init();
		Zako_Init();
		Syutyusen_Init();
		break;
	case SCENE_RESULT:
		Score_Init();
		Result_Init();
		break;
	default:
		break;
	};
 	if (Model_Load() < 0||Texture_Load() < 0) {
		MessageBox(NULL, "異常が発生したよ(´･ω･`)", "エラーパターン:Texture_Load() < 0", MB_OK);
	}
}

void Scene_Uninit(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Uninit();
		break;
	case SCENE_RAID:
		Game_UnInit();
		Wall_UnInit();
		Raid_UnInit();
		break;
	case SCENE_ZAKO:
		Game_UnInit();
		Zako_UnInit();
		Syutyusen_UnInit();
		break;
	case SCENE_RESULT:
		Score_Uninit();
		Result_Uninit();
		break;
	default:
		break;
	};
}

void Scene_Update(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Update();
		break;
	case SCENE_RAID:
		Game_Update();
		Wall_Update();
		Raid_Update();
		break;
	case SCENE_ZAKO:
		Game_Update();
		Zako_Update();
		Syutyusen_Update();
		break;
	case SCENE_RESULT:
		Result_Update();
		break;
	default:
		break;
	};
}

void Scene_Draw(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Draw();
		break;
	case SCENE_RAID:
		Game_Draw();
		Wall_Draw();
		Raid_Draw();
		break;
	case SCENE_ZAKO:
		Game_Draw();
		Zako_Draw();
		Syutyusen_Draw();
		break;
	case SCENE_RESULT:
		Result_Draw();
		break;
	default:
		break;
	};
}


void Scene_SetNextScene(SCENE nextScene)
{
	g_NextScene = nextScene;
}

bool Scene_Change(void)
{
	if(g_NextScene != g_Scene){
		Scene_Uninit();
		Scene_Init();
		g_Scene = g_NextScene;
	}

	if (g_NextScene == SCENE_END) {
		return true;
	}
	return false;
}