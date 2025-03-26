//---------------------------------------
//
//ボール処理の定義・宣言[Brick.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _BRICK_H_
#define _BRICK_H_

#include"main.h"

#define BRICK_TEX "data\\TEXTURE\\Brick.png"
#define BRICK_MAX (128)
#define BRICK_WIDTH (184.0f)
#define BRICK_HEIGHT (92.0f)

typedef struct
{
	D3DXVECTOR2 pos;
	float fAngle;
	bool bUse;
}Brick;

void InitBrick(void);//ポリゴンの初期化処理
void UninitBrick(void);//ポリゴンの終了処理
void UpdateBrick(void);//ポリゴンの更新処理
void DrawBrick(void);//ポリゴンの描画処理
void SetBrick(D3DXVECTOR2 pos, float fAngle);

void ReflectionBrick(D3DXVECTOR2& pos, D3DXVECTOR2& posOld, D3DXVECTOR2& move, float fWidth);
#endif //_BALL_H_