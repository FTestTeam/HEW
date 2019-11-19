#include<d3d9.h>
#include<d3dx9.h>
#include"mydirect3d.h"

void Light_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();

	//============================
	//���C�g�̐ݒ�
	//============================
	D3DLIGHT9 light = {};
	light.Type = D3DLIGHT_DIRECTIONAL;	//���C�g�p�̍\����
	D3DXVECTOR3 vecDirLight = { -1.0f ,-1.0f,0.0f };	//�Ƃ炷�����̃x�N�g��
	D3DXVec3Normalize(&vecDirLight, &vecDirLight);//���K��
	light.Direction = vecDirLight;
	light.Diffuse.r = 0.7f;	//���C�g�̃J���[
	light.Diffuse.g = 0.7f;
	light.Diffuse.b = 0.7f;
	light.Diffuse.a = 1.0f;	//���͉��Ɏg�����s���@�Ƃ肠����1,0f
	pDevice->SetLight(0, &light);	//�����P�̓X���b�g�@���C�g�𕡐��g���Ƃ��ɐ����ŕ�����@
	pDevice->LightEnable(0, true);	//�X���b�g�O��true�̈Ӗ�

	//�A���r�G���g���C�g�i�����j
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(0.3f,0.3f,0.3f,1.0f));
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);
}