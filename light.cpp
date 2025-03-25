#include "light.h"

//�O���[�o���ϐ��錾
D3DLIGHT9 g_light[8];	//���C�g���

//*****************************************
//���C�g�̏�����
//*****************************************
void InitLight(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���C�g�̕����x�N�g��
	D3DXVECTOR3 vecDir[8];

	for (int nCntLight = 0;nCntLight < 3;nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���C�g�̕�����ݒ�
		vecDir[0] = D3DXVECTOR3(0.2f , -0.8f, -0.4f);
		vecDir[1] = D3DXVECTOR3(-12.0f , -14.0f, 15.0f);
		vecDir[2] = D3DXVECTOR3(-5.0f , -5.57f, -3.3f);

		// ���K������(�傫���P�̃x�N�g���ɂ���)
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		g_light[nCntLight].Direction = vecDir[nCntLight];

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}

	// ���C�g���N���A����
	ZeroMemory(&g_light[3], sizeof(D3DLIGHT9));

	//���
	g_light[3].Type = D3DLIGHT_POINT;
	//�g�U��
	g_light[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
	//����
	g_light[3].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
	//���ʔ��ˌ�
	g_light[3].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
	//�ʒu
	g_light[3].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�͈�
	g_light[3].Range = 0.0f;
	//����������(���)
	g_light[3].Attenuation0 = 0.1f;
	//����������(����)
	g_light[3].Attenuation1 = 0.0f;
	//����������(����*2)
	g_light[3].Attenuation2 = 0.0f;
	//���C�g�Z�b�g
	pDevice->SetLight(3, &g_light[3]);
	//�L����
	pDevice->LightEnable(3, FALSE);

	for (int nCnt = 4; nCnt < 8; nCnt++)
	{
		//���
		g_light[nCnt].Type = D3DLIGHT_SPOT;
		//�g�U��
		g_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//����
		g_light[nCnt].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//���ʔ��ˌ�
		g_light[nCnt].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�ʒu
		g_light[nCnt].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//����
		vecDir[nCnt] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		//���K��
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		g_light[nCnt].Direction = vecDir[nCnt];
		//�͈�
		g_light[nCnt].Range = 0.0f;
		//�R�[��������
		g_light[nCnt].Falloff = 0.01f;
		//����������
		g_light[nCnt].Attenuation0 = 0.1f;
		//�R�[���p�x(��)
		g_light[nCnt].Theta = D3DXToRadian(90.0f);
		//�R�[���p�x(�O)
		g_light[nCnt].Phi = D3DXToRadian(360.0f);
		//���C�g�Z�b�g
		pDevice->SetLight(nCnt, &g_light[nCnt]);
		//�L����
		pDevice->LightEnable(nCnt, FALSE);
	}
}

//*****************************************
//���C�g�̏I��
//*****************************************
void UninitLight(void)
{
	

}

//*****************************************
//���C�g�̍X�V
//*****************************************
void UpdateLight(void)
{

}

D3DLIGHT9* GetLight(void)
{
	return &g_light[0];
}

//--------------------------
//�Z�b�g
//--------------------------
void SetLight(int nIdx, float Range, D3DXCOLOR col, D3DXVECTOR3 pos)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ����
	g_light[nIdx].Range = Range;
	//�g�U��
	g_light[nIdx].Diffuse = col;
	//����
	g_light[nIdx].Ambient = col;
	//���ʔ��ˌ�
	g_light[nIdx].Specular = col;
	//�ʒu
	g_light[nIdx].Position = pos;

	//���C�g�Z�b�g
	pDevice->SetLight(nIdx, &g_light[nIdx]);
	//�L����
	pDevice->LightEnable(nIdx, TRUE);
}

//--------------------------
//�j��
//--------------------------
void EndLight(int nIdx)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�L����
	pDevice->LightEnable(nIdx, FALSE);
}