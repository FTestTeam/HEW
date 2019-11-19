#pragma once
#ifndef SPRITE_H
#define SPRITE_H

enum ZERO_POSITION {
	CENTER,
	BOTTOM,
};

//�\��
//(���W.x,���W.y,ID)
void Sprite_Draw(int textureId,float dx, float dy);

//��]
//(���W.x,���W.y,ID,��]�̒��S.x,��]�̒��S.y,��]�̒��S�p)
void Sprite_Draw(int textureId,float dx, float dy, float center_x, float center_y, float angle);

//�g��
//(���W.x,���W.y,ID,�g�傷��{��.x,�g�傷��{��.y,���S.x,���S.y)
void Sprite_Draw(int textureId,float dx, float dy, float scale_x, float scale_y,float center_x, float center_y);

//�g��E��]
//(���W.x,���W.y,ID,�g�傷��{��.x,�g�傷��{��.y,���S.x,���S.y,��]�̒��S�p)
void Sprite_Draw(int textureId,float dx, float dy, float scale_x, float scale_y, float center_x, float center_y, float angle);

//�g��E��]�E���]
//(���W.x,���W.y,ID,�g�傷��{��.x,�g�傷��{��.y,���S.x,���S.y,��]�̒��S�p)
void Sprite_Mirror_Draw(int textureId,float dx, float dy, float scale_x, float scale_y, float center_x, float center_y, float angle);


//�J�b�g
//(���W.x,���W.y,ID,�J�b�g����e�N�X�`�����W.x,�J�b�g����e�N�X�`�����W.y,�J�b�g����e�N�X�`���̕�,�J�b�g����e�N�X�`���̍���)
void Sprite_Draw(int textureId,float dx, float dy,int cut_x,int cut_y,int cut_w,int cut_h);

//�J�b�g�E��]
//(���W.x,���W.y,ID,�J�b�g����e�N�X�`�����W.x,�J�b�g����e�N�X�`�����W.y,�J�b�g����e�N�X�`���̕�,�J�b�g����e�N�X�`���̍���,��]�̒��S.x,��]�̒��S.y,��]�̒��S�p)
void Sprite_Draw(int textureId,float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h,float center_x,float center_y, float angle);

//�J�b�g�E�g��
//(���W.x,���W.y,ID,�J�b�g����e�N�X�`�����W.x,�J�b�g����e�N�X�`�����W.y,�J�b�g����e�N�X�`���̕�,�J�b�g����e�N�X�`���̍���,�g�傷��{��.x,�g�傷��{��.y)
void Sprite_Draw(int textureId,float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float scale_x, float scale_y, float center_x, float center_y);

//�J�b�g�E�g��E��]
//(���W.x,���W.y,ID,�J�b�g����e�N�X�`�����W.x,�J�b�g����e�N�X�`�����W.y,�J�b�g����e�N�X�`���̕�,�J�b�g����e�N�X�`���̍���,�g�傷��{��.x,�g�傷��{��.y,���S.x,���S.y,��]�̒��S�p)
void Sprite_Draw(int textureId,float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float scale_x, float scale_y, float center_x, float center_y,float angle);

//�J�b�g�E�g��E��]�E���]
//(���W.x,���W.y,ID,�J�b�g����e�N�X�`�����W.x,�J�b�g����e�N�X�`�����W.y,�J�b�g����e�N�X�`���̕�,�J�b�g����e�N�X�`���̍���,�g�傷��{��.x,�g�傷��{��.y,���S.x,���S.y,��]�̒��S�p)
void Sprite_Mirror_Draw(int textureId,float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float scale_x, float scale_y, float center_x, float center_y, float angle);

//�F�Z�b�g
void Sprite_SetColor(D3DCOLOR Color);

#endif // !SPRITE_H