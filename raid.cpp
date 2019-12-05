#include"hammer.h"
#include"wall.h"
#include"mic.h"
#include"Scene.h"
#include"score.h"

static int	g_MicFream;
static int	g_EndFream;
static bool g_bMic = false;

void Raid_Init()
{
	g_MicFream = 120;
	g_EndFream = g_MicFream + 120;
	g_bMic = false;
}

void Raid_UnInit()
{

}

void Raid_Update()
{
	if (Wall_GetPosition().z - 1.0f < Hammer_GetPosition().z && Wall_isUse()) {
		Hammer_SetPosition(POS_Z,Wall_GetPosition().z - 1.0f);
		g_bMic = true;
		if (g_MicFream < 120) {
			if (Mic_GetVolume() > 100) {
				Wall_MinAlpha(0.01f);
			}
		}
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

void Raid_Draw()
{
	Score_Draw(g_MicFream / 60, 100, 100, 4, 0, 0);
}