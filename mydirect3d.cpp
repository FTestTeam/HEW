//�C���N���[�h
#include"common.h"
#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>

//�O���[�o���ϐ�
static LPDIRECT3D9 g_pD3D = NULL;
static LPDIRECT3DDEVICE9 g_pDevice = NULL;

bool MyDirect3D_Init(HWND hWnd) {
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {
		MessageBox(NULL, "Direct3DCreate9���擾�ł��܂���", "�G���[", MB_OK);
	}

	D3DPRESENT_PARAMETERS d3dpp = {};
	//�o�b�N�o�b�t�@
	d3dpp.BackBufferWidth = Window_GetWidth();		//�o�b�N�o�b�t�@�̕�
	d3dpp.BackBufferHeight = Window_GetHeight();		//�o�b�N�o�b�t�@�̍���
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//�o�b�N�o�b�t�@�̎��
	d3dpp.BackBufferCount = 1;					//�o�b�N�o�b�t�@�̐�

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�X���b�v�̕��@
	d3dpp.Windowed = true;						//�E�B���h�E���[�h->true,�t���X�N���[��->false
	d3dpp.EnableAutoDepthStencil = true;		//�f�v�X�o�b�t�@�i�[�x���j��L���ɂ��邩�H
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//�f�v�X�o�b�t�@�̎��	D3DFMT_D16->�f�v�X16�r�b�g
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//��ʂ̍X�V�^�C�~���O
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//��ʂ̍X�V�^�C�~���O�@IMMEDIATE->���t���b�V�����[�g�����ŕ`��

	HRESULT hr = g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT, //�g�����j�^�[
		D3DDEVTYPE_HAL,		//
		hWnd,				//�Ώۂ̃E�B���h�E�n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pDevice
	);

	//HRESULT�^�̐��������s����^���U�ŕԂ�
	//FAILED(hr);		//hr�����s�Ȃ�^
	//SUCCEEDED(hr);	//hr�������Ȃ�^
	if (!SUCCEEDED(hr)) {
		MessageBox(NULL, "�f�o�C�X���擾�ł��܂���ł���", "�G���[", MB_OK);
		return false;
	}

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);	//�@���x�N�g������ɐ��K��

	return true;
}

void MyDirect3D_UnInit(void){
	SAFE_RELEASE(g_pDevice);
	g_pD3D->Release();
}

LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void) {
	return g_pDevice;
}