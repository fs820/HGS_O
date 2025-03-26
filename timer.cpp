#include "timer.h"
#include "fade.h"
#include "sound.h"
#include <math.h>
#include "input.h"
#include "score.h"

// ƒOƒ[ƒoƒ‹•Ï”éŒ¾
LPDIRECT3DTEXTURE9 g_pTextureTimer[TIMER_MAX] = {};    // ƒeƒNƒXƒ`ƒƒ‚Ö‚Ìƒ|ƒCƒ“ƒ^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;        // ’¸“_ƒoƒbƒtƒ@‚Ö‚Ìƒ|ƒCƒ“ƒ^
TIMER g_timer[TIMER_MAX];                               // ƒ^ƒCƒ}[‚Ìî•ñ

//*********************************************
// ƒ^ƒCƒ}[‰æ–Ê‚Ì‰Šú‰»ˆ—
//*********************************************
void InitTimer(void)
{
    VERTEX_2D* pVtx;

    LPDIRECT3DDEVICE9 pDevice;

    // ƒfƒoƒCƒX‚Ìæ“¾
    pDevice = GetDevice();

    // ’¸“_ƒoƒbƒtƒ@‚Ì¶¬
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIMER_MAX, // •K—v‚È’¸“_”
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_2D,
        D3DPOOL_DEFAULT,
        &g_pVtxBuffTimer,
        NULL);

    // ’¸“_ƒoƒbƒtƒ@‚ğƒƒbƒN‚µA’¸“_î•ñ‚Ö‚Ìƒ|ƒCƒ“ƒ^‚ğæ“¾
    g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

    for (int nCount = 0; nCount < TIMER_MAX; nCount++)
    {
        // ƒ^ƒCƒ}[ŠÖ˜A‚ÌƒeƒNƒXƒ`ƒƒ‚Ì“Ç‚İ‚İ
        D3DXCreateTextureFromFileEx(pDevice,
            TIMER_TEXTURES[nCount],
            D3DX_DEFAULT,              // ƒeƒNƒXƒ`ƒƒ‚Ì•iD3DX_DEFAULT‚È‚ç©“®’²®j
            D3DX_DEFAULT,              // ƒeƒNƒXƒ`ƒƒ‚Ì‚‚³iD3DX_DEFAULT‚È‚ç©“®’²®j
            D3DX_DEFAULT,              // ƒ~ƒbƒvƒ}ƒbƒvƒŒƒxƒ‹iD3DX_DEFAULT‚Å©“®İ’èj
            0,                         // g—p‚µ‚È‚¢ê‡‚Í0i“®“IƒeƒNƒXƒ`ƒƒ‚È‚çD3DUSAGE_DYNAMICj
            D3DFMT_A8R8G8B8,           // ƒtƒH[ƒ}ƒbƒgiD3DFMT_A8R8G8B8 ‚È‚Çj
            D3DPOOL_DEFAULT,           // ƒƒ‚ƒŠƒv[ƒ‹i’Êí‚Í D3DPOOL_MANAGEDj
            D3DX_FILTER_BOX,           // ‰æ‘œ‚ÌŠgkƒtƒBƒ‹ƒ^iD3DX_FILTER_LINEAR ‚È‚Çj
            D3DX_FILTER_BOX,           // ƒ~ƒbƒvƒ}ƒbƒv‚ÌƒtƒBƒ‹ƒ^
            0,                         // ƒJƒ‰[ƒL[i“§–¾‚É‚µ‚½‚¢Fj
            NULL,                      // `D3DXIMAGE_INFO`i‰æ‘œî•ñ‚ğæ“¾‚·‚éê‡j
            NULL,                      // ƒpƒŒƒbƒgƒf[ƒ^iƒpƒŒƒbƒg‚È‚µ‚È‚çNULLj
            &g_pTextureTimer[nCount]);

        // ƒ^ƒCƒ}[‚ÌˆÊ’u‚ÆƒTƒCƒYİ’è
        

        switch (nCount)
        {
        case TIMER_LABEL:		// ¯‹ó
            g_timer[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.1f, 0.0f);  // ˆÊ’u‚Ìİ’è
            g_timer[nCount].fWidth = SCREEN_WIDTH * 0.05f;                                       // •‚Ìİ’è
            g_timer[nCount].fHeight = SCREEN_HEIGHT * 0.025f;                                      // ‚‚³‚Ìİ’è
            break;

        case TIMER_DIGITS:		// ¯‹ó
            g_timer[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.87f, SCREEN_HEIGHT * 0.1f, 0.0f);  // ˆÊ’u‚Ìİ’è
            g_timer[nCount].fWidth = SCREEN_WIDTH * 0.015f;                                       // •‚Ìİ’è
            g_timer[nCount].fHeight = SCREEN_HEIGHT * 0.025f;                                      // ‚‚³‚Ìİ’è
            break;

        case TIMER_DIGITS_TWO:		// ¯‹ó
            g_timer[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.1f, 0.0f);  // ˆÊ’u‚Ìİ’è
            g_timer[nCount].fWidth = SCREEN_WIDTH * 0.015f;                                       // •‚Ìİ’è
            g_timer[nCount].fHeight = SCREEN_HEIGHT * 0.025f;                                      // ‚‚³‚Ìİ’è
            break;

        }
        // ’¸“_À•W‚Ìİ’è
        pVtx[0 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(-g_timer[nCount].fWidth, -g_timer[nCount].fHeight, 0.0f);
        pVtx[1 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(g_timer[nCount].fWidth, -g_timer[nCount].fHeight, 0.0f);
        pVtx[2 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(-g_timer[nCount].fWidth, g_timer[nCount].fHeight, 0.0f);
        pVtx[3 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(g_timer[nCount].fWidth, g_timer[nCount].fHeight, 0.0f);

        // rhw‚Ìİ’è
        pVtx[0 + (4 * nCount)].rhw = 1.0f;
        pVtx[1 + (4 * nCount)].rhw = 1.0f;
        pVtx[2 + (4 * nCount)].rhw = 1.0f;
        pVtx[3 + (4 * nCount)].rhw = 1.0f;

        // ’¸“_ƒJƒ‰[‚Ìİ’è
        pVtx[0 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        pVtx[1 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        pVtx[2 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        pVtx[3 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

        // ƒeƒNƒXƒ`ƒƒÀ•W‚Ìİ’è
        pVtx[0 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 0.0f);
        pVtx[1 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 0.0f);
        pVtx[2 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 1.0f);
        pVtx[3 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 1.0f);
    }

    // ’¸“_ƒoƒbƒtƒ@‚ğƒAƒ“ƒƒbƒN‚·‚é
    g_pVtxBuffTimer->Unlock();
}

//*********************************************
// ƒ^ƒCƒ}[‰æ–Ê‚ÌI—¹ˆ—
//*********************************************
void UninitTimer(void)
{
    for (int nCount = 0; nCount < TIMER_MAX; nCount++)
    {
        // ƒeƒNƒXƒ`ƒƒ‚Ì”jŠü
        if (g_pTextureTimer[nCount] != NULL)
        {
            g_pTextureTimer[nCount]->Release();
            g_pTextureTimer[nCount] = NULL;
        }
    }

    // ’¸“_ƒoƒbƒtƒ@‚Ì”jŠü
    if (g_pVtxBuffTimer != NULL)
    {
        g_pVtxBuffTimer->Release();
        g_pVtxBuffTimer = NULL;
    }
}

//*********************************************
// ƒ^ƒCƒ}[‰æ–Ê‚ÌXVˆ—
//*********************************************
void UpdateTimer(void)
{
    VERTEX_2D* pVtx;  // „P„€„z„~„„„u„‚ „~„p „r„u„‚„Š„y„~„
    static float timeElapsed = 100.0f; // „N„p„‰„p„|„„~„€„u „x„~„p„‰„u„~„y„u „r„‚„u„}„u„~„y (99)

    // „R„{„€„‚„€„ƒ„„„ „„„p„z„}„u„‚„p
    const float timeSpeed = 0.012f;

    // „O„q„~„€„r„|„u„~„y„u „r„‚„u„}„u„~„y
    timeElapsed -= timeSpeed;
    if (timeElapsed < 0.0f) {
        timeElapsed = 0.0f; // „B„‚„u„}„‘ „~„u „t„€„|„w„~„€ „q„„„„ „}„u„~„„Š„u 0
    }

    // „P„‚„u„€„q„‚„p„x„…„u„} „r„‚„u„}„‘ „r „ˆ„u„|„€„u „‰„y„ƒ„|„€
    int timeInt = static_cast<int>(timeElapsed);

    // „Q„p„x„q„y„r„p„u„} „r„‚„u„}„‘ „~„p „t„u„ƒ„‘„„„{„y „y „u„t„y„~„y„ˆ„
    int timeTens = (timeInt / 10) % 10; // „W„y„†„‚„p „t„u„ƒ„‘„„„{„€„r
    int timeOnes = timeInt % 10;        // „W„y„†„‚„p „u„t„y„~„y„ˆ

    // „L„€„{„y„‚„…„u„} „q„…„†„u„‚ „r„u„‚„Š„y„~
    g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

    // „T„ƒ„„„p„~„p„r„|„y„r„p„u„} „„„u„{„ƒ„„„…„‚„~„„u „{„€„€„‚„t„y„~„p„„„ „t„|„‘ „t„u„ƒ„‘„„„{„€„r
    pVtx[4].tex = D3DXVECTOR2(timeTens * 0.1f, 0.0f);
    pVtx[5].tex = D3DXVECTOR2(timeTens * 0.1f + 0.1f, 0.0f);
    pVtx[6].tex = D3DXVECTOR2(timeTens * 0.1f, 1.0f);
    pVtx[7].tex = D3DXVECTOR2(timeTens * 0.1f + 0.1f, 1.0f);

    // „T„ƒ„„„p„~„p„r„|„y„r„p„u„} „„„u„{„ƒ„„„…„‚„~„„u „{„€„€„‚„t„y„~„p„„„ „t„|„‘ „u„t„y„~„y„ˆ
    pVtx[8].tex = D3DXVECTOR2(timeOnes * 0.1f, 0.0f);
    pVtx[9].tex = D3DXVECTOR2(timeOnes * 0.1f + 0.1f, 0.0f);
    pVtx[10].tex = D3DXVECTOR2(timeOnes * 0.1f, 1.0f);
    pVtx[11].tex = D3DXVECTOR2(timeOnes * 0.1f + 0.1f, 1.0f);

	/*AddScore(1);*/
    // „Q„p„x„q„|„€„{„y„‚„…„u„} „q„…„†„u„‚ „r„u„‚„Š„y„~
    g_pVtxBuffTimer->Unlock();

    // „E„ƒ„|„y „r„‚„u„}„‘ „y„ƒ„„„u„{„|„€, „x„p„{„p„~„‰„y„r„p„u„} „y„s„‚„…
    if (timeElapsed <= 0.0f) {
        
        FADE fade = GetFade(); //sato
        if (fade == FADE_NONE)
        {//‘JˆÚ’†‚Å‚È‚¢ sato
            SetFade(MODE_RESULT, 2.0f);
        }
        
    }

	// Ÿ‚Á‚½‚çƒXƒRƒA‚ğ•Û‘¶
    //if (isGameWon) {
    //    int remainingTimeInSeconds = static_cast<int>(timeElapsed);
    //    int score = remainingTimeInSeconds * 10; // 1 sec = 10 points
    //    SaveScore(score);
    //}
}



//*********************************************
// ƒ^ƒCƒ}[‰æ–Ê‚Ì•`‰æˆ—
//*********************************************
void DrawTimer(void)
{
    // ƒfƒoƒCƒX‚Ö‚Ìƒ|ƒCƒ“ƒ^
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
