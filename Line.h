//---------------------------------------
//
//ボール処理の定義・宣言[Line.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _LINE_H_
#define _LINE_H_

#include"main.h"

#define LINE_TEX "data\\TEXTURE\\Generated Platform.png"
#define LINE_MAX (128)
#define LINE_WIDTH (300.0f)
#define LINE_HEIGHT (50.0f)

#define LINE_ROT_SPEED (0.1f)

typedef struct
{
	D3DXVECTOR2 pos;
	float fAngle;
	bool bUse;
	bool bHold;
}Line;

void InitLine(void);//ポリゴンの初期化処理
void UninitLine(void);//ポリゴンの終了処理
void UpdateLine(void);//ポリゴンの更新処理
void DrawLine(void);//ポリゴンの描画処理
void SetLine(int HoldIdx, D3DXVECTOR2 pos, float fAngle);
void HoldLine(void);

void ReflectionLine(D3DXVECTOR2& pos, D3DXVECTOR2& posOld, D3DXVECTOR2& move, float fWidth);
#endif //_BALL_H_