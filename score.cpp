#include "common.h"
#include "score.h"
#include "Result.h"

int g_Score_TextureID;
int g_Score;

void Score_Init()
{
	g_Score_TextureID = Texture_SetLoadFile("Texture/number480.tga", 480,48 );
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

	Sprite_Draw(g_Score_TextureID, x, y,48*n,48,48,48);
}

void Score_Draw(int score, float x, float y, int digit, bool bZero, bool bLeft)
{
	for (int i = 0; i < digit; i++)
	{
		int n = score % 10;
		number_Draw(n, x - (i * 48) , y);
		score /= 10;
		if ((bZero == false)&&(score / 1 == 0))
		{
			break;
		}
	}
}

int GetScore(void)
{
	return g_Score;
}

void AddScore(void)
{
	g_Score += 100;
	Result_GetScore(g_Score);
}

// 	Score_Draw(GetScore() , 1232, 0, 7, false, true); To Scene