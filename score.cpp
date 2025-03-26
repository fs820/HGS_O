//---------------------------------------
//
//ƒXƒRƒAˆ—[score.cpp]
//Author fuma sato
//
//---------------------------------------

#include "score.h"
#include "fade.h"
#include "sound.h"
#include <math.h>
#include "input.h"

#include <fstream>

// „C„|„€„q„p„|„„~„p„‘ „„u„‚„u„}„u„~„~„p„‘ „t„|„‘ „€„q„‹„u„s„€ „ƒ„‰„u„„„p
int totalScore = 0;



// ƒOƒ[ƒoƒ‹•Ï”éŒ¾
LPDIRECT3DTEXTURE9 g_pTextureScore[SCORE_UI_MAX] = {};	// ƒeƒNƒXƒ`ƒƒ‚Ö‚Ìƒ|ƒCƒ“ƒ^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			// ’¸“_ƒoƒbƒtƒ@‚Ö‚Ìƒ|ƒCƒ“ƒ^
THANKYOU g_score[SCORE_UI_MAX];							// ƒXƒRƒA‚Ìî•ñ

//*********************************************
// ƒXƒRƒA‰æ–Ê‚Ì‰Šú‰»ˆ—
//*********************************************
void InitScore(void)
{
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	// ƒfƒoƒCƒX‚Ìæ“¾
	pDevice = GetDevice();

	// ’¸“_ƒoƒbƒtƒ@‚Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SCORE_UI_MAX, // •K—v‚È’¸“_”
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_DEFAULT,
		&g_pVtxBuffScore,
		NULL);

	// ’¸“_ƒoƒbƒtƒ@‚ğƒƒbƒN‚µA’¸“_î•ñ‚Ö‚Ìƒ|ƒCƒ“ƒ^‚ğæ“¾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < SCORE_UI_MAX; nCount++)
	{
		// ƒXƒRƒAƒeƒNƒXƒ`ƒƒ‚Ì“Ç‚İ‚İ
		D3DXCreateTextureFromFileEx(pDevice,
			SCORE_TEXTURES[nCount],
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
			&g_pTextureScore[nCount]);

		switch (nCount)
		{
		case SCORE_UI:		// ƒXƒRƒA”wŒi
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.81f, SCREEN_HEIGHT * 0.18f, 0.0f);	// ˆÊ’u‚Ìİ’è
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.06f;										// •‚Ìİ’è
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// ‚‚³‚Ìİ’è
			break;

		case SCORE_UI_ONE:		// ”ši1j
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.89f, SCREEN_HEIGHT * 0.18f, 0.0f);	// ˆÊ’u‚Ìİ’è
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.015f;										// •‚Ìİ’è
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// ‚‚³‚Ìİ’è
			break;

		case SCORE_UI_TWO:		// ”ši2j
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.92f, SCREEN_HEIGHT * 0.18f, 0.0f);	// ˆÊ’u‚Ìİ’è
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.015f;										// •‚Ìİ’è
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// ‚‚³‚Ìİ’è
			break;

		case SCORE_UI_THREE:		// ”ši3j
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.95f, SCREEN_HEIGHT * 0.18f, 0.0f);	// ˆÊ’u‚Ìİ’è
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.015f;										// •‚Ìİ’è
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// ‚‚³‚Ìİ’è
			break;
		}

		// ’¸“_À•W‚Ìİ’è
		pVtx[0 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(-g_score[nCount].fWidth, -g_score[nCount].fHeight, 0.0f);
		pVtx[1 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(g_score[nCount].fWidth, -g_score[nCount].fHeight, 0.0f);
		pVtx[2 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(-g_score[nCount].fWidth, g_score[nCount].fHeight, 0.0f);
		pVtx[3 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(g_score[nCount].fWidth, g_score[nCount].fHeight, 0.0f);

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
	g_pVtxBuffScore->Unlock();
}

//*********************************************
// ƒXƒRƒA‰æ–Ê‚ÌI—¹ˆ—
//*********************************************
void UninitScore(void)
{
	for (int nCount = 0; nCount < SCORE_UI_MAX; nCount++)
	{
		// ’¸“_ƒoƒbƒtƒ@‚Ì”jŠü
		if (g_pTextureScore[nCount] != NULL)
		{
			g_pTextureScore[nCount]->Release();
			g_pTextureScore[nCount] = NULL;
		}
	}

	// ”wŒiƒeƒNƒXƒ`ƒƒ‚Ì”jŠü
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

// „U„…„~„{„ˆ„y„‘ „t„|„‘ „€„q„~„€„r„|„u„~„y„‘ „€„„„€„q„‚„p„w„p„u„}„€„s„€ „ƒ„‰„u„„„p
void UpdateScore(int score)  // „S„u„„u„‚„ „„u„‚„u„t„p„u„} „„p„‚„p„}„u„„„‚ `score` „r „†„…„~„{„ˆ„y„
{
	VERTEX_2D* pVtx;  // „P„€„z„~„„„u„‚ „~„p „r„u„‚„Š„y„~„

	// „Q„p„x„q„y„r„p„u„} „ƒ„‰„u„„ „~„p „t„u„ƒ„‘„„„{„y, „ƒ„€„„„~„y „y „u„t„y„~„y„ˆ„
	int scoreHundreds = (score / 100) % 10; // „W„y„†„‚„p „ƒ„€„„„u„~
	int scoreTens = (score / 10) % 10;      // „W„y„†„‚„p „t„u„ƒ„‘„„„{„€„r
	int scoreOnes = score % 10;             // „W„y„†„‚„p „u„t„y„~„y„ˆ

	// „L„€„{„y„‚„…„u„} „q„…„†„u„‚ „r„u„‚„Š„y„~
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// „T„ƒ„„„p„~„p„r„|„y„r„p„u„} „„„u„{„ƒ„„„…„‚„~„„u „{„€„€„‚„t„y„~„p„„„ „t„|„‘ „ƒ„€„„„u„~
	pVtx[4].tex = D3DXVECTOR2(scoreHundreds * 0.1f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(scoreHundreds * 0.1f + 0.1f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(scoreHundreds * 0.1f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(scoreHundreds * 0.1f + 0.1f, 1.0f);

	// „T„ƒ„„„p„~„p„r„|„y„r„p„u„} „„„u„{„ƒ„„„…„‚„~„„u „{„€„€„‚„t„y„~„p„„„ „t„|„‘ „t„u„ƒ„‘„„„{„€„r
	pVtx[8].tex = D3DXVECTOR2(scoreTens * 0.1f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(scoreTens * 0.1f + 0.1f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(scoreTens * 0.1f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(scoreTens * 0.1f + 0.1f, 1.0f);

	// „T„ƒ„„„p„~„p„r„|„y„r„p„u„} „„„u„{„ƒ„„„…„‚„~„„u „{„€„€„‚„t„y„~„p„„„ „t„|„‘ „u„t„y„~„y„ˆ
	pVtx[12].tex = D3DXVECTOR2(scoreOnes * 0.1f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(scoreOnes * 0.1f + 0.1f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(scoreOnes * 0.1f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(scoreOnes * 0.1f + 0.1f, 1.0f);

	// „Q„p„x„q„|„€„{„y„‚„…„u„} „q„…„†„u„‚ „r„u„‚„Š„y„~
	g_pVtxBuffScore->Unlock();
}



void DrawScore(void)
{
	// ƒfƒoƒCƒX‚Ö‚Ìƒ|ƒCƒ“ƒ^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 180);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ’¸“_ƒoƒbƒtƒ@‚ğƒZƒbƒg
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ŠeƒXƒRƒAUI‚ğ•`‰æ
	for (int nCount = 0; nCount < SCORE_UI_MAX; nCount++)
	{
		pDevice->SetTexture(0, g_pTextureScore[nCount]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount, 2);
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}


//--------------------
//Œ…•ªŠ„ˆ—
//--------------------
int Digit(int nData, int nDigit)
{
	int aNumber[SCORE_MAX - 1] = { 0 };//•ªŠ„—p”z—ñ
	int nData2 = 1;//ŒvZ—p

	for (int i = SCORE_MAX - 2; i >= 0; i--)
	{//Œ…”•ª
		if (i == 0)
		{
			aNumber[i] = nData / nData2;//ÅãˆÊ‚ÌŒ…
		}
		aNumber[i] = nData % (nData2 * DIGIT) / nData2;//ŒvZ
		nData2 *= DIGIT;//Œ…ˆø‚«ã‚°
	}

	return aNumber[nDigit];//w’è‚ÌŒ…‚ğ•Ô‚·
}

// „U„…„~„{„ˆ„y„‘ „t„|„‘ „t„€„q„p„r„|„u„~„y„‘ „€„‰„{„€„r
void AddScore(int scoreToAdd) {
	totalScore += scoreToAdd;
	UpdateScore(totalScore);
}

// „U„…„~„{„ˆ„y„‘ „t„|„‘ „ƒ„€„‡„‚„p„~„u„~„y„‘ „ƒ„‰„u„„„p „r „†„p„z„| („u„ƒ„|„y „~„…„w„~„€)
void SaveScore(int score) {
	const char* fileName = "score.txt"; // „I„}„‘ „†„p„z„|„p „t„|„‘ „ƒ„€„‡„‚„p„~„u„~„y„‘

	// „O„„„{„‚„„r„p„u„} „†„p„z„| „t„|„‘ „x„p„„y„ƒ„y
	std::ofstream outFile(fileName, std::ios::app);  // „O„„„{„‚„„r„p„u„} „r „‚„u„w„y„}„u „t„€„q„p„r„|„u„~„y„‘ (append)
	if (outFile.is_open()) {
		outFile << "Score: " << score << std::endl;
		outFile.close();
	}
}