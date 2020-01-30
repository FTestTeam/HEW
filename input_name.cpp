#include "common.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "input.h"
#include "Result.h"

#define NAME_MAX (5)     //�ő啶����
#define NAME_WIDTH (3456) //�摜�̉���
#define NAME_HIGH (128)  //�摜�̍���
#define NAME_YOKOLINE (27)  //����ɕ������Ă��邩
#define NAME_TATELINE (1)  //���s�ɕ������Ă��邩
#define NAME_START_POS_X (336)
#define SCALE (0.5f)      //�W�����P

static int g_iName_TextureID;
static int nAlphabet[NAME_MAX];  //�A���t�@�x�b�g�������ڂ�
static int Select;               //���O�̉������ڑI�𒆂�
static char name1[NAME_MAX];     //���O�ۑ��p
static char name2[NAME_MAX];
static char name3[NAME_MAX];

void iName_Init(void)
{
	g_iName_TextureID = Texture_SetLoadFile("Asset/Font/alphabet2.png", NAME_WIDTH, NAME_HIGH);
	Select = 0;
	for (int i = 0; i < NAME_MAX; i++)
	{
		nAlphabet[i] = 0;
	}
	for (int i = 0; i < NAME_MAX; i++)
	{
		////�󔒂ŏ�����
		//name1[i] = 26;
		//name2[i] = 26;
		//name3[i] = 26;
	}
}

void iName_Uninit(void)
{

}

void iName_Update(void)
{
	//���O�������ڂ��I��
	if (Keyboard_IsTrigger(DIK_RIGHTARROW))
	{
		Select += 1;
		if (Select >= NAME_MAX)
		{//���O���͏I��
			for (int i = 0; i < NAME_MAX; i++)
			{
				name1[i] = nAlphabet[i];
			}
			Scene_SetNextScene(SCENE_TITLE);
		}
	}
	if (Keyboard_IsTrigger(DIK_LEFTARROW))
	{
		Select -= 1;
		if (Select < 0)
		{//�I�����̓}�C�i�X����
			Select = 0;
		}
	}
	//�A���t�@�x�b�g�I��
	if (Keyboard_IsTrigger(DIK_DOWNARROW))
	{
		nAlphabet[Select] += 1;
		if (nAlphabet[Select] > 26)
		{
			nAlphabet[Select] = 0;
		}
	}
	if (Keyboard_IsTrigger(DIK_UPARROW))
	{
		nAlphabet[Select] -= 1;
		if (nAlphabet[Select] < 0)
		{
			nAlphabet[Select] = 26;
		}
	}
}

void alphabet_Draw(int n, float x, float y)
{
	if (n < 0)
	{
		MessageBox(NULL, "���l�Ɉُ킪����������", "�G���[�p�^�[��:n < 0", MB_OK);
	}
	if (n > 26)
	{
		MessageBox(NULL, "���l�Ɉُ킪����������", "�G���[�p�^�[��:n > 26", MB_OK);
	}

	//�摜�`��
	Sprite_Draw(g_iName_TextureID, x, y,
		(NAME_WIDTH / NAME_YOKOLINE) * (n % NAME_YOKOLINE), (NAME_HIGH / NAME_TATELINE) * (n / NAME_YOKOLINE),
		(NAME_WIDTH / NAME_YOKOLINE), (NAME_HIGH / NAME_TATELINE),
		SCALE, SCALE,
		0, 0);
}

void iName_Draw(void)
{
	for (int i = 0; i < NAME_MAX; i++)
	{
		i == Select ? Sprite_SetColor(D3DCOLOR_RGBA(255, 0, 0, 255)) : Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
		alphabet_Draw(nAlphabet[i], NAME_START_POS_X + (i * ((NAME_WIDTH * SCALE) / NAME_YOKOLINE)), SCORE_POS_NOW);
	}
	//�ۑ��������O�\��
	for (int i = 0; i < NAME_MAX; i++)
	{
		Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
		alphabet_Draw(name1[i], NAME_START_POS_X + (i * ((NAME_WIDTH * SCALE) / NAME_YOKOLINE)), SCORE_POS_1);
	}
	for (int i = 0; i < NAME_MAX; i++)
	{
		Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
		alphabet_Draw(name2[i], NAME_START_POS_X + (i * ((NAME_WIDTH * SCALE) / NAME_YOKOLINE)), SCORE_POS_2);
	}
	for (int i = 0; i < NAME_MAX; i++)
	{
		Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
		alphabet_Draw(name3[i], NAME_START_POS_X + (i * ((NAME_WIDTH * SCALE) / NAME_YOKOLINE)), SCORE_POS_3);
	}
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}