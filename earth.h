//---------------------------------------
//
//ポリゴン表示処理の定義・宣言[earth.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _EARTH_H_
#define _EARTH_H_

#include"main.h"

#define EARTH_TEX "data\\texture\\sato\\Earth000.png"//テクスチャ
#define EARTH_WIDTH (3000.0f)//幅
#define EARTH_HEIGHT (3000.0f)//高さ

//地球構造体
typedef struct
{
	D3DXMATRIX mtxWorld;//マトリックス
	bool bUse;//使用
}Earth;

void InitEarth(void);//初期化処理
void UninitEarth(void);//終了処理
void UpdateEarth(void);//更新処理
void DrawEarth(void);//描画処理
void SetEarth(void);//設定処理

#endif _EARTH_H_