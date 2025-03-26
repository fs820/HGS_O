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
		g_aBall[nCntBall].nLife = 0;
		g_aBall[nCntBall].bUse = false;
	}
	//1つ目

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
//ポリゴン描画処理
//-------------------
void DrawBall(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxScale, mtxTrans;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();
	//アルファテストオン
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	int nCntBall;
	for (nCntBall = 0; nCntBall < BALL_MAX; nCntBall++)
	{
		if (g_aBall[nCntBall].bUse)
		{
			//マトリックス初期化
			D3DXMatrixIdentity(&g_aBall[nCntBall].mtxWorld);

			//位置の計算
			D3DXMatrixTransformation2D(&mtxTrans, nullptr, 0.0f, nullptr, nullptr, 0.0f, &g_aBall[nCntBall].pos);
			D3DXMatrixMultiply(&g_aBall[nCntBall].mtxWorld, &g_aBall[nCntBall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBall[nCntBall].mtxWorld);

			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffBall, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBall);

			//ポリゴンの描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				0,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}

	//アルファテストオフ
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
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
			g_aBall[nCntBall].nLife = BALL_LIFE;
			g_aBall[nCntBall].bUse = true;
			break;
		}
	}
}