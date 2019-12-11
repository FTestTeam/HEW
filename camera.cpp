#include<d3d9.h>
#include<d3dx9.h>
#include"mydirect3d.h"
#include"input.h"
#include"common.h"
#include"camera.h"
#include"player.h"
#include"hammer.h"

enum Dir_enum{
	front,
	right,
	left,
	back,
	up,
	down,
};
static void camera_translation(Dir_enum dir);
static void camera_rotation(Dir_enum dir);
static void camera_donnakimoti(Dir_enum dir);

static Camera g_camera;
static D3DXVECTOR3 g_VecDir(0.0f, 0.0f, 0.0f);

static bool DebugCam;

void Camera_Init()
{
	
	g_camera.LocalVec.Front = D3DXVECTOR3(0.0f, -0.3f, 1.0f);
	g_camera.LocalVec.Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXVec3Cross(&g_camera.LocalVec.Up, &g_camera.LocalVec.Front, &g_camera.LocalVec.Right);	//D3DXVec3Cross�O�ς����߂�֐��@��̃x�N�g���ɒ��p�ȃx�N�g�������

	D3DXVec3Normalize(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front);
	D3DXVec3Normalize(&g_camera.LocalVec.Right, &g_camera.LocalVec.Right);
	D3DXVec3Normalize(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up);
	
	g_camera.Pos = D3DXVECTOR3(Hammer_GetPosition().x, Hammer_GetPosition().y+2.0f, Hammer_GetPosition().z-2.0f);
	g_camera.Fov = D3DXToRadian(60);
	g_camera.MoveSpeed = 0.3f;
	g_camera.RotationSpeed = 0.05f;

	DebugCam = false;
}

void Camera_Update()
{
	if (!DebugCam && Player_IsFly()) {
		g_camera.Pos.y = Hammer_GetPosition().y + 3.0f;
		g_camera.Pos.z = Hammer_GetPosition().z - 3.0f;
	}


	if (Keyboard_IsTrigger(DIK_0)) {
		DebugCam = true;
	}
	if (DebugCam) {
		g_VecDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		if (Keyboard_IsPress(DIK_LSHIFT)) {
			if (Keyboard_IsPress(DIK_W)) {
				camera_rotation(up);
			}
			if (Keyboard_IsPress(DIK_S)) {
				camera_rotation(down);
			}

			if (Keyboard_IsPress(DIK_D)) {
				camera_rotation(right);
			}
			if (Keyboard_IsPress(DIK_A)) {
				camera_rotation(left);
			}
		}
		else {
			if (Keyboard_IsPress(DIK_W)) {
				camera_translation(front);
			}
			if (Keyboard_IsPress(DIK_S)) {
				camera_translation(back);
			}

			if (Keyboard_IsPress(DIK_D)) {
				camera_translation(right);
			}
			if (Keyboard_IsPress(DIK_A)) {
				camera_translation(left);
			}
		}

		if (Keyboard_IsPress(DIK_E)) {
			camera_translation(up);
		}
		if (Keyboard_IsPress(DIK_Q)) {
			camera_translation(down);
		}

		if (Keyboard_IsPress(DIK_Z)) {
			camera_donnakimoti(left);
		}
		if (Keyboard_IsPress(DIK_C)) {
			camera_donnakimoti(right);
		}

		D3DXVec3Normalize(&g_VecDir, &g_VecDir);
		g_camera.Pos += g_VecDir * g_camera.MoveSpeed;
	}
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	//=================================================
	//2�D�r���[�ϊ��s��
	//=================================================
	D3DXMATRIX mtxView;
	D3DXVECTOR3 eye(g_camera.Pos.x, g_camera.Pos.y, g_camera.Pos.z);	//�J�����̍��W
	D3DXVECTOR3 at(g_camera.Pos.x+g_camera.LocalVec.Front.x*AT_L ,g_camera.Pos.y + g_camera.LocalVec.Front.y*AT_L, g_camera.Pos.z + g_camera.LocalVec.Front.z*AT_L);//����ꏊ
	D3DXMatrixLookAtLH(&mtxView, &eye, &at, &g_camera.LocalVec.Up);	//������W�n�H�Ńr���[�s������
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//=================================================
	//3�D�v���W�F�N�V�����ϊ��s��
	//=================================================
	D3DXMATRIX mtxProje;
	D3DXMatrixPerspectiveFovLH(&mtxProje, g_camera.Fov, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.f);
	//����(2).����p�̓��W�A���w�� �㔼������	
	//����(3).�A�X�y�N�g��
	//����(4,5).near(>0)��far
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProje);	
}

Camera Camera_GetPosition(void) 
{
	return g_camera;
}

static void camera_translation(Dir_enum dir)
{
	
	switch (dir) 
	{
	case front:
		g_VecDir.x += g_camera.LocalVec.Front.x;
		g_VecDir.z += g_camera.LocalVec.Front.z;
		break;
	case back:
		g_VecDir.x -= g_camera.LocalVec.Front.x;
		g_VecDir.z -= g_camera.LocalVec.Front.z;
		break;
	case right:
		g_VecDir += g_camera.LocalVec.Right;
		break;
	case left:
		g_VecDir -= g_camera.LocalVec.Right;
		break;
	case up:
		g_VecDir.y += g_camera.LocalVec.Up.y;
		break;
	case down:
		g_VecDir.y -= g_camera.LocalVec.Up.y;
		break;
	default:
		break;
	}
	
}

static void camera_rotation(Dir_enum dir)
{
	D3DXMATRIX mtxR;
	switch (dir)
	{
	case right:
		D3DXMatrixRotationY(&mtxR, g_camera.RotationSpeed);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front, &mtxR);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Right, &g_camera.LocalVec.Right, &mtxR);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up, &mtxR);
		D3DXVec3Normalize(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front);
		D3DXVec3Normalize(&g_camera.LocalVec.Right, &g_camera.LocalVec.Right);
		D3DXVec3Normalize(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up);
		break;
	case left:
		D3DXMatrixRotationY(&mtxR, -g_camera.RotationSpeed);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front, &mtxR);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Right, &g_camera.LocalVec.Right, &mtxR);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up, &mtxR);
		D3DXVec3Normalize(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front);
		D3DXVec3Normalize(&g_camera.LocalVec.Right, &g_camera.LocalVec.Right);
		D3DXVec3Normalize(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up);
		break;
	case up:
		D3DXMatrixRotationAxis(&mtxR, &g_camera.LocalVec.Right, -g_camera.RotationSpeed);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front, &mtxR);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up, &mtxR);
		D3DXVec3Normalize(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front);
		D3DXVec3Normalize(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up);
		break;
	case down:
		D3DXMatrixRotationAxis(&mtxR, &g_camera.LocalVec.Right, g_camera.RotationSpeed);	//D3DXMatrixRotationAxis() �C�ӎ���]	��]���鎲�����߂���
		D3DXVec3TransformNormal(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front, &mtxR);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up, &mtxR);
		D3DXVec3Normalize(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front);
		D3DXVec3Normalize(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up);
		break;
	default:
		break;
	}
}

static void camera_donnakimoti(Dir_enum dir)
{
	D3DXMATRIX mtxR;
	D3DXVECTOR3 Rat(g_camera.Pos.x + g_camera.LocalVec.Front.x*AT_L, g_camera.Pos.y + g_camera.LocalVec.Front.y*AT_L, g_camera.Pos.z + g_camera.LocalVec.Front.z*AT_L);
	switch (dir)
	{
	case right:
		D3DXMatrixRotationY(&mtxR, -g_camera.RotationSpeed);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front, &mtxR);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Right, &g_camera.LocalVec.Right, &mtxR);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up, &mtxR);
		D3DXVec3Normalize(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front);
		D3DXVec3Normalize(&g_camera.LocalVec.Right, &g_camera.LocalVec.Right);
		D3DXVec3Normalize(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up);
		g_camera.Pos.x = Rat.x - g_camera.LocalVec.Front.x*AT_L;
		g_camera.Pos.y = Rat.y - g_camera.LocalVec.Front.y*AT_L;
		g_camera.Pos.z = Rat.z - g_camera.LocalVec.Front.z*AT_L;
		break;
	case left:
		D3DXMatrixRotationY(&mtxR, g_camera.RotationSpeed);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front, &mtxR);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Right, &g_camera.LocalVec.Right, &mtxR);
		D3DXVec3TransformNormal(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up, &mtxR);
		D3DXVec3Normalize(&g_camera.LocalVec.Front, &g_camera.LocalVec.Front);
		D3DXVec3Normalize(&g_camera.LocalVec.Right, &g_camera.LocalVec.Right);
		D3DXVec3Normalize(&g_camera.LocalVec.Up, &g_camera.LocalVec.Up);
		g_camera.Pos.x = Rat.x - g_camera.LocalVec.Front.x*AT_L;
		g_camera.Pos.y = Rat.y - g_camera.LocalVec.Front.y*AT_L;
		g_camera.Pos.z = Rat.z - g_camera.LocalVec.Front.z*AT_L;
		break;
	default:
		break;
	}
}