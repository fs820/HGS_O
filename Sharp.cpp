//---------------------------------------
//
//�{�[������[Sharp.cpp]
//Author fuma sato
//
//---------------------------------------
#include"Sharp.h"
#include"mesh.h"
#include"vectorcollision.h"
#include"rotation.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSharp = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSharp = NULL;
Sharp g_Sharp[SHARP_MAX];
//-----------------
// ����������
//-----------------
void InitSharp(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * SHARP_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSharp,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		SHARP_TEX,
		&g_pTextureSharp
	);

	for (int nCntSharp = 0; nCntSharp < SHARP_MAX; nCntSharp++)
	{
		g_Sharp[nCntSharp].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Sharp[nCntSharp].fAngle = 0.0f;
		g_Sharp[nCntSharp].bUse = false;
	}
	//1��

	SetVertex2D
	(
		&g_pVtxBuffSharp,
		0, SHARP_MAX,
		1, 1,
		D3DXVECTOR2(0.0f, 0.0f), 0.0f,
		SHARP_WIDTH, SHARP_HEIGHT,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		SHARP_WIDTH, SHARP_HEIGHT
	);
}

//-----------------
// �I������
//-----------------
void UninitSharp(void)
{
	SAFE_RELEASE(g_pTextureSharp);
	SAFE_RELEASE(g_pVtxBuffSharp);
}

//-----------------
// �X�V����
//-----------------
void UpdateSharp(void)
{

}

//-----------------
// �`�揈��
//-----------------
void DrawSharp(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntSharp = 0; nCntSharp < SHARP_MAX; nCntSharp++)
	{
		if (g_Sharp[nCntSharp].bUse)
		{
			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffSharp, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSharp);

			//�|���S���̕`��
			HRESULT hr = pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				nCntSharp * VT_MAX,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}
}

//-----------------
// �ݒ�
//-----------------
int SetSharp(D3DXVECTOR2 pos, float fAngle)
{
	for (int nCntSharp = 0; nCntSharp < SHARP_MAX; nCntSharp++)
	{
		if (g_Sharp[nCntSharp].bUse == false)
		{
			g_Sharp[nCntSharp].pos = pos;
			g_Sharp[nCntSharp].fAngle = fAngle;

			SetVertex2D
			(
				&g_pVtxBuffSharp,
				nCntSharp, 1,
				1, 1,
				pos, fAngle,
				SHARP_WIDTH, SHARP_HEIGHT,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				SHARP_WIDTH, SHARP_HEIGHT
			);

			g_Sharp[nCntSharp].bUse = true;
			return nCntSharp;
		}
	}
	return -1;
}

//--------------------------------
// ���t���N�V����
//--------------------------------
bool HitSharp(D3DXVECTOR2& pos, D3DXVECTOR2& posOld, D3DXVECTOR2& move, float fWidth)
{
	for (int nCntSharp = 0; nCntSharp < SHARP_MAX; nCntSharp++)
	{
		if (g_Sharp[nCntSharp].bUse)
		{
			D3DXVECTOR3 RightUp = D3DXVECTOR3(SHARP_WIDTH * 0.5f, -SHARP_HEIGHT * 0.5f, 0.0f),
				LeftUp = D3DXVECTOR3(-SHARP_WIDTH * 0.5f, -SHARP_HEIGHT * 0.5f, 0.0f),
				LeftDown = D3DXVECTOR3(-SHARP_WIDTH * 0.5f, SHARP_HEIGHT * 0.5f, 0.0f),
				RightDown = D3DXVECTOR3(SHARP_WIDTH * 0.5f, SHARP_HEIGHT * 0.5f, 0.0f);

			RotationofShaftbyMatrix(RightUp, RightUp, D3DXVECTOR3(0.0f, 0.0f, g_Sharp[nCntSharp].fAngle), TYPE_Z);
			RotationofShaftbyMatrix(LeftUp, LeftUp, D3DXVECTOR3(0.0f, 0.0f, g_Sharp[nCntSharp].fAngle), TYPE_Z);
			RotationofShaftbyMatrix(LeftDown, LeftDown, D3DXVECTOR3(0.0f, 0.0f, g_Sharp[nCntSharp].fAngle), TYPE_Z);
			RotationofShaftbyMatrix(RightDown, RightDown, D3DXVECTOR3(0.0f, 0.0f, g_Sharp[nCntSharp].fAngle), TYPE_Z);

			D3DXVECTOR2 RightUp2 = (D3DXVECTOR2)RightUp,
				LeftUp2 = (D3DXVECTOR2)LeftUp,
				LeftDown2 = (D3DXVECTOR2)LeftDown,
				RightDown2 = (D3DXVECTOR2)RightDown;

			RightUp2 += g_Sharp[nCntSharp].pos;
			LeftUp2 += g_Sharp[nCntSharp].pos;
			LeftDown2 += g_Sharp[nCntSharp].pos;
			RightDown2 += g_Sharp[nCntSharp].pos;

			for (int nCnt10 = 0; nCnt10 < 10; nCnt10++)
			{
				if (VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, RightUp2, LeftUp2))return true;
				if (VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, LeftUp2, LeftDown2))return true;
				if (VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, LeftDown2, RightDown2))return true;
				if (VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, RightDown2, RightUp2))return true;
			}
		}
	}

	return false;
}