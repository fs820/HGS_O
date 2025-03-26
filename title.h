#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

// サンキュー背景の列挙
typedef enum
{
	BACKGROUND = 0,
	MOVING_BACKGROUND,
	TITLE_BUTTON,
	TITLE_MAX
}THANKYOUTYPE;

// 列挙型にテクスチャ名を代入
static const char* THANKYOU_BACKGROUND[TITLE_MAX] =
{
	"data\\TEXTURE\\Bg new.png",		// Spaceship Background Move
	"data\\TEXTURE\\buildings.png",		// Girl Background
	"data\\TEXTURE\\TAP TO START.png",		// Logo
};

// サンキュー情報
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	float fWidth;			// 幅
	float fHeight;			// 高さ
}THANKYOU;

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
#endif