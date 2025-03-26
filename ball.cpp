//----------------------------------------
//
//ボール処理[ball.cpp]
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

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBall = NULL;//バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBall = NULL;
Ball g_aBall[BALL_MAX];

//----------------------
//ポリゴンの初期化処理
//----------------------
void InitBall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
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

	//テクスチャの読み込み
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
		g_aBall[nCntBall].bUse = false;
	}
	//1つ目

	SetVertex2D
	(
		&g_pVtxBuffBall,
		0, 1,
		1, 1,
		g_aBall[nCntBall].pos, 0.0f,
		BALL_WIDTH, BALL_HEIGHT,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		BALL_WIDTH, BALL_HEIGHT
	);
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitBall(void)
{
	//テクスチャの破棄
	if (g_pTextureBall != NULL)
	{
		g_pTextureBall->Release();
		g_pTextureBall = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBall != NULL)
	{
		g_pVtxBuffBall->Release();
		g_pVtxBuffBall = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateBall(void)
{
	int nCntBall;
	for (nCntBall = 0; nCntBall < BALL_MAX; nCntBall++)
	{
		if (g_aBall[nCntBall].bUse)
		{
			D3DXVec2Normalize(&g_aBall[nCntBall].dir, &g_aBall[nCntBall].dir);

			g_aBall[nCntBall].move.x = g_aBall[nCntBall].dir.x * BALL_SPEED;
			g_aBall[nCntBall].move.y = g_aBall[nCntBall].dir.y * BALL_SPEED;

			g_aBall[nCntBall].posOld = g_aBall[nCntBall].pos;

			g_aBall[nCntBall].pos += g_aBall[nCntBall].move;

			ReflectionBrick(g_aBall[nCntBall].pos, g_aBall[nCntBall].posOld, g_aBall[nCntBall].move, BALL_WIDTH);

			ReflectionLine(g_aBall[nCntBall].pos, g_aBall[nCntBall].posOld, g_aBall[nCntBall].move, BALL_WIDTH);

			ReflectionBlock(g_aBall[nCntBall].pos, g_aBall[nCntBall].posOld, g_aBall[nCntBall].move, BALL_WIDTH);

			D3DXVec2Normalize(&g_aBall[nCntBall].dir, &g_aBall[nCntBall].move);

			SetVertex2D
			(
				&g_pVtxBuffBall,
				0, 1,
				1, 1,
				g_aBall[nCntBall].pos, 0.0f,
				BALL_WIDTH, BALL_HEIGHT,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				BALL_WIDTH, BALL_HEIGHT
			);

			SetEffect(g_aBall[nCntBall].pos, D3DXVECTOR2(0.0f, 0.0f), D3DXCOLOR(0.1f, 0.5f, 0.4f, 0.01f), 5, EFFECT_TYPE_NORMAL);
		}
	}
}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawBall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	int nCntBall;
	for (nCntBall = 0; nCntBall < BALL_MAX; nCntBall++)
	{
		if (g_aBall[nCntBall].bUse)
		{
			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffBall, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBall);

			//ポリゴンの描画
			HRESULT hr = pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				0,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}
}

//----------
//設定
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
			g_aBall[nCntBall].bUse = true;
			break;
		}
	}
}