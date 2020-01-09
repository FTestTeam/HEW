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

#define RAID_HP (10000)

static int	g_MicFream;	//��Q�ɓ������Ă��狩�Ԏ��Ԃ̃J�E���^
static int	g_EndFream;	//���яI����Ă���V�[����؂�ւ���܂ł̎���
static bool g_bMic = false;	//�}�C�N���g�����ǂ����̃t���O

static int g_textureID_Gage;
static float g_RaidHP = RAID_HP;

void Raid_Init()
{
	g_MicFream = Zako_GetBreakCount() * 60;
	g_EndFream = g_MicFream + 120;	//�}�C�N�ɋ��Ԏ��Ԃ��I����Ă���120�t���[����ɃV�[���`�F���W
	g_bMic = false;

	g_textureID_Gage = Texture_SetLoadFile("Asset/Texture/gage.png", 640, 32);
}

void Raid_UnInit()
{

}

void Raid_Update()
{
	if (Wall_GetPosition().z - 1.0f < Hammer_GetPosition().z && Wall_isUse()) {	//��Q�ɓ���������
		D3DXVECTOR3 w(Wall_GetPosition().x, Hammer_GetPosition().y, Wall_GetPosition().z-0.5f);
		Hammer_SetPosition(w);
		
		g_bMic = true;
		if (g_bMic) {
			if (Mic_GetVolume() > 80) {
				//Wall_MinAlpha(0.01f);
			}
			g_RaidHP -= Mic_GetVolume() / 10;
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
	
	Sprite_SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
	Sprite_Draw(g_textureID_Gage, SCREEN_WIDTH / 2, 16.0f, g_RaidHP / RAID_HP, 1.0f, 0.0f, 16.0f);
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	DebugFont_Draw(1, 24, "%f", g_RaidHP);
}