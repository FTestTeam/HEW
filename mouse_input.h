#pragma once
#ifndef MOUSE_INPUT_H_
#define MOUSE_INPUT_H_


#include <Windows.h>
// dinput.h���C���N���[�h����O�ɂ�������Ȃ��ƌx�����o��̂Œ���
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

enum MOUSE_KEY {
	DIM_LEFT,
	DIM_RIGHT,
	DIM_WHEEL,
	DIM_MAX,
};

/*------------------------------------------------------------------------------
   �֐��̃v���g�^�C�v�錾
------------------------------------------------------------------------------*/

// �}�E�X���̓��W���[���̏�����
//
// �߂�l�F�������o���Ȃ������ꍇfalse
//
// �����Fhinstance ... �C���X�^���X�n���h���iWinMain�̈����ȂǂŎ擾�j
//       hWnd      ... �E�B���h�E�n���h��
//
bool Mouse_Initialize(HINSTANCE hInstance, HWND hWnd);

// �}�E�X���W���[���̏I������
void Mouse_Finalize(void);

// �}�E�X���W���[���̍X�V
// ���}�E�X�S�̂̃L�[��Ԃ̎擾
//
void Mouse_Update(void);

// �}�E�X�̃L�[��Ԃ̎擾
//
// Mouse_Update()�Ŏ擾�����L�[�̏�Ԃ��m�F����֐��Q
//
// �߂�l�F�w��̃L�[��
//     Press   ... ������Ă���
//     Trigger ... �������u��
//     Release ... �������u��
// �ł������ꍇtrue��Ԃ�
//
// �����FKey ... �L�[�w��iDIM_�`�Ƃ����L�[�񋓁j
//

bool Mouse_IsPress(MOUSE_KEY key);
bool Mouse_IsTrigger(MOUSE_KEY key);
bool Mouse_IsRelease(MOUSE_KEY key);

#endif // !MOUSE_INPUT
