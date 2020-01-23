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

#define RAID_ADD_HP (10000)

#define RAID_START_HP (10000)
#define RAID_SEC (5)

static int	g_MicFream;	//��Q�ɓ������Ă��狩�Ԏ��Ԃ̃J�E���^
static int	g_EndFream;	//���яI����Ă���V�[����؂�ւ���܂ł̎���
static bool g_bMic = false;	//�}�C�N���g�����ǂ����̃t���O

static int g_textureID_Gage;
static float g_RaidHP = RAID_START_HP;
static float g_BufHP;
static float g_startHP;
static int g_breakNum = 0;

static int g_textureID_break;
static float g_scale_break;
static bool g_bUse_Break;

void Raid_Init()
{
	g_MicFream = RAID_SEC * 60;
	g_EndFream = g_MicFream + 120;	//�}�C�N�ɋ��Ԏ��Ԃ��I����Ă���120�t���[����ɃV�[���`�F���W
	g_bMic = false;

	g_startHP = g_RaidHP;
	g_BufHP = 0;

	g_textureID_Gage = Texture_SetLoadFile("Asset/Texture/gage.png", 640, 32);

	g_textureID_break = Texture_SetLoadFile("Asset/Texture/kiretu.png", 3509, 2481);
	g_scale_break = 0.0f;
	g_bUse_Break = false;
}

void Raid_UnInit()
{
	Result_GetScore(g_startHP - g_RaidHP);
}

void Raid_Update()
{
	if (Wall_GetPosition().z - 1.0f < Hammer_GetPosition().z && Wall_isUse()) {	//��Q�ɓ���������
		D3DXVECTOR3 w(Wall_GetPosition().x, Hammer_GetPosition().y, Wall_GetPosition().z-0.5f);
		Hammer_SetPosition(w);
		
		g_bMic = true;
		g_bUse_Break = true;
		if (g_bMic) {
			if (Mic_GetVolume() > 80) {
				g_scale_break += 0.1f;
			}
			g_RaidHP -= (Mic_GetVolume() * Zako_GetBreakCount()) / 100;
		}
	}

	if (g_RaidHP <= 0) {
		g_breakNum++;

		g_RaidHP = RAID_START_HP + g_breakNum * RAID_ADD_HP;
		g_startHP += RAID_START_HP + g_breakNum * RAID_ADD_HP;

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

void Raid_Draw()
{
	Sprite_SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
	Sprite_Draw(g_textureID_Gage, SCREEN_WIDTH / 2, 16.0f, g_RaidHP / (RAID_START_HP + g_breakNum * RAID_ADD_HP), 1.0f, 0.0f, 16.0f);
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));

	if (g_bUse_Break) {
		D3DXMATRIX mtxW, mtxT,mtxS;
		D3DXMatrixTranslation(&mtxT, Hammer_GetPosition().x, Hammer_GetPosition().y+1.0f, Hammer_GetPosition().z);
		D3DXMatrixScaling(&mtxS, g_scale_break , g_scale_break, 1.0f);
		mtxW = mtxS * mtxT;
		Cube_Draw(&mtxW, g_textureID_break);
	}

	DebugFont_Draw(1, 24, "�X�^�[�g:%f", g_startHP);
	DebugFont_Draw(1, 24*2, "%f", g_BufHP);
	DebugFont_Draw(1, 24*3, "����:%f", g_RaidHP);

	Score_Draw(g_MicFream / 60, 100, 100, 4, 0, 0);
}