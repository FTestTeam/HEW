#include "common.h"
#include "score.h"
#include "Result.h"
#include "sprite.h"
#include "texture.h"

int g_Score_TextureID;
int g_Score;

void Score_Init()
{
	g_Score_TextureID = Texture_SetLoadFile("Asset/Font/number2.png", 1280,128 );
	g_Score = 0;
}

void Score_Uninit()
{

}

static void number_Draw(int n, float x, float y)
{
	if (n < 0)
	{
		MessageBox(NULL, "数値に異常が発生したよ(´･ω･`)", "エラーパターン:n < 0", MB_OK);
	}
	if (n > 9)
	{
		MessageBox(NULL, "数値に異常が発生したよ(´･ω･`)", "エラーパターン:n > 9", MB_OK);
	}
	Sprite_SetColor(D3DCOLOR_RGBA(0, 0, 0, 255));
	Sprite_Draw(g_Score_TextureID, x, y,128*n,0, 128, 128,0.5f,0.5f,0,0);
}

void Score_Draw(int score, float x, float y, int digit, bool bZero, bool bLeft)
{
	for (int i = 0; i < digit; i++)
	{
		int n = score % 10;
		number_Draw(n, x - (i * 32) , y);
		score /= 10;
		if ((bZero == false)&&(score / 1 == 0))
		{
			break;
		}
	}
}

int Score_GetScore(void)
{
	return g_Score;
}

void Score_AddScore(int n)
{
	g_Score += n;
	Result_GetScore(g_Score);
}

// 	Score_Draw(GetScore() , 1232, 0, 7, false, true); To Scene