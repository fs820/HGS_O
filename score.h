//---------------------------------------
//
//スコア処理の定義・宣言[score.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"

#define SCORE_MAX (5)//桁数
#define U_MAX_S (11)//テクスチャ数(横)
#define V_MAX_S (1)//テクスチャ数(縦)
#define SCORE_WIDTH (160.0f)//サイズ
#define SCORE_HEIGHT (64.0f)//サイズ
#define DIGIT (10)//進数

extern int totalScore;//合計スコア

// サンキュー背景の列挙
typedef enum
{
	SCORE_UI = 0,
	SCORE_UI_ONE,
	SCORE_UI_TWO,
	SCORE_UI_THREE,
	SCORE_UI_MAX
}SCORETYPE;

// 列挙型にテクスチャ名を代入
static const char* SCORE_TEXTURES[SCORE_UI_MAX] =
{
	"data\\TEXTURE\\Score.png",		
	"data\\TEXTURE\\Numbers.png",		
	"data\\TEXTURE\\Numbers.png",
	"data\\TEXTURE\\Numbers.png",		
};

// サンキュー情報
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	float fWidth;			// 幅
	float fHeight;			// 高さ
}THANKYOU;

void InitScore(void);
void UninitScore(void);
void UpdateScore(int score);
void DrawScore(void);
int Digit(int nData, int nDigit);//分割処理
void AddScore(int scoreToAdd);
void SaveScore(int score);

#endif _SCORE_H_