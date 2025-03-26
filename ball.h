//---------------------------------------
//
//ボール処理の定義・宣言[ball.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _BALL_H_
#define _BALL_H_

#include"main.h"

#define BALL_TEX "data\\TEXTURE\\Ball.png"
#define BALL_MAX (1)
#define BALL_WIDTH (100.0f)
#define BALL_HEIGHT (100.0f)
#define BALL_SPEED (10.0f)

typedef struct
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 posOld;
	D3DXVECTOR2 move;
	D3DXVECTOR2 dir;
	bool bUse;
}Ball;

void InitBall(void);//ポリゴンの初期化処理
void UninitBall(void);//ポリゴンの終了処理
void UpdateBall(void);//ポリゴンの更新処理
void DrawBall(void);//ポリゴンの描画処理
void SetBall(D3DXVECTOR2 pos, D3DXVECTOR2 dir);
#endif //_BALL_H_