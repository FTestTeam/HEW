#include "Scene.h"
#include "Title.h"
#include "game.h"
#include "texture.h"
#include "Result.h"

SCENE g_NextScene = SCENE_TITLE;		//最初の画面 完成版はタイトルにする
SCENE g_Scene = g_NextScene;



void Scene_Init(void)
{
	switch (g_NextScene)
	{
	case SCENE_TITLE:
		Title_Init();
		break;
	case SCENE_GAME:
		Game_Init();
		break;
	case SCENE_RESULT:
		Result_Init();
		break;
	default:
		break;
	};
 	if (Texture_Load() < 0) {
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
	case SCENE_GAME:
		Game_Uninit();
		break;
	case SCENE_RESULT:
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
	case SCENE_GAME:
		Game_Update();
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
	case SCENE_GAME:
		Game_Draw();
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