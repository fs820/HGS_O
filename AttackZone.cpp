//---------------------------------------
//
//アタックゾーン処理[AttackZone.cpp]
//Author fuma sato
//
//---------------------------------------
#include "AttackZone.h"
#include "camera.h"
#include "mesh.h"
#include "light.h"

AttackZone g_aAttackZone[ATTACK_ZONE_MAX];	// アタックゾーン情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAttackZone = NULL; //バッファのポインタ
LPDIRECT3DTEXTURE9 g_pTextureAttackZone = NULL;      //テクスチャのポインタ
//******************************************************
// アタックゾーン初期化
//******************************************************
void InitAttackZone(void)
{
	for (int nCntAttackZone = 0; nCntAttackZone < ATTACK_ZONE_MAX; nCntAttackZone++)
	{// 最大アタックゾーン分回す
		// 各種変数の初期化
		g_aAttackZone[nCntAttackZone].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	    // 位置
		g_aAttackZone[nCntAttackZone].fRadius = 0.0f;						    // 半径
		g_aAttackZone[nCntAttackZone].bLess = 0.0f;						        // 半径
		g_aAttackZone[nCntAttackZone].bUse = false;						        // 使用
		g_aAttackZone[nCntAttackZone].col = D3DXCOLOR(0.3f, 0.0f, 0.0f, 0.1f);	// 色
	}

	LPDIRECT3DDEVICE9 pDevice;//デバイスへポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4 * ATTACK_ZONE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_DEFAULT,
		&g_pVtxBuffAttackZone,
		NULL
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFileEx
	(
		pDevice,
		ATTACK_ZONE_TEX,
		D3DX_DEFAULT,              // テクスチャの幅（D3DX_DEFAULTなら自動調整）
		D3DX_DEFAULT,              // テクスチャの高さ（D3DX_DEFAULTなら自動調整）
		D3DX_DEFAULT,              // ミップマップレベル（D3DX_DEFAULTで自動設定）
		0,                         // 使用しない場合は0（動的テクスチャならD3DUSAGE_DYNAMIC）
		D3DFMT_X8R8G8B8,           // フォーマット（A8R8G8B8 png X8R8G8B8 jpg）
		D3DPOOL_DEFAULT,           // メモリプール（通常は D3DPOOL_MANAGED）
		D3DX_FILTER_TRIANGLE,      // 画像の拡縮フィルタ（D3DX_FILTER_LINEAR など）
		D3DX_FILTER_TRIANGLE,      // ミップマップのフィルタ
		0,                         // カラーキー（透明にしたい色）
		NULL,                      // `D3DXIMAGE_INFO`（画像情報を取得する場合）
		NULL,                      // パレットデータ（パレットなしならNULL）
		&g_pTextureAttackZone
	);

	//頂点の設定
	SetVertex3DZX
	(
		&g_pVtxBuffAttackZone,
		0, ATTACK_ZONE_MAX,
		1, 1,
		1.0f, 1.0f,
		D3DXVECTOR3(0.0f, 1.0f, 0.0f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
		1.0f, 1.0f
	);
}

//-----------------------------------------------------
//終了処理
//-----------------------------------------------------
void UninitAttackZone(void)
{
	for (int nCntAttackZone = 0; nCntAttackZone < ATTACK_ZONE_MAX; nCntAttackZone++)
	{// 最大アタックゾーン分回す
		// 各種変数の初期化
		g_aAttackZone[nCntAttackZone].bUse = false;	// 使用
		EndLight(4 + nCntAttackZone);				// ライトの終了
	}
	if (g_pTextureAttackZone != NULL)
	{
		g_pTextureAttackZone->Release();
		g_pTextureAttackZone = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffAttackZone != NULL)
	{
		g_pVtxBuffAttackZone->Release();
		g_pVtxBuffAttackZone = NULL;
	}
}

//------------------------------------------------------
//描画処理
//------------------------------------------------------
void DrawAttackZone(void)
{
	LPDIRECT3DDEVICE9 pDevice; // デバイスへのポインタ
	D3DXMATRIX mtxTrans; // 計算マトリックス

	// デバイスの取得
	pDevice = GetDevice();

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0); // 0の方が適切 sato
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Zテスト
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Depth Bias 設定 sato
	float depthBias = -0.000001f; //Zバッファをカメラ方向にオフセットする値

	// 遠いほうから描画する
	static int nIdx[ATTACK_ZONE_MAX]; // 遠い順格納用
	static int nLimit = 0;
	if (nLimit % 60 == 0)
	{// フレームごとに処理 (毎フレームやると重くなる可能性があるため)
		D3DXVECTOR3 PosList[ATTACK_ZONE_MAX]; // ポスリスト
		Camera* pCamera = GetCamera();
		for (int nCnt = 0; nCnt < ATTACK_ZONE_MAX; nCnt++)
		{// ポスリスト作成
			if (g_aAttackZone[nCnt].bUse)
			{
				PosList[nCnt] = g_aAttackZone[nCnt].pos;
			}
			else
			{
				PosList[nCnt] = pCamera->posV;
			}
		}
		DrawCameraFarSort(nIdx, PosList, ATTACK_ZONE_MAX); //遠い順にソート
	}
	nLimit++;

	for (int nCntAttackZone = 0; nCntAttackZone < ATTACK_ZONE_MAX; nCntAttackZone++)
	{
		if (g_aAttackZone[nIdx[nCntAttackZone]].bUse == false)
		{
			break;
		}

		if (g_aAttackZone[nIdx[nCntAttackZone]].bLess)
		{
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		else
		{
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		depthBias += -0.000001f; //影同士の重なりを避ける
		pDevice->SetRenderState(D3DRS_DEPTHBIAS, *(DWORD*)&depthBias); //Zバイアス設定

		// マトリックス初期化
		D3DXMatrixIdentity(&g_aAttackZone[nIdx[nCntAttackZone]].mtxWorld);

		// 位置の計算
		D3DXMatrixTranslation(&mtxTrans, g_aAttackZone[nIdx[nCntAttackZone]].pos.x, g_aAttackZone[nIdx[nCntAttackZone]].pos.y, g_aAttackZone[nIdx[nCntAttackZone]].pos.z);
		D3DXMatrixMultiply(&g_aAttackZone[nIdx[nCntAttackZone]].mtxWorld, &g_aAttackZone[nIdx[nCntAttackZone]].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aAttackZone[nIdx[nCntAttackZone]].mtxWorld);

		// 頂点バッファ
		pDevice->SetStreamSource(0, g_pVtxBuffAttackZone, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureAttackZone);

		for (int nCnt = 0; nCnt < 20; nCnt++)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,        // タイプ
				4 * nIdx[nCntAttackZone],
				2                          // ポリゴンの個数
			);
		}
	}

	// Depth Bias 設定を解除 sato
	float resetBias = 0.0f;
	pDevice->SetRenderState(D3DRS_DEPTHBIAS, *(DWORD*)&resetBias);

	// Zテストを戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// 設定をを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//******************************************************
// アタックゾーン設定
//******************************************************
int SetAttackZone(D3DXVECTOR3 pos, float fRadius, D3DXCOLOR col, bool Less)
{
	for (int nCntAttackZone = 0; nCntAttackZone < ATTACK_ZONE_MAX; nCntAttackZone++)
	{// 最大アタックゾーン分回す
		if (g_aAttackZone[nCntAttackZone].bUse == false)
		{// 使っていないアタックゾーン
			g_aAttackZone[nCntAttackZone].pos = pos;		    // 位置
			g_aAttackZone[nCntAttackZone].fRadius = fRadius;	// 半径
			g_aAttackZone[nCntAttackZone].col = col;	        // 半径
			g_aAttackZone[nCntAttackZone].bLess = Less;		// 減算
			g_aAttackZone[nCntAttackZone].bUse = true;		// 使用

			//頂点の設定
			SetVertex3DZX
			(
				&g_pVtxBuffAttackZone,
				nCntAttackZone,
				1,
				1,
				1,
				g_aAttackZone[nCntAttackZone].fRadius * 2.0f,
				g_aAttackZone[nCntAttackZone].fRadius * 2.0f,
				D3DXVECTOR3(0.0f, 1.0f, 0.0f),
				g_aAttackZone[nCntAttackZone].col,
				g_aAttackZone[nCntAttackZone].fRadius * 2.0f,
				g_aAttackZone[nCntAttackZone].fRadius * 2.0f
			);
			SetLight(4 + nCntAttackZone, g_aAttackZone[nCntAttackZone].fRadius, g_aAttackZone[nCntAttackZone].col * 20.0f, g_aAttackZone[nCntAttackZone].pos + D3DXVECTOR3(0.0f, g_aAttackZone[nCntAttackZone].fRadius * 0.5f, 0.0f));
			return nCntAttackZone;
		}
	}
	return -1;
}

//******************************************************
// アタックゾーン破棄
//******************************************************
void EndAttackZone(int nIdx)
{
	g_aAttackZone[nIdx].bUse = false;		// 使用
	EndLight(4 + nIdx);
}