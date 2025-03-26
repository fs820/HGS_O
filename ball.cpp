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
#include "Sharp.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBall = NULL;//バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBall = NULL;
Ball g_Ball;
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

	g_Ball.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Ball.posOld = D3DXVECTOR2(0.0f, 0.0f);
	g_Ball.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Ball.dir = D3DXVECTOR2(0.0f, 0.0f);
	g_Ball.nCnt = 0;

	//1つ目

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
//ポリゴン描画処理
//-------------------
void DrawBall(void)
{
	if (g_Ball.nCnt == 0)
	{
		LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

		//デバイスの取得
		pDevice = GetDevice();

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

//----------
//設定
//----------
void SetBall(D3DXVECTOR2 pos, D3DXVECTOR2 dir)
{
	g_Ball.pos = pos;
	g_Ball.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Ball.dir = dir;
	g_Ball.nCnt = 0;
}