#include "timer.h"
#include "fade.h"
#include "sound.h"
#include <math.h>
#include "input.h"
#include "score.h"

// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTimer[TIMER_MAX] = {};    // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;        // 頂点バッファへのポインタ
TIMER g_timer[TIMER_MAX];                               // タイマーの情報

//*********************************************
// タイマー画面の初期化処理
//*********************************************
void InitTimer(void)
{
    VERTEX_2D* pVtx;

    LPDIRECT3DDEVICE9 pDevice;

    // デバイスの取得
    pDevice = GetDevice();

    // 頂点バッファの生成
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIMER_MAX, // 必要な頂点数
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_2D,
        D3DPOOL_DEFAULT,
        &g_pVtxBuffTimer,
        NULL);

    // 頂点バッファをロックし、頂点情報へのポインタを取得
    g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

    for (int nCount = 0; nCount < TIMER_MAX; nCount++)
    {
        // タイマー関連のテクスチャの読み込み
        D3DXCreateTextureFromFileEx(pDevice,
            TIMER_TEXTURES[nCount],
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
            &g_pTextureTimer[nCount]);

        // タイマーの位置とサイズ設定
        

        switch (nCount)
        {
        case TIMER_LABEL:		// 星空
            g_timer[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.1f, 0.0f);  // 位置の設定
            g_timer[nCount].fWidth = SCREEN_WIDTH * 0.05f;                                       // 幅の設定
            g_timer[nCount].fHeight = SCREEN_HEIGHT * 0.025f;                                      // 高さの設定
            break;

        case TIMER_DIGITS:		// 星空
            g_timer[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.87f, SCREEN_HEIGHT * 0.1f, 0.0f);  // 位置の設定
            g_timer[nCount].fWidth = SCREEN_WIDTH * 0.015f;                                       // 幅の設定
            g_timer[nCount].fHeight = SCREEN_HEIGHT * 0.025f;                                      // 高さの設定
            break;

        case TIMER_DIGITS_TWO:		// 星空
            g_timer[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.1f, 0.0f);  // 位置の設定
            g_timer[nCount].fWidth = SCREEN_WIDTH * 0.015f;                                       // 幅の設定
            g_timer[nCount].fHeight = SCREEN_HEIGHT * 0.025f;                                      // 高さの設定
            break;

        }
        // 頂点座標の設定
        pVtx[0 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(-g_timer[nCount].fWidth, -g_timer[nCount].fHeight, 0.0f);
        pVtx[1 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(g_timer[nCount].fWidth, -g_timer[nCount].fHeight, 0.0f);
        pVtx[2 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(-g_timer[nCount].fWidth, g_timer[nCount].fHeight, 0.0f);
        pVtx[3 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(g_timer[nCount].fWidth, g_timer[nCount].fHeight, 0.0f);

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
    g_pVtxBuffTimer->Unlock();
}

//*********************************************
// タイマー画面の終了処理
//*********************************************
void UninitTimer(void)
{
    for (int nCount = 0; nCount < TIMER_MAX; nCount++)
    {
        // テクスチャの破棄
        if (g_pTextureTimer[nCount] != NULL)
        {
            g_pTextureTimer[nCount]->Release();
            g_pTextureTimer[nCount] = NULL;
        }
    }

    // 頂点バッファの破棄
    if (g_pVtxBuffTimer != NULL)
    {
        g_pVtxBuffTimer->Release();
        g_pVtxBuffTimer = NULL;
    }
}

//*********************************************
// タイマー画面の更新処理
//*********************************************
void UpdateTimer(void)
{
    VERTEX_2D* pVtx;  // Пойнтер на вершины
    static float timeElapsed = 100.0f; // Начальное значение времени (99)

    // Скорость таймера
    const float timeSpeed = 0.012f;

    // Обновление времени
    timeElapsed -= timeSpeed;
    if (timeElapsed < 0.0f) {
        timeElapsed = 0.0f; // Время не должно быть меньше 0
    }

    // Преобразуем время в целое число
    int timeInt = static_cast<int>(timeElapsed);

    // Разбиваем время на десятки и единицы
    int timeTens = (timeInt / 10) % 10; // Цифра десятков
    int timeOnes = timeInt % 10;        // Цифра единиц

    // Локируем буфер вершин
    g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

    // Устанавливаем текстурные координаты для десятков
    pVtx[4].tex = D3DXVECTOR2(timeTens * 0.1f, 0.0f);
    pVtx[5].tex = D3DXVECTOR2(timeTens * 0.1f + 0.1f, 0.0f);
    pVtx[6].tex = D3DXVECTOR2(timeTens * 0.1f, 1.0f);
    pVtx[7].tex = D3DXVECTOR2(timeTens * 0.1f + 0.1f, 1.0f);

    // Устанавливаем текстурные координаты для единиц
    pVtx[8].tex = D3DXVECTOR2(timeOnes * 0.1f, 0.0f);
    pVtx[9].tex = D3DXVECTOR2(timeOnes * 0.1f + 0.1f, 0.0f);
    pVtx[10].tex = D3DXVECTOR2(timeOnes * 0.1f, 1.0f);
    pVtx[11].tex = D3DXVECTOR2(timeOnes * 0.1f + 0.1f, 1.0f);

	/*AddScore(1);*/
    // Разблокируем буфер вершин
    g_pVtxBuffTimer->Unlock();

    // Если время истекло, заканчиваем игру
    if (timeElapsed <= 0.0f) {
        
        FADE fade = GetFade(); //sato
        if (fade == FADE_NONE)
        {//遷移中でない sato
            SetFade(MODE_RESULT, 2.0f);
        }
        
    }

	// 勝ったらスコアを保存
    //if (isGameWon) {
    //    int remainingTimeInSeconds = static_cast<int>(timeElapsed);
    //    int score = remainingTimeInSeconds * 10; // 1 sec = 10 points
    //    SaveScore(score);
    //}
}



//*********************************************
// タイマー画面の描画処理
//*********************************************
void DrawTimer(void)
{
    // デバイスへのポインタ
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ALPHAREF, 180);
    pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

    pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));
    pDevice->SetFVF(FVF_VERTEX_2D);

    for (int nCount = 0; nCount < TIMER_MAX; nCount++)
    {
        pDevice->SetTexture(0, g_pTextureTimer[nCount]);
        pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount, 2);
    }

    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
