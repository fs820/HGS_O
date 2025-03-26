//------------------------------------------
//
//背景処理[Back.cpp]
//Author fuma sato
//
//------------------------------------------
#include"Back.h"
#include "mesh.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBack = NULL;//バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBack = NULL;
//-------------
//初期化処理
//-------------
void InitBack(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//バッファーの設定
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBack,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		BACK_TEX,
		&g_pTextureBack
	);

	VERTEX_2D* pVtx;
	g_pVtxBuffBack->Lock(0, 0, (void**)&pVtx, 0);//プレイヤーバッファのロック

	//座標設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBuffBack->Unlock();//プレイヤーバッファのアンロック
}

//-----------------
//終了処理
//-----------------
void UninitBack(void)
{
	//テクスチャの破棄
	SAFE_RELEASE(g_pTextureBack);
	//頂点バッファの破棄
	SAFE_RELEASE(g_pVtxBuffBack);
}

//-----------------
//更新処理
//-----------------
void UpdateBack(void)
{

}

//----------------
//描画処理
//----------------
void DrawBack(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファ
	pDevice->SetStreamSource(0, g_pVtxBuffBack, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBack);

	//背景の描画
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,//タイプ
		0,//始まりの番号
		2//ポリゴンの個数
	);
}