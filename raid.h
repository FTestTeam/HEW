#pragma once
#ifndef RAID_H_
#define RAID_H_

//================================
//	レイドのコントロールプログラム
//================================

void Raid_Init();
void Raid_UnInit();
void Raid_Update();
void Raid_Draw();

bool Raid_IsBreak();

#endif // !RAID_H_