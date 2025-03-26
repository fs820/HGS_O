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
#include "Line.h"
#include "block.h"
#include "Brick.h"
#include "Sharp.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBall = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBall = NULL;
Ball g_Ball;
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

	g_Ball.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Ball.posOld = D3DXVECTOR2(0.0f, 0.0f);
	g_Ball.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Ball.dir = D3DXVECTOR2(0.0f, 0.0f);
	g_Ball.nCnt = 0;

	//1��

	SetVertex2D
	(
		&g_pVtxBuffBall,
		0, 1,
		1, 1,
		g_Ball.pos, 0.0f,
		BALL_WIDTH, BALL_HEIGHT,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		BALL_WIDTH, BALL_HEIGHT
	);

	float Rot = ROT_RAND;
	SetBall(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(sinf(Rot), cosf(Rot)));
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
	if (g_Ball.nCnt != 0)
	{
		g_Ball.nCnt--;
		if (g_Ball.nCnt == 0)
		{
			float Rot = ROT_RAND;
			SetBall(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(sinf(Rot), cosf(Rot)));
		}
	}
	else
	{
		D3DXVec2Normalize(&g_Ball.dir, &g_Ball.dir);

		g_Ball.move.x = g_Ball.dir.x * BALL_SPEED;
		g_Ball.move.y = g_Ball.dir.y * BALL_SPEED;

		g_Ball.posOld = g_Ball.pos;

		g_Ball.pos += g_Ball.move;

		ReflectionBrick(g_Ball.pos, g_Ball.posOld, g_Ball.move, BALL_WIDTH);

		ReflectionLine(g_Ball.pos, g_Ball.posOld, g_Ball.move, BALL_WIDTH);

		ReflectionBlock(g_Ball.pos, g_Ball.posOld, g_Ball.move, BALL_WIDTH);

		D3DXVec2Normalize(&g_Ball.dir, &g_Ball.move);

		if (g_Ball.pos.x < 0.0f || g_Ball.pos.x > SCREEN_WIDTH || g_Ball.pos.y < 0.0f || g_Ball.pos.y > SCREEN_HEIGHT)
		{
			g_Ball.nCnt = 180;
		}

		if (HitSharp(g_Ball.pos, g_Ball.posOld, g_Ball.move, BALL_WIDTH))
		{
			SetParticle(g_Ball.pos);

			g_Ball.nCnt = 180;
		}

		SetVertex2D
		(
			&g_pVtxBuffBall,
			0, 1,
			1, 1,
			g_Ball.pos, 0.0f,
			BALL_WIDTH, BALL_HEIGHT,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			BALL_WIDTH, BALL_HEIGHT
		);

		SetEffect(g_Ball.pos, D3DXVECTOR2(0.0f, 0.0f), D3DXCOLOR(0.1f, 0.5f, 0.4f, 0.01f), 5, EFFECT_TYPE_NORMAL);
	}
}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawBall(void)
{
	if (g_Ball.nCnt == 0)
	{
		LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@
		pDevice->SetStreamSource(0, g_pVtxBuffBall, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBall);

		//�|���S���̕`��
		HRESULT hr = pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,//�^�C�v
			0,//�n�܂�̔ԍ�
			2//�|���S���̌�
		);
	}
}

//----------
//�ݒ�
//----------
void SetBall(D3DXVECTOR2 pos, D3DXVECTOR2 dir)
{
	g_Ball.pos = pos;
	g_Ball.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Ball.dir = dir;
	g_Ball.nCnt = 0;
}