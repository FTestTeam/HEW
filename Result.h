#ifndef _RESULT_H_
#define _RESULT_H_

#define	SCORE_POS_NOW (255)
#define SCORE_POS_1 (335)
#define SCORE_POS_2 (415)
#define SCORE_POS_3 (490)

void Result_Init(void);
void Result_Uninit(void);
void Result_Update(void);
void Result_Draw(void);
void Result_GetScore(int x);
void Result_Sort(void);
#endif // !_RESULT_H_
