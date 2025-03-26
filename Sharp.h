//---------------------------------------
//
//ボール処理の定義・宣言[Sharp.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _SHARP_H_
#define _SHARP_H_

#include"main.h"

#define SHARP_TEX "data\\TEXTURE\\Sharp.png"
#define SHARP_MAX (128)
#define SHARP_WIDTH (234.0f)
#define SHARP_HEIGHT (77.0f)

typedef struct
{
	D3DXVECTOR2 pos;
	float fAngle;
	bool bUse;
}Sharp;

void InitSharp(void);//ポリゴンの初期化処理
void UninitSharp(void);//ポリゴンの終了処理
void UpdateSharp(void);//ポリゴンの更新処理
void DrawSharp(void);//ポリゴンの描画処理
int SetSharp(D3DXVECTOR2 pos, float fAngle);

bool HitSharp(D3DXVECTOR2& pos, D3DXVECTOR2& posOld, D3DXVECTOR2& move, float fWidth);
#endif //_BALL_H_