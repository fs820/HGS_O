//---------------------------------------
//
//エフェクト表示処理[effect.cpp]
//Author fuma sato
//
//---------------------------------------

#include"effect.h"
#include"ball.h"
#include"mesh.h"

//弾構造体
typedef struct
{
	D3DXVECTOR2 pos;//位置
	D3DXVECTOR2 move;
	D3DXCOLOR col;
	int nLife;//寿命
	EFFECT_TYPE Type;
	bool bUse;//使用しているかどうか
}Effect;

//グローバル
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//バッファのポインタ
Effect g_aEffect[MAX_EFFECT];//弾の情報
int g_nLifeDef[MAX_EFFECT] = { 0 };

//-----------------
//弾の初期化処理
//-----------------
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得
	pDevice = GetDevice();

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_aEffect[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_aEffect[i].move = D3DXVECTOR2(0.0f, 0.0f);
		g_aEffect[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect[i].nLife = 0;
		g_aEffect[i].Type = EFFECT_TYPE_NORMAL;
		g_aEffect[i].bUse = false;//使用していない状態にする
	}

	//バッファの作成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		EFFECT_TEX,
		&g_pTextureEffect
	);


	SetVertex2D
	(
		&g_pVtxBuffEffect,
		0, MAX_EFFECT,
		1, 1,
		D3DXVECTOR2(0.0f, 0.0f),0.0f,
		EFFECT_SIZE_DEF, EFFECT_SIZE_DEF,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		EFFECT_SIZE_DEF, EFFECT_SIZE_DEF
	);
}

//----------------
//弾の終了処理
//----------------
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//----------------
//弾の更新処理
//----------------
void UpdateEffect(void)
{
	VERTEX_2D* pVtx;
	static D3DXVECTOR2 Oldpos[MAX_EFFECT];

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_aEffect[i].bUse == true)
		{//弾が使用されている

			Oldpos[i] = g_aEffect[i].pos;

			g_aEffect[i].pos.x += g_aEffect[i].move.x;
			g_aEffect[i].pos.y += g_aEffect[i].move.y;

			SetVertex2D
			(
				&g_pVtxBuffEffect,
				i, 1,
				1, 1,
				g_aEffect[i].pos,0.0f,
				EFFECT_SIZE_DEF * ((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i]), EFFECT_SIZE_DEF * ((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i]),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				EFFECT_SIZE_DEF * ((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i]), EFFECT_SIZE_DEF * ((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i])
			);

			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += i * VT_MAX;//ポリゴン1つ分進める
			BYTE alpha = (BYTE)(((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i]) * 255.0f);
			pVtx[0].col = (pVtx[0].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[1].col = (pVtx[1].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[2].col = (pVtx[2].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[3].col = (pVtx[3].col & 0x00FFFFFF) | (alpha << 24);

			g_pVtxBuffEffect->Unlock();//バッファのアンロック

			g_aEffect[i].nLife--;

			if (g_aEffect[i].nLife <= 0)
			{
				g_aEffect[i].bUse = false;
			}
		}
	}
}

//----------------
//弾の描画処理
//----------------
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//加算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	int nCntEffect;
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse)
		{
			//頂点バッファ
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

			//ポリゴンの描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//タイプ
				nCntEffect * VT_MAX,//始まりの番号
				2//ポリゴンの個数
			);
		}
	}

	//通常
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//-------------------
//発通常弾
//-------------------
void SetEffect(D3DXVECTOR2 pos, D3DXVECTOR2 move, D3DXCOLOR col, int nLife, EFFECT_TYPE Type)
{
	VERTEX_3D* pVtx;

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_aEffect[i].bUse == false)
		{//弾が使用されていない
			g_aEffect[i].pos = pos;
			g_aEffect[i].move = move;
			g_aEffect[i].col = col;

			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

			//頂点座標設定
			pVtx += i * VT_MAX;//ポリゴン1つ分進める
			pVtx[0].col = g_aEffect[i].col;
			pVtx[1].col = g_aEffect[i].col;
			pVtx[2].col = g_aEffect[i].col;
			pVtx[3].col = g_aEffect[i].col;

			g_pVtxBuffEffect->Unlock();//バッファのアンロック

			g_aEffect[i].nLife = nLife;
			g_nLifeDef[i] = g_aEffect[i].nLife;
			g_aEffect[i].Type = Type;
			g_aEffect[i].bUse = true;

			break;
		}
	}
}