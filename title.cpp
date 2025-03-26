
#include "title.h"
#include "fade.h"
#include "sound.h"
#include <math.h>
#include "input.h"

// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureThankyou[TITLE_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			// 頂点バッファへのポインタ
THANKYOU g_thankyou[TITLE_MAX];							// サンキューの情報

//*********************************************
// サンキュー画面の初期化処理
//*********************************************
void InitTitle(void)
{
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLE_MAX, // 必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_DEFAULT,
		&g_pVtxBuffTitle,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < TITLE_MAX; nCount++)
	{
		// 背景テクスチャの読み込み
		D3DXCreateTextureFromFileEx(pDevice,
			THANKYOU_BACKGROUND[nCount],
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
			&g_pTextureThankyou[nCount]);

		switch (nCount)
		{
		case BACKGROUND:		// 星空
			g_thankyou[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);	// 位置の設定
			g_thankyou[nCount].fWidth = SCREEN_WIDTH * 0.5f;										// 幅の設定
			g_thankyou[nCount].fHeight = SCREEN_HEIGHT * 0.5f;										// 高さの設定
			break;

		case MOVING_BACKGROUND:		// 星空
			g_thankyou[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);	// 位置の設定
			g_thankyou[nCount].fWidth = SCREEN_WIDTH * 0.5f;										// 幅の設定
			g_thankyou[nCount].fHeight = SCREEN_HEIGHT * 0.5f;										// 高さの設定
			break;

		case TITLE_BUTTON:		// かわいい女の子
			g_thankyou[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);	// 位置の設定
			g_thankyou[nCount].fWidth = SCREEN_WIDTH * 0.15f;										// 幅の設定
			g_thankyou[nCount].fHeight = SCREEN_HEIGHT * 0.028f;										// 高さの設定
			break;
		}

		// 頂点座標の設定
		pVtx[0 + (4 * nCount)].pos = g_thankyou[nCount].pos + D3DXVECTOR3(-g_thankyou[nCount].fWidth, -g_thankyou[nCount].fHeight, 0.0f);
		pVtx[1 + (4 * nCount)].pos = g_thankyou[nCount].pos + D3DXVECTOR3(g_thankyou[nCount].fWidth, -g_thankyou[nCount].fHeight, 0.0f);
		pVtx[2 + (4 * nCount)].pos = g_thankyou[nCount].pos + D3DXVECTOR3(-g_thankyou[nCount].fWidth, g_thankyou[nCount].fHeight, 0.0f);
		pVtx[3 + (4 * nCount)].pos = g_thankyou[nCount].pos + D3DXVECTOR3(g_thankyou[nCount].fWidth, g_thankyou[nCount].fHeight, 0.0f);

		// rhwの設定
		pVtx[0 + (4 * nCount)].rhw = 1.0f;
		pVtx[1 + (4 * nCount)].rhw = 1.0f;
		pVtx[2 + (4 * nCount)].rhw = 1.0f;
		pVtx[3 + (4 * nCount)].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGM, 1.0f);

}

//*********************************************
// サンキュー画面の終了処理
//*********************************************
void UninitTitle(void)
{
	for (int nCount = 0; nCount < TITLE_MAX; nCount++)
	{
		// 頂点バッファの破棄
		if (g_pTextureThankyou[nCount] != NULL)
		{
			g_pTextureThankyou[nCount]->Release();
			g_pTextureThankyou[nCount] = NULL;
		}
	}

	// 背景テクスチャの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//*********************************************
// サンキュー画面の更新処理
//*********************************************
void UpdateTitle(void)
{
	VERTEX_2D* pVtx;  // 頂点情報へのポインタ
	HWND hWnd = GetHWND();



	if (GetKeyboardTrigger(DIK_RETURN))
	{
		FADE fade = GetFade(); //sato
		if (fade == FADE_NONE)
		{//遷移中でない sato
			SetFade(MODE_GAME, 2.0f);
		}

		StopSound(SOUND_LABEL_BGM);
	}

	
	static float scrollOffset = 0.0f; // Смещение текстуры
	const float scrollSpeed = 0.00025f;  // Скорость движения

	// Обновление смещения
	scrollOffset += scrollSpeed;
	if (scrollOffset >= 1.0f) {
		scrollOffset -= 1.0f; // Циклический сброс
	}
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// Установка текстурных координат с повторением
	pVtx[0 + (4 * MOVING_BACKGROUND)].tex = D3DXVECTOR2(scrollOffset, 0.0f);
	pVtx[1 + (4 * MOVING_BACKGROUND)].tex = D3DXVECTOR2(scrollOffset + 1.0f, 0.0f);
	pVtx[2 + (4 * MOVING_BACKGROUND)].tex = D3DXVECTOR2(scrollOffset, 1.0f);
	pVtx[3 + (4 * MOVING_BACKGROUND)].tex = D3DXVECTOR2(scrollOffset + 1.0f, 1.0f);


	// Глобальные переменные для анимации кнопки
	static float scaleFactor = 1.0f;    // Коэффициент масштабирования
	const float scaleSpeed = 0.0025f;   // Скорость изменения
	static bool isGrowing = true;       // Флаг увеличения

	// Обновление масштаба кнопки
	if (isGrowing) {
		scaleFactor += scaleSpeed;
		if (scaleFactor >= 1.05f) {
			scaleFactor = 1.05f;
			isGrowing = false;
		}
	}
	else {
		scaleFactor -= scaleSpeed;
		if (scaleFactor <= 0.95f) {
			scaleFactor = 0.95f;
			isGrowing = true;
		}
	}

	// Блокировка буфера вершин
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// Обновление размеров кнопки с учетом анимации
	pVtx[0 + (4 * TITLE_BUTTON)].pos = g_thankyou[TITLE_BUTTON].pos + D3DXVECTOR3(-g_thankyou[TITLE_BUTTON].fWidth * scaleFactor, -g_thankyou[TITLE_BUTTON].fHeight * scaleFactor, 0.0f);
	pVtx[1 + (4 * TITLE_BUTTON)].pos = g_thankyou[TITLE_BUTTON].pos + D3DXVECTOR3(g_thankyou[TITLE_BUTTON].fWidth * scaleFactor, -g_thankyou[TITLE_BUTTON].fHeight * scaleFactor, 0.0f);
	pVtx[2 + (4 * TITLE_BUTTON)].pos = g_thankyou[TITLE_BUTTON].pos + D3DXVECTOR3(-g_thankyou[TITLE_BUTTON].fWidth * scaleFactor, g_thankyou[TITLE_BUTTON].fHeight * scaleFactor, 0.0f);
	pVtx[3 + (4 * TITLE_BUTTON)].pos = g_thankyou[TITLE_BUTTON].pos + D3DXVECTOR3(g_thankyou[TITLE_BUTTON].fWidth * scaleFactor, g_thankyou[TITLE_BUTTON].fHeight * scaleFactor, 0.0f);


		g_pVtxBuffTitle->Unlock();

}

//*********************************************
// サンキュー画面の描画処理
//*********************************************
void DrawTitle(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 180);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < TITLE_MAX; nCount++)
	{
		pDevice->SetTexture(0, g_pTextureThankyou[nCount]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount, 2);
	}


	// アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}