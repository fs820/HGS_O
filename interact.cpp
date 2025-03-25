//----------------------------------------
//
//インタラクト処理[interact.cpp]
//Author fuma sato
//
//----------------------------------------

#include"interact.h"
#include"mesh.h"
#include"camera.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffInteract = NULL;                   //バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureInteract[INTERACT_TYPE_MAX] = { NULL }; //テクスチャのポインタ
Interact g_Interact;                                                 //情報体
//----------------------
//ポリゴンの初期化処理
//----------------------
void InitInteract(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_DEFAULT,
		&g_pVtxBuffInteract,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFileEx
	(
		pDevice,
		INTERACT_TEX_KEY,
		D3DX_DEFAULT,              // テクスチャの幅（D3DX_DEFAULTなら自動調整）
		D3DX_DEFAULT,              // テクスチャの高さ（D3DX_DEFAULTなら自動調整）
		D3DX_DEFAULT,              // ミップマップレベル（D3DX_DEFAULTで自動設定）
		0,                         // 使用しない場合は0（動的テクスチャならD3DUSAGE_DYNAMIC）
		D3DFMT_A8R8G8B8,           // フォーマット（D3DFMT_A8R8G8B8 など）
		D3DPOOL_DEFAULT,           // メモリプール（通常は D3DPOOL_MANAGED）
		D3DX_FILTER_BOX,           // 画像の拡縮フィルタ（D3DX_FILTER_LINEAR など）
		D3DX_FILTER_BOX,           // ミップマップのフィルタ
		0,                         // カラーキー（透明にしたい色）
		NULL,                      // `D3DXIMAGE_INFO`（画像情報を取得する場合）
		NULL,                      // パレットデータ（パレットなしならNULL）
		&g_pTextureInteract[INTERACT_TYPE_KEY]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFileEx
	(
		pDevice,
		INTERACT_TEX_JOY,
		D3DX_DEFAULT,              // テクスチャの幅（D3DX_DEFAULTなら自動調整）
		D3DX_DEFAULT,              // テクスチャの高さ（D3DX_DEFAULTなら自動調整）
		D3DX_DEFAULT,              // ミップマップレベル（D3DX_DEFAULTで自動設定）
		0,                         // 使用しない場合は0（動的テクスチャならD3DUSAGE_DYNAMIC）
		D3DFMT_A8R8G8B8,           // フォーマット（A8R8G8B8 png X8R8G8B8 jpg）
		D3DPOOL_DEFAULT,           // メモリプール（通常は D3DPOOL_MANAGED）
		D3DX_FILTER_TRIANGLE,      // 画像の拡縮フィルタ（D3DX_FILTER_LINEAR など）
		D3DX_FILTER_TRIANGLE,      // ミップマップのフィルタ
		0,                         // カラーキー（透明にしたい色）
		NULL,                      // `D3DXIMAGE_INFO`（画像情報を取得する場合）
		NULL,                      // パレットデータ（パレットなしならNULL）
		&g_pTextureInteract[INTERACT_TYPE_JOY]
	);

	//情報体の初期化
	g_Interact.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Interact.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Interact.Type = INTERACT_TYPE_KEY;
	g_Interact.bUse = false;

	//頂点の設定
	SetVertex3DYX
	(
		&g_pVtxBuffInteract,
		0,
		1,
		1,
		1,
		INTERACT_WIDTH,
		INTERACT_HEIGHT,
		D3DXVECTOR3(0.0f, 0.0f, -1.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		INTERACT_WIDTH,
		INTERACT_HEIGHT,
		false, false
	);
}

//-------------------
//ポリゴン終了処理
//-------------------
void UninitInteract(void)
{
	g_Interact.bUse = false;

	//テクスチャの破棄
	for (int nCntTex = 0; nCntTex < INTERACT_TYPE_MAX; nCntTex++)
	{
		if (g_pTextureInteract[nCntTex] != NULL)
		{
			g_pTextureInteract[nCntTex]->Release();
			g_pTextureInteract[nCntTex] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffInteract != NULL)
	{
		g_pVtxBuffInteract->Release();
		g_pVtxBuffInteract = NULL;
	}
}

//-------------------
//ポリゴン更新処理
//-------------------
void UpdateInteract(void)
{

}

//-------------------
//ポリゴン描画処理
//-------------------
void DrawInteract(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ
	D3DXMATRIX mtxScale, mtxTrans;//計算マトリックス

	//デバイスの取得
	pDevice = GetDevice();
	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Zテスト
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	if (g_Interact.bUse)
	{//使っている
		//マトリックス初期化
		D3DXMatrixIdentity(&g_Interact.mtxWorld);

		//ビューマトリックス取得
		D3DXMATRIX mtxView;
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//カメラの逆行列を設定
		g_Interact.mtxWorld._11 = mtxView._11;
		g_Interact.mtxWorld._12 = mtxView._21;
		g_Interact.mtxWorld._13 = mtxView._31;
		g_Interact.mtxWorld._21 = mtxView._12;
		g_Interact.mtxWorld._22 = mtxView._22;
		g_Interact.mtxWorld._23 = mtxView._32;
		g_Interact.mtxWorld._31 = mtxView._13;
		g_Interact.mtxWorld._32 = mtxView._23;
		g_Interact.mtxWorld._33 = mtxView._33;

		//大きさの反映
		D3DXMatrixScaling(&mtxScale, g_Interact.scale.x, g_Interact.scale.y, g_Interact.scale.z);
		D3DXMatrixMultiply(&g_Interact.mtxWorld, &g_Interact.mtxWorld, &mtxScale);

		//位置の計算
		D3DXMatrixTranslation(&mtxTrans, g_Interact.pos.x, g_Interact.pos.y, g_Interact.pos.z);
		D3DXMatrixMultiply(&g_Interact.mtxWorld, &g_Interact.mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Interact.mtxWorld);

		//頂点バッファ
		pDevice->SetStreamSource(0, g_pVtxBuffInteract, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureInteract[g_Interact.Type]);

		//ポリゴンの描画
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,//タイプ
			0,//始まりの番号
			2//ポリゴンの個数
		);
	}

	// Zテストを戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);


	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//----------
//設定
//----------
void SetInteract(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	g_Interact.pos = pos;      //位置
	g_Interact.pos.y += 50.0f; //少し上げる
	g_Interact.scale = scale;  //大きさ
	g_Interact.bUse = true;    //使用
}

//----------------------
//破棄
//----------------------
void EndInteract(void)
{
	g_Interact.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //位置
	g_Interact.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f); //大きさ
	g_Interact.bUse = false;                          //使用
}

//---------------------
//タイプ変更
//---------------------
void SetInteractType(INTERACT_TYPE Type)
{
	g_Interact.Type = Type;
}