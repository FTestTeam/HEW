#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

void Player_Init();
void Player_UnInit();
void Player_Update();
void Player_Draw();

//�v���C���[�̐��ʂ̃x�N�g���擾
D3DXVECTOR3 Player_GetFront(void);
//�v���C���[�̉�]�p�x�擾
float Player_GetRotation(void);
//�v���C���[���n���}�[��΂������H
bool Player_IsFly(void);

#endif // !PLAYER_H_