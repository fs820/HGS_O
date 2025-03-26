//------------------------------------------
//
//タイトルの処理の定義・宣言[title.h]
//Author fuma sato
//
//------------------------------------------

#ifndef _TITLE_H_
#define _TITLE_H_

#include"main.h"

#define TEXTURE_ROGO "data\\TEXTURE\\Cursor.png"
#define TEXTURE_ROGOTXT "data\\TEXTURE\\Background.png"
#define TEXTURE_START "data\\TEXTURE\\TAP TO START.png"
#define TEXTURE_SELECT "data\\TEXTURE\\Select.png"

void InitTitle(void);//タイトル初期化処理
void UninitTitle(void);//タイトル終了処理
void UpdateTitle(void);//タイトル更新処理
void DrawTitle(void);//タイトル描画処理

#endif _TITLE_H_
