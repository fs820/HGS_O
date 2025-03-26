//---------------------------------------
//
//ボール処理の定義・宣言[block.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"main.h"

#define BLOCK_TEX "data\\TEXTURE\\Block.png"
#define BLOCK_MAX (128)
#define BLOCK_WIDTH (100.0f)
#define BLOCK_HEIGHT (100.0f)

typedef struct
{
	D3DXVECTOR2 pos;
	bool bUse;
}Block;

void InitBlock(void);//ポリゴンの初期化処理
void UninitBlock(void);//ポリゴンの終了処理
void UpdateBlock(void);//ポリゴンの更新処理
void DrawBlock(void);//ポリゴンの描画処理
void SetBlock(D3DXVECTOR2 pos);

void ReflectionBlock(D3DXVECTOR2& pos, D3DXVECTOR2& posOld, D3DXVECTOR2& move, float fWidth);
#endif //_BALL_H_