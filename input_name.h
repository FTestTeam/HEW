#pragma once
#ifndef _INPUT_NAME_H_
#define _INPUT_NAME_H_

void iName_Init(void);
void iName_Uninit(void);
void iName_Update(void);
void iName_Draw(void);

void alphabet_Draw(int n, float x, float y);
void SetRankName(int no);
void NameSort(void);
void NameLink(int i);
#endif //_INPUT_NAME_H_