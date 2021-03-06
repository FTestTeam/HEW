#include<d3d9.h>
#include<d3dx9.h>
#include"common.h"
#include"model.h"
#include"hammer.h"
#include"joycon.h"
#include"cube.h"
#include"input.h"
#include"DebugPrintf.h"
#include"mydirect3d.h"
#include"Scene.h"
#include"collect_data.h"
#include"sound.h"
#include"debug_font.h"

typedef struct PLAYER_Tag{
	LocalVecter LocalVec;
	D3DXVECTOR3 Position;
	int ModelId;
}PLAYER;

static PLAYER g_Player;
static float g_Rspeed;
static float g_Ratetion;
static int g_fream;
static bool g_Fly;
static float g_Force;
static bool g_bSound;

void Player_Init() 
{
	g_Player.Position = {0.0f,0.0f,0.0f};
	g_Player.LocalVec.Front = { 0.0f, 0.0f, -1.0f };
	g_Player.ModelId = Model_SetLoadFile("Asset/Model/player.x");

	g_Fly = false;
	g_Rspeed = 0.0f;
	g_Force = 0;
	g_bSound = false;

	//ハンマーのポジションをプレイヤーの前に初期化
	D3DXVECTOR3 w;
	w = g_Player.Position + g_Player.LocalVec.Front * 1.5f;
	Hammer_SetPosition(w);
}

void Player_UnInit()
{

}

void Player_Update()
{
	if (Scene_GetScene() == SCENE_REPLAY_ZAKO || Scene_GetScene() == SCENE_RESULT || Scene_GetScene() == SCENE_REPLAY_RAID) {
		if (Collect_Data_GetData().bJoy_R_Press) {
			if (Collect_Data_GetData().accel > -30000 || Collect_Data_GetData().accel < 30000) {
				g_Rspeed = fabsf(Collect_Data_GetData().accel / 100000);
				//g_Rspeed = min(g_Rspeed, 1.0f);
			}
			else {	//	ジョイコン振ってない間回転減少
				g_Rspeed -= 0.005f;
				g_Rspeed = max(g_Rspeed, 0.0f);
			}
			g_Ratetion -= g_Rspeed;
			g_fream++;
		}
		if (Collect_Data_GetData().bJoy_R_Release) {	//ボタン離したら投げる
			g_Fly = true;
		}
	}
	else {
		if (Keyboard_IsPress(DIK_SPACE) || Joycon_IsPress(DIJOY_R_SR)) {
			if (Joycon_GetAccel(DIJOY_ACCEL_SL1) > -30000 || Joycon_GetAccel(DIJOY_ACCEL_SL1) < 30000 || Keyboard_IsPress(DIK_SPACE)) {
				if (Joycon_IsUsed()) {
					g_Rspeed = fabsf(Joycon_GetAccel(DIJOY_ACCEL_SL1) / 50000);
					g_Force += g_Rspeed;
					if (!g_bSound) {
						PlaySound(SOUND_LABEL_BGM_KAZE);
						g_bSound = true;
					}
				}
				else {
					g_Rspeed += 0.01f;
				}
			}
			else {	//	ジョイコン振ってない間回転減少
				g_Rspeed -= 0.005f;
				g_Rspeed = max(g_Rspeed, 0.0f);
			}
			g_Ratetion -= g_Rspeed;
			g_fream++;
		}

		if(g_bSound) DebugFont_SetParam(5, "SoundOn");

		if (!g_bSound) {
			StopSound(SOUND_LABEL_BGM_KAZE);
		}

		if (Keyboard_IsRelease(DIK_SPACE) || Joycon_IsRelease(DIJOY_R_SR)) {	//ボタン離したら投げる
			g_Fly = true;
			g_bSound = false;
		}


	}
	//DebugPrintf("%f\n", Joycon_GetAccel(DIJOY_ACCEL_SL1));
}

void Player_Draw()
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	D3DXMATRIX mtxW,mtxR,mtxRR,mtxS,mtxT;
	D3DXMatrixRotationY(&mtxR, g_Ratetion);
	D3DXMatrixRotationX(&mtxRR, D3DXToRadian(-90));
	D3DXMatrixScaling(&mtxS, 0.01f, 0.01f, 0.01f);
	mtxW = mtxS*mtxRR*mtxR;
	Model_Draw(&mtxW, g_Player.ModelId);
}

D3DXVECTOR3 Player_GetFront(void)
{
	return g_Player.LocalVec.Front;
}

float Player_GetRotation(void)
{
	return g_Ratetion;
}

D3DXVECTOR3 Player_GetPosition()
{
	return g_Player.Position;
}

bool Player_IsFly(void)
{
	return g_Fly;
}

float Player_GetForce()
{
	return g_Force;
}