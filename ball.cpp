//----------------------------------------
//
//�{�[������[ball.cpp]
//Author fuma sato
//
//----------------------------------------

#include"ball.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"sound.h"
#include "mesh.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBall = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBall = NULL;
Ball g_aBall[BALL_MAX];

//----------------------
//�|���S���̏���������
//----------------------
void InitBall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBall,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		BALL_TEX,
		&g_pTextureBall
	);

	int nCntBall;
	for (nCntBall = 0; nCntBall < BALL_MAX; nCntBall++)
	{
		g_aBall[nCntBall].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_aBall[nCntBall].posOld = D3DXVECTOR2(0.0f, 0.0f);
		g_aBall[nCntBall].move = D3DXVECTOR2(0.0f, 0.0f);
		g_aBall[nCntBall].dir = D3DXVECTOR2(0.0f, 0.0f);
		g_aBall[nCntBall].nLife = 0;
		g_aBall[nCntBall].bUse = false;
	}
	//1��

	SetVertex2D
	(
		&g_pVtxBuffBall,
		0, 1,
		1, 1,
		BALL_WIDTH, BALL_HEIGHT,
		1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		BALL_WIDTH, BALL_HEIGHT
	);
}

//-------------------
//�|���S���I������
//-------------------
void UninitBall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBall != NULL)
	{
		g_pTextureBall->Release();
		g_pTextureBall = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBall != NULL)
	{
		g_pVtxBuffBall->Release();
		g_pVtxBuffBall = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateBall(void)
{
	int nCntBall;
	for (nCntBall = 0; nCntBall < BALL_MAX; nCntBall++)
	{
		if (g_aBall[nCntBall].bUse)
		{
			g_aBall[nCntBall].nLife--;

			D3DXVec2Normalize(&g_aBall[nCntBall].dir, &g_aBall[nCntBall].dir);

			g_aBall[nCntBall].move.x = g_aBall[nCntBall].dir.x * BALL_SPEED;
			g_aBall[nCntBall].move.y = g_aBall[nCntBall].dir.y * BALL_SPEED;

			g_aBall[nCntBall].posOld = g_aBall[nCntBall].pos;

			g_aBall[nCntBall].pos += g_aBall[nCntBall].move;

			SetEffect(g_aBall[nCntBall].pos, D3DXVECTOR2(0.0f, 0.0f), D3DXCOLOR(0.1f, 0.5f, 0.4f, 0.1f), 1000, EFFECT_TYPE_NORMAL);

			if (g_aBall[nCntBall].nLife < 0)
			{
				g_aBall[nCntBall].bUse = false;
				SetParticle(g_aBall[nCntBall].pos);
			}
		}
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawBall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxScale, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�A���t�@�e�X�g�I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	int nCntBall;
	for (nCntBall = 0; nCntBall < BALL_MAX; nCntBall++)
	{
		if (g_aBall[nCntBall].bUse)
		{
			//�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aBall[nCntBall].mtxWorld);

			//�ʒu�̌v�Z
			D3DXMatrixTransformation2D(&mtxTrans, nullptr, 0.0f, nullptr, nullptr, 0.0f, &g_aBall[nCntBall].pos);
			D3DXMatrixMultiply(&g_aBall[nCntBall].mtxWorld, &g_aBall[nCntBall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBall[nCntBall].mtxWorld);

			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffBall, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBall);

			//�|���S���̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				0,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}

	//�A���t�@�e�X�g�I�t
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//----------
//�ݒ�
//----------
void SetBall(D3DXVECTOR2 pos, D3DXVECTOR2 dir)
{
	int nCntBall;
	for (nCntBall = 0; nCntBall < BALL_MAX; nCntBall++)
	{
		if (!g_aBall[nCntBall].bUse)
		{
			g_aBall[nCntBall].pos = pos;
			g_aBall[nCntBall].move = D3DXVECTOR2(0.0f, 0.0f);
			g_aBall[nCntBall].dir = dir;
			g_aBall[nCntBall].nLife = BALL_LIFE;
			g_aBall[nCntBall].bUse = true;
			break;
		}
	}
}