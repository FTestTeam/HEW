#include"debug_font.h"
#include"hammer.h"
#include"wall.h"
#include"mic.h"
#include"Scene.h"
#include"score.h"
#include"zako.h"
#include"texture.h"
#include"sprite.h"
#include"common.h"
#include"Result.h"
#include"cube.h"
#include"input.h"
#include"collect_data.h"

#define RAID_ADD_HP (10000)

#define RAID_START_HP (10000)
#define RAID_MAX_HP (RAID_START_HP + g_breakNum * RAID_ADD_HP)
#define RAID_SEC (5)

#define KIRETU_TEXTURE_SIZE_W (3509)
#define KIRETU_TEXTURE_SIZE_H (2481)

static int	g_MicFream;	//障害に当たってから叫ぶ時間のカウンタ
static int	g_EndFream;	//叫び終わってからシーンを切り替えるまでの時間
static bool g_bMic = false;	//マイクを使うかどうかのフラグ

static int g_textureID_Gage;
static float g_RaidHP = RAID_START_HP;
static float g_BufHP;
static float g_startHP;
static int g_breakNum = 0;

static int g_textureID_break;
static bool g_bUse_Break;

void Raid_Init()
{
	g_MicFream = RAID_SEC * 60;
	g_EndFream = g_MicFream + 120;	//マイクに叫ぶ時間が終わってから120フレーム後にシーンチェンジ
	g_bMic = false;

	g_startHP = g_RaidHP;
	g_BufHP = 0;

	g_textureID_Gage = Texture_SetLoadFile("Asset/Texture/gage.png", 640, 32);

	g_textureID_break = Texture_SetLoadFile("Asset/Texture/kiretu.tga", KIRETU_TEXTURE_SIZE_W, KIRETU_TEXTURE_SIZE_H);
	g_bUse_Break = false;

	Collect_Data_SetRaidStartHP(g_RaidHP);

	if (Scene_GetScene() == SCENE_RAID) {
		g_startHP = Collect_Data_GetData().raidHP;
	}
}

void Raid_UnInit()
{
	Result_GetScore(g_startHP - g_RaidHP);
}

void Raid_Update()
{
	if (Scene_GetScene() == SCENE_REPLAY_RAID) {
		if (Wall_GetPosition().z - 1.0f < Hammer_GetPosition().z && Wall_isUse()) {	//障害に当たったら
			D3DXVECTOR3 w(Wall_GetPosition().x, Hammer_GetPosition().y, Wall_GetPosition().z - 0.5f);
			Hammer_SetPosition(w);

			g_bMic = true;
			g_bUse_Break = true;
			if (g_bMic) {
				g_RaidHP -= (Collect_Data_GetData().vol * Zako_GetBreakCount()) / 100;
			}
		}

		if (g_RaidHP <= 0) {
			g_breakNum++;

			g_RaidHP = RAID_MAX_HP;
			g_startHP += RAID_MAX_HP;

			D3DXVECTOR3 w = Wall_GetPosition();
			w.z += 20;
			Wall_SetPosition(w);
		}

		if (g_bMic) {
			g_MicFream--;
			g_MicFream = max(g_MicFream, 0);
			g_EndFream--;
		}

		if (g_EndFream < 0) {
			Scene_SetNextScene(SCENE_TITLE);
		}
	}
	else {
		if (Wall_GetPosition().z - 1.0f < Hammer_GetPosition().z && Wall_isUse()) {	//障害に当たったら
			D3DXVECTOR3 w(Wall_GetPosition().x, Hammer_GetPosition().y, Wall_GetPosition().z - 0.5f);
			Hammer_SetPosition(w);

			g_bMic = true;
			g_bUse_Break = true;
			if (g_bMic) {
				g_RaidHP -= (Mic_GetVolume() * Zako_GetBreakCount()) / 100;
			}
		}

		if (g_RaidHP <= 0) {
			g_breakNum++;

			g_RaidHP = RAID_MAX_HP;
			g_startHP += RAID_MAX_HP;

			D3DXVECTOR3 w = Wall_GetPosition();
			w.z += 20;
			Wall_SetPosition(w);
		}

		if (g_bMic) {
			g_MicFream--;
			g_MicFream = max(g_MicFream, 0);
			g_EndFream--;
		}

		if (g_EndFream < 0) {
			Scene_SetNextScene(SCENE_RESULT);
		}
	}

#if defined(_DEBUG) || defined(DEBUG)
	if (Keyboard_IsTrigger(DIK_RETURN)) Scene_SetNextScene(SCENE_RESULT);
#endif
}

void Raid_Draw()
{
	Sprite_SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
	Sprite_Draw(g_textureID_Gage, SCREEN_WIDTH / 2, 16.0f, g_RaidHP / (RAID_MAX_HP), 1.0f, 0.0f, 16.0f);
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	if (g_bUse_Break) {
		D3DXMATRIX mtxW, mtxT,mtxS;
		D3DXMatrixTranslation(&mtxT, Hammer_GetPosition().x, Hammer_GetPosition().y+1.0f, Hammer_GetPosition().z);
		
		float Kiretu_size = (1.0f - (g_RaidHP / RAID_MAX_HP));

		D3DXMatrixScaling(&mtxS, Kiretu_size, Kiretu_size, 1.0f);
		mtxW = mtxS * mtxT;
		Cube_SetUV(KIRETU_TEXTURE_SIZE_W / 2 - (KIRETU_TEXTURE_SIZE_W / 2) * Kiretu_size, KIRETU_TEXTURE_SIZE_H / 2 - (KIRETU_TEXTURE_SIZE_H / 2) * Kiretu_size, (KIRETU_TEXTURE_SIZE_W / 2) * Kiretu_size*2, (KIRETU_TEXTURE_SIZE_H / 2) * Kiretu_size*2, g_textureID_break);
		Cube_Draw(&mtxW, g_textureID_break);
		DebugFont_Draw(1, 24 * 2, "%f", Kiretu_size);
	}

	DebugFont_Draw(1, 24, "スタート:%f", g_startHP);
	
	DebugFont_Draw(1, 24*3, "現在:%f", g_RaidHP);

	Score_Draw(g_MicFream / 60, 100, 100, 4, 0, 0);
}

bool Raid_IsBreak()
{
	return g_bUse_Break;
}