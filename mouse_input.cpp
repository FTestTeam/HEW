#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include"mouse_input.h"
#include<XInput.h>

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
static bool initialize(HINSTANCE hInstance);
static void finalize(void);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECTINPUT8			g_pInput = NULL;					// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
static LPDIRECTINPUTDEVICE8		g_pDevMouse = NULL;					// ���̓f�o�C�X�ւ̃|�C���^

static DIMOUSESTATE				g_MouseState;
static DIMOUSESTATE				g_MouseTrrigerState;
static DIMOUSESTATE				g_MouseReleaseState;

//=============================================================================
// ���͏����̏�����
//=============================================================================
bool initialize(HINSTANCE hInstance)
{
	if (g_pInput == NULL) {

		// DirectInput�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL))) {

			return false;
		}
	}

	return true;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void finalize(void)
{
	if (g_pInput != NULL) {

		// DirectInput�I�u�W�F�N�g�̊J��
		g_pInput->Release();
		g_pInput = NULL;
	}
}


//=============================================================================
// �}�E�X�̏�����
//=============================================================================
bool Mouse_Initialize(HINSTANCE hInstance, HWND hWnd)
{
	// ���͏����̏�����
	if (!initialize(hInstance)) {

		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �f�o�C�X�̍쐬
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		MessageBox(hWnd, "�}�E�X���˂��I", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		MessageBox(hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))))
	{
		MessageBox(hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return false;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;		//���Βl���[�h�H

	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph))) {
		MessageBox(hWnd, "�f�o�C�X�̐ݒ�Ɏ��s�B", "�x���I", MB_ICONWARNING);

		return false;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevMouse->Acquire();

	return true;
}


//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void Mouse_Finalize(void)
{
	if (g_pDevMouse != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		g_pDevMouse->Unacquire();

		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	// ���͏����̏I������
	finalize();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void Mouse_Update(void)
{
	DIMOUSESTATE MouseState;
	
	g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState);

	for (int iKey = 0; iKey < DIM_MAX; iKey++) {
		g_MouseTrrigerState.rgbButtons[iKey] = (g_MouseState.rgbButtons[iKey] ^ MouseState.rgbButtons[iKey]) & MouseState.rgbButtons[iKey];
		g_MouseReleaseState.rgbButtons[iKey] = (g_MouseState.rgbButtons[iKey] ^ MouseState.rgbButtons[iKey]) & g_MouseState.rgbButtons[iKey];

		g_MouseState = MouseState;
	}

	g_pDevMouse->Acquire();
}

bool Mouse_IsPress(MOUSE_KEY key)
{
	return (g_MouseState.rgbButtons[key]& 0x80)? true : false;	//�����炭�i0x80�j�������ꂽ���
}

bool Mouse_IsTrigger(MOUSE_KEY key)
{
	return (g_MouseTrrigerState.rgbButtons[key] & 0x80) ? true : false;	//�����炭�i0x80�j�������ꂽ���
}

bool Mouse_IsRelease(MOUSE_KEY key)
{
	return (g_MouseReleaseState.rgbButtons[key] & 0x80) ? true : false;	//�����炭�i0x80�j�������ꂽ���
}
