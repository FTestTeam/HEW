#include "common.h"
#include "texture.h"
#include "sprite.h"
#include "Scene.h"
#include "input.h"

#define NAME_MAX (5)     //最大文字数
#define NAME_WIDTH (660) //画像の横幅
#define NAME_HIGH (467)  //画像の高さ
#define SCALE (0.6f)

static int g_iName_TextureID;
static int nAlphabet[NAME_MAX];  //アルファベット何文字目か
static int Select;               //名前の何文字目選択中か
static char name1[NAME_MAX];     //名前保存用
static char name2[NAME_MAX];
static char name3[NAME_MAX];

void iName_Init(void)
{
	g_iName_TextureID = Texture_SetLoadFile("Asset/Texture/Name.jpg", NAME_WIDTH, NAME_HIGH);
	Select = 0;
	for (int i = 0; i < NAME_MAX; i++)
	{
		nAlphabet[i] = 0;
	}
	for (int i = 0; i < NAME_MAX; i++)
	{
		//空白で初期化
		name1[i] = 26;
		name2[i] = 26;
		name3[i] = 26;
	}
}

void iName_Uninit(void)
{

}

void iName_Update(void)
{
	//名前何文字目か選択
	if (Keyboard_IsTrigger(DIK_RIGHTARROW))
	{
		Select += 1;
		if (Select >= NAME_MAX)
		{//名前入力終了
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
		{//選択肢はマイナス無し
			Select = 0;
		}
	}
	//アルファベット選択
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

static void alphabet_Draw(int n, float x, float y)
{
	if (n < 0)
	{
		MessageBox(NULL, "数値に異常が発生したよ", "エラーパターン:n < 0", MB_OK);
	}
	if (n > 26)
	{
		MessageBox(NULL, "数値に異常が発生したよ", "エラーパターン:n > 26", MB_OK);
	}

	//画像660*467 文字 横6縦5
	Sprite_Draw(g_iName_TextureID, x, y, (NAME_WIDTH / 6) * (n % 6), (NAME_HIGH / 5) * (n / 6), (NAME_WIDTH / 6), (NAME_HIGH / 5), SCALE, SCALE, (NAME_WIDTH*0.5f), (NAME_HIGH * 0.5f));
}

void iName_Draw(void)
{
	for (int i = 0; i < NAME_MAX; i++)
	{
		alphabet_Draw(nAlphabet[i], 50 + (i * ((NAME_WIDTH * SCALE) / 6)), 80);
	}
	//保存した名前表示
	for (int i = 0; i < NAME_MAX; i++)
	{
		alphabet_Draw(name1[i], 50 + (i * ((NAME_WIDTH * SCALE) / 6)), 200);
	}
	for (int i = 0; i < NAME_MAX; i++)
	{
		alphabet_Draw(name2[i], 50 + (i * ((NAME_WIDTH * SCALE) / 6)), 260);
	}
	for (int i = 0; i < NAME_MAX; i++)
	{
		alphabet_Draw(name3[i], 50 + (i * ((NAME_WIDTH * SCALE) / 6)), 320);
	}
}