//---------------------------------------
//
//ボール処理[Sharp.cpp]
//Author fuma sato
//
//---------------------------------------
#include"Sharp.h"
#include"mesh.h"
#include"vectorcollision.h"
#include"rotation.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSharp = NULL;//バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSharp = NULL;
Sharp g_Sharp[SHARP_MAX];
//-----------------
// 初期化処理
//-----------------
void InitSharp(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
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

	//テクスチャの読み込み
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
	//1つ目

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
// 終了処理
//-----------------
void UninitSharp(void)
{
	SAFE_RELEASE(g_pTextureSharp);
	SAFE_RELEASE(g_pVtxBuffSharp);
}

//-----------------
// 更新処理
//-----------------
void UpdateSharp(void)
{

}

//-----------------
// 描画処理
//-----------------
void DrawSharp(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntSharp = 0; nCntSharp < SHARP_MAX; nCntSharp++)
	{
		if (g_Sharp[nCntSharp].bUse)
		{
			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffSharp, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureSharp);

			//ポリゴンの描画
			HRESULT hr = pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				nCntSharp * VT_MAX,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}
}

//-----------------
// 設定
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
// リフレクション
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