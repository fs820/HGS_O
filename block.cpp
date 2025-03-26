//---------------------------------------
//
//�{�[������[block.cpp]
//Author fuma sato
//
//---------------------------------------
#include"block.h"
#include"mesh.h"
#include"vectorcollision.h"
#include"rotation.h"
#include "score.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;
Block g_Block[BLOCK_MAX];
//-----------------
// ����������
//-----------------
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * BLOCK_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		BLOCK_TEX,
		&g_pTextureBlock
	);

	for (int nCntBlock = 0; nCntBlock < BLOCK_MAX; nCntBlock++)
	{
		g_Block[nCntBlock].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Block[nCntBlock].bUse = false;
	}
	//1��

	SetVertex2D
	(
		&g_pVtxBuffBlock,
		0, BLOCK_MAX,
		1, 1,
		D3DXVECTOR2(0.0f, 0.0f), 0.0f,
		BLOCK_WIDTH, BLOCK_HEIGHT,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		BLOCK_WIDTH, BLOCK_HEIGHT
	);
}

//-----------------
// �I������
//-----------------
void UninitBlock(void)
{
	SAFE_RELEASE(g_pTextureBlock);
	SAFE_RELEASE(g_pVtxBuffBlock);
}

//-----------------
// �X�V����
//-----------------
void UpdateBlock(void)
{

}

//-----------------
// �`�揈��
//-----------------
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntBlock = 0; nCntBlock < BLOCK_MAX; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse)
		{
			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock);

			//�|���S���̕`��
			HRESULT hr = pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				nCntBlock * VT_MAX,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}
}

//-----------------
// �ݒ�
//-----------------
int SetBlock(D3DXVECTOR2 pos)
{
	for (int nCntBlock = 0; nCntBlock < BLOCK_MAX; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse == false)
		{
			g_Block[nCntBlock].pos = pos;

			SetVertex2D
			(
				&g_pVtxBuffBlock,
				nCntBlock, 1,
				1, 1,
				pos, 0.0f,
				BLOCK_WIDTH, BLOCK_HEIGHT,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				BLOCK_WIDTH, BLOCK_HEIGHT
			);

			g_Block[nCntBlock].bUse = true;
			return nCntBlock;
		}
	}
	return -1;
}

//--------------------------------
// ���t���N�V����
//--------------------------------
void ReflectionBlock(D3DXVECTOR2& pos, D3DXVECTOR2& posOld, D3DXVECTOR2& move, float fWidth)
{
	for (int nCntBlock = 0; nCntBlock < BLOCK_MAX; nCntBlock++)
	{
		if (g_Block[nCntBlock].bUse)
		{
			D3DXVECTOR3 RightUp = D3DXVECTOR3(BLOCK_WIDTH * 0.5f, -BLOCK_HEIGHT * 0.5f, 0.0f),
				LeftUp = D3DXVECTOR3(-BLOCK_WIDTH * 0.5f, -BLOCK_HEIGHT * 0.5f, 0.0f),
				LeftDown = D3DXVECTOR3(-BLOCK_WIDTH * 0.5f, BLOCK_HEIGHT * 0.5f, 0.0f),
				RightDown = D3DXVECTOR3(BLOCK_WIDTH * 0.5f, BLOCK_HEIGHT * 0.5f, 0.0f);

			D3DXVECTOR2 RightUp2 = (D3DXVECTOR2)RightUp,
				LeftUp2 = (D3DXVECTOR2)LeftUp,
				LeftDown2 = (D3DXVECTOR2)LeftDown,
				RightDown2 = (D3DXVECTOR2)RightDown;

			RightUp2 += g_Block[nCntBlock].pos;
			LeftUp2 += g_Block[nCntBlock].pos;
			LeftDown2 += g_Block[nCntBlock].pos;
			RightDown2 += g_Block[nCntBlock].pos;

			for (int nCnt10 = 0; nCnt10 < 10; nCnt10++)
			{
				if (VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, RightUp2, LeftUp2))
				{
					g_Block[nCntBlock].bUse = false;
					AddScore(10);
				}
				if (VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, LeftUp2, LeftDown2))
				{
					g_Block[nCntBlock].bUse = false;
					AddScore(10);
				}
				if (VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, LeftDown2, RightDown2))
				{
					g_Block[nCntBlock].bUse = false;
					AddScore(10);
				}
				if (VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, RightDown2, RightUp2))
				{
					g_Block[nCntBlock].bUse = false;
					AddScore(10);
				}
			}
		}
	}
}