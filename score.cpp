//---------------------------------------
//
//スコア処理[score.cpp]
//Author fuma sato
//
//---------------------------------------

#include "score.h"
#include "fade.h"
#include "sound.h"
#include <math.h>
#include "input.h"

#include <fstream>

// Глобальная переменная для общего счета
int totalScore = 0;



// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureScore[SCORE_UI_MAX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			// 頂点バッファへのポインタ
THANKYOU g_score[SCORE_UI_MAX];							// スコアの情報

//*********************************************
// スコア画面の初期化処理
//*********************************************
void InitScore(void)
{
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SCORE_UI_MAX, // 必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_DEFAULT,
		&g_pVtxBuffScore,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < SCORE_UI_MAX; nCount++)
	{
		// スコアテクスチャの読み込み
		D3DXCreateTextureFromFileEx(pDevice,
			SCORE_TEXTURES[nCount],
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
			&g_pTextureScore[nCount]);

		switch (nCount)
		{
		case SCORE_UI:		// スコア背景
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.81f, SCREEN_HEIGHT * 0.18f, 0.0f);	// 位置の設定
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.06f;										// 幅の設定
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// 高さの設定
			break;

		case SCORE_UI_ONE:		// 数字（1）
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.89f, SCREEN_HEIGHT * 0.18f, 0.0f);	// 位置の設定
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.015f;										// 幅の設定
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// 高さの設定
			break;

		case SCORE_UI_TWO:		// 数字（2）
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.92f, SCREEN_HEIGHT * 0.18f, 0.0f);	// 位置の設定
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.015f;										// 幅の設定
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// 高さの設定
			break;

		case SCORE_UI_THREE:		// 数字（3）
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.95f, SCREEN_HEIGHT * 0.18f, 0.0f);	// 位置の設定
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.015f;										// 幅の設定
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// 高さの設定
			break;
		}

		// 頂点座標の設定
		pVtx[0 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(-g_score[nCount].fWidth, -g_score[nCount].fHeight, 0.0f);
		pVtx[1 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(g_score[nCount].fWidth, -g_score[nCount].fHeight, 0.0f);
		pVtx[2 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(-g_score[nCount].fWidth, g_score[nCount].fHeight, 0.0f);
		pVtx[3 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(g_score[nCount].fWidth, g_score[nCount].fHeight, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//*********************************************
// スコア画面の終了処理
//*********************************************
void UninitScore(void)
{
	for (int nCount = 0; nCount < SCORE_UI_MAX; nCount++)
	{
		// 頂点バッファの破棄
		if (g_pTextureScore[nCount] != NULL)
		{
			g_pTextureScore[nCount]->Release();
			g_pTextureScore[nCount] = NULL;
		}
	}

	// 背景テクスチャの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

// Функция для обновления отображаемого счета
void UpdateScore(int score)  // Теперь передаем параметр `score` в функцию
{
	VERTEX_2D* pVtx;  // Пойнтер на вершины

	// Разбиваем счет на десятки, сотни и единицы
	int scoreHundreds = (score / 100) % 10; // Цифра сотен
	int scoreTens = (score / 10) % 10;      // Цифра десятков
	int scoreOnes = score % 10;             // Цифра единиц

	// Локируем буфер вершин
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// Устанавливаем текстурные координаты для сотен
	pVtx[4].tex = D3DXVECTOR2(scoreHundreds * 0.1f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(scoreHundreds * 0.1f + 0.1f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(scoreHundreds * 0.1f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(scoreHundreds * 0.1f + 0.1f, 1.0f);

	// Устанавливаем текстурные координаты для десятков
	pVtx[8].tex = D3DXVECTOR2(scoreTens * 0.1f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(scoreTens * 0.1f + 0.1f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(scoreTens * 0.1f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(scoreTens * 0.1f + 0.1f, 1.0f);

	// Устанавливаем текстурные координаты для единиц
	pVtx[12].tex = D3DXVECTOR2(scoreOnes * 0.1f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(scoreOnes * 0.1f + 0.1f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(scoreOnes * 0.1f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(scoreOnes * 0.1f + 0.1f, 1.0f);

	// Разблокируем буфер вершин
	g_pVtxBuffScore->Unlock();
}



void DrawScore(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 180);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをセット
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	// 各スコアUIを描画
	for (int nCount = 0; nCount < SCORE_UI_MAX; nCount++)
	{
		pDevice->SetTexture(0, g_pTextureScore[nCount]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount, 2);
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}


//--------------------
//桁分割処理
//--------------------
int Digit(int nData, int nDigit)
{
	int aNumber[SCORE_MAX - 1] = { 0 };//分割用配列
	int nData2 = 1;//計算用

	for (int i = SCORE_MAX - 2; i >= 0; i--)
	{//桁数分
		if (i == 0)
		{
			aNumber[i] = nData / nData2;//最上位の桁
		}
		aNumber[i] = nData % (nData2 * DIGIT) / nData2;//計算
		nData2 *= DIGIT;//桁引き上げ
	}

	return aNumber[nDigit];//指定の桁を返す
}

// Функция для добавления очков
void AddScore(int scoreToAdd) {
	totalScore += scoreToAdd;
	UpdateScore(totalScore);
}

// Функция для сохранения счета в файл (если нужно)
void SaveScore(int score) {
	const char* fileName = "score.txt"; // Имя файла для сохранения

	// Открываем файл для записи
	std::ofstream outFile(fileName, std::ios::app);  // Открываем в режиме добавления (append)
	if (outFile.is_open()) {
		outFile << "Score: " << score << std::endl;
		outFile.close();
	}
}