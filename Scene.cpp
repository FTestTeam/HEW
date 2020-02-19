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
#include "syutyusen.h"
#include "wall.h"
#include "effect.h"
#include "tornado.h"
#include "collect_data.h"
#include "replay.h"
#include "fade.h"
#include "input_name.h"
#include "sound.h"
#include "input.h"

SCENE g_NextScene = SCENE_TITLE;		//最初の画面 完成版はタイトルにする
SCENE g_Scene = g_NextScene;

void Scene_Init(void)
{
	switch (g_NextScene)
	{
	case SCENE_TITLE:
		Title_Init();

		break;

	case SCENE_ZAKO:
		Collect_Data_Init(WRITE);
		PlaySound(SOUND_LABEL_BGM_ZAKO);

		Effect_Init();
		Game_Init();
		Camera_Init();
		Zako_Init();
		Syutyusen_Init();
		Tornado_Init();
		break;

	case SCENE_RAID:
		PlaySound(SOUND_LABEL_BGM_RAID);

		Effect_Init();
		Game_Init();
		Camera_Init();
		Wall_Init();
		Raid_Init();
		Syutyusen_Init();
		Tornado_Init();
		break;

	case SCENE_RESULT:
		Score_Init();
		Result_Init();
		iName_Init();
		break;

	case SCENE_REPLAY_ZAKO:
		Collect_Data_UnInit();

		PlaySound(SOUND_LABEL_BGM_RESULT);

		Score_Init();
		Result_Init();
		iName_Init();

		Collect_Data_Init(READ);

		Effect_Init();
		Game_Init();
		Camera_Init();
		Zako_Init();
		Syutyusen_Init();
		Tornado_Init();
		Replay_Init();
		break;
	case SCENE_REPLAY_RAID:
		Effect_Init();
		Game_Init();
		Camera_Init();
		Wall_Init();
		Raid_Init();
		Syutyusen_Init();
		Tornado_Init();
		Replay_Init();
		break;
	default:
		break;
	};
 	if (Model_Load() < 0 || Texture_Load() < 0) {
		MessageBox(NULL, "異常が発生したよ(´･ω･`)", "エラーパターン:Texture_Load() < 0", MB_OK);
	}

	Fade_Stert(60, D3DCOLOR_RGBA(255, 255, 255, 255), false);
}

void Scene_Uninit(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Uninit();

		break;
	case SCENE_ZAKO:
		StopSound(SOUND_LABEL_BGM_ZAKO);

		Effect_UnInit();
		Game_UnInit();
		Zako_UnInit();
		Syutyusen_UnInit();
		Tornado_UnInit();
		break;
	case SCENE_RAID:
		StopSound(SOUND_LABEL_BGM_RAID);

		Effect_UnInit();
		Game_UnInit();
		Wall_UnInit();
		Raid_UnInit();
		Syutyusen_UnInit();
		Tornado_UnInit();
		break;
	case SCENE_RESULT:
		Score_Uninit();
		Result_Uninit();
		iName_Uninit();

		Collect_Data_UnInit();
		break;

	case SCENE_REPLAY_ZAKO:		
		Effect_UnInit();
		Game_UnInit();
		Zako_UnInit();
		Syutyusen_UnInit();
		Tornado_UnInit();
		Replay_UnInit();
		break;
	case SCENE_REPLAY_RAID:
		StopSound();

		Score_Uninit();
		Result_Uninit();
		iName_Uninit();

		Effect_UnInit();
		Game_UnInit();
		Wall_UnInit();
		Raid_UnInit();
		Syutyusen_UnInit();
		Tornado_UnInit();
		Replay_UnInit();
		break;
	default:
		break;
	};

	Fade_Stert(60, D3DCOLOR_RGBA(255, 255, 255, 255), true);
}

void Scene_Update(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		Title_Update();
		break;
	case SCENE_ZAKO:
		Effect_Update();
		Game_Update();
		Zako_Update();
		Syutyusen_Update();
		Tornado_Update();

		Collect_Data_Save();
		break;
	case SCENE_RAID:
		Effect_Update();
		Game_Update();
		Wall_Update();
		Raid_Update();
		Syutyusen_Update();
		Tornado_Update();

		Collect_Data_Save();
		break;
	case SCENE_RESULT:
		Result_Update();
		iName_Update();
		break;

	case SCENE_REPLAY_ZAKO:
		Collect_Data_Load();

		Result_Update();
		iName_Update();

		Effect_Update();
		Game_Update();
		Zako_Update();
		Syutyusen_Update();
		Tornado_Update();
		Replay_Update();
		break;
	case SCENE_REPLAY_RAID:
		Collect_Data_Load();

		Result_Update();
		iName_Update();

		Effect_Update();
		Game_Update();
		Wall_Update();
		Raid_Update();
		Syutyusen_Update();
		Tornado_Update();
		Replay_Update();
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
	case SCENE_ZAKO:
		Game_Draw();
		Zako_Draw();
		Tornado_Draw();
		Effect_Draw();
		Syutyusen_Draw();
		break;
	case SCENE_RAID:
		Game_Draw();
		Wall_Draw();
		Effect_Draw();
		Raid_Draw();
		Tornado_Draw();
		Syutyusen_Draw();
		break;
	case SCENE_RESULT:
		Result_Draw();
		iName_Draw();
		break;

	case SCENE_REPLAY_ZAKO:
		Game_Draw();
		Zako_Draw();
		Tornado_Draw();
		Effect_Draw();
		Syutyusen_Draw();
		//Replay_Draw();

		Result_Draw();
		iName_Draw();
		break;
	case SCENE_REPLAY_RAID:
		Game_Draw();
		Wall_Draw();
		Effect_Draw();
		Raid_Draw();
		Tornado_Draw();
		Syutyusen_Draw();
		//Replay_Draw();

		Result_Draw();
		iName_Draw();
		break;
	default:
		break;
	};

}


void Scene_SetNextScene(SCENE nextScene)
{
	g_NextScene = nextScene;
}

SCENE Scene_GetScene()
{
	return g_Scene;
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