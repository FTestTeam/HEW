#ifndef _SCORE_H_
#define _SCORE_H_
void Score_Init();
void Score_Uninit();
static void number_Draw(int n,float x,float y);
/*bZero�c0���� bLeft�c����*/
void Score_Draw(int score,float x,float y,int digit,bool bZero,bool bLeft);
int Score_GetScore(void);
void Score_AddScore(int n);
#endif // !_SCORE_H_