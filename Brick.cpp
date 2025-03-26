//---------------------------------------
//
//ボール処理[Brick.cpp]
//Author fuma sato
//
//---------------------------------------
#include"Brick.h"
#include"mesh.h"
#include"vectorcollision.h"
#include"rotation.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBrick = NULL;//バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBrick = NULL;
Brick g_Brick[BRICK_MAX];
//-----------------
// 初期化処理
//-----------------
void InitBrick(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * BRICK_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBrick,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		BRICK_TEX,
		&g_pTextureBrick
	);

	for (int nCntBrick = 0; nCntBrick < BRICK_MAX; nCntBrick++)
	{
		g_Brick[nCntBrick].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Brick[nCntBrick].fAngle = 0.0f;
		g_Brick[nCntBrick].bUse = false;
	}
	//1つ目

	SetVertex2D
	(
		&g_pVtxBuffBrick,
		0, BRICK_MAX,
		1, 1,
		D3DXVECTOR2(0.0f, 0.0f), 0.0f,
		BRICK_WIDTH, BRICK_HEIGHT,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		BRICK_WIDTH, BRICK_HEIGHT
	);
}

//-----------------
// 終了処理
//-----------------
void UninitBrick(void)
{
	SAFE_RELEASE(g_pTextureBrick);
	SAFE_RELEASE(g_pVtxBuffBrick);
}

//-----------------
// 更新処理
//-----------------
void UpdateBrick(void)
{

}

//-----------------
// 描画処理
//-----------------
void DrawBrick(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntBrick = 0; nCntBrick < BRICK_MAX; nCntBrick++)
	{
		if (g_Brick[nCntBrick].bUse)
		{
			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffBrick, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBrick);

			//ポリゴンの描画
			HRESULT hr = pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				nCntBrick * VT_MAX,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}
}

//-----------------
// 設定
//-----------------
void SetBrick(D3DXVECTOR2 pos, float fAngle)
{
	for (int nCntBrick = 0; nCntBrick < BRICK_MAX; nCntBrick++)
	{
		if (g_Brick[nCntBrick].bUse == false)
		{
			g_Brick[nCntBrick].pos = pos;
			g_Brick[nCntBrick].fAngle = fAngle;

			SetVertex2D
			(
				&g_pVtxBuffBrick,
				nCntBrick, 1,
				1, 1,
				pos, fAngle,
				BRICK_WIDTH, BRICK_HEIGHT,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				BRICK_WIDTH, BRICK_HEIGHT
			);

			g_Brick[nCntBrick].bUse = true;
			break;
		}
	}
}

//--------------------------------
// リフレクション
//--------------------------------
void ReflectionBrick(D3DXVECTOR2& pos, D3DXVECTOR2& posOld, D3DXVECTOR2& move, float fWidth)
{
	for (int nCntBrick = 0; nCntBrick < BRICK_MAX; nCntBrick++)
	{
		if (g_Brick[nCntBrick].bUse)
		{
			D3DXVECTOR3 RightUp = D3DXVECTOR3(BRICK_WIDTH * 0.5f, -BRICK_HEIGHT * 0.5f, 0.0f),
				LeftUp = D3DXVECTOR3(-BRICK_WIDTH * 0.5f, -BRICK_HEIGHT * 0.5f, 0.0f),
				LeftDown = D3DXVECTOR3(-BRICK_WIDTH * 0.5f, BRICK_HEIGHT * 0.5f, 0.0f),
				RightDown = D3DXVECTOR3(BRICK_WIDTH * 0.5f, BRICK_HEIGHT * 0.5f, 0.0f);

			RotationofShaftbyMatrix(RightUp, RightUp, D3DXVECTOR3(0.0f, 0.0f, g_Brick[nCntBrick].fAngle), TYPE_Z);
			RotationofShaftbyMatrix(LeftUp, LeftUp, D3DXVECTOR3(0.0f, 0.0f, g_Brick[nCntBrick].fAngle), TYPE_Z);
			RotationofShaftbyMatrix(LeftDown, LeftDown, D3DXVECTOR3(0.0f, 0.0f, g_Brick[nCntBrick].fAngle), TYPE_Z);
			RotationofShaftbyMatrix(RightDown, RightDown, D3DXVECTOR3(0.0f, 0.0f, g_Brick[nCntBrick].fAngle), TYPE_Z);


			D3DXVECTOR2 RightUp2 = (D3DXVECTOR2)RightUp,
				LeftUp2 = (D3DXVECTOR2)LeftUp,
				LeftDown2 = (D3DXVECTOR2)LeftDown,
				RightDown2 = (D3DXVECTOR2)RightDown;

			RightUp2 += g_Brick[nCntBrick].pos;
			LeftUp2 += g_Brick[nCntBrick].pos;
			LeftDown2 += g_Brick[nCntBrick].pos;
			RightDown2 += g_Brick[nCntBrick].pos;

			for (int nCnt10 = 0; nCnt10 < 10; nCnt10++)
			{
				VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, RightUp2, LeftUp2);
				VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, LeftUp2, LeftDown2);
				VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, LeftDown2, RightDown2);
				VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, RightDown2, RightUp2);
			}
		}
	}
}