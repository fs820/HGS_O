//---------------------------------------
//
//ベクトルの当たり判定処理の定義・宣言[vectorcollision.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _VECTERCOLLISION_H_
#define _VECTERCOLLISION_H_
#include "main.h"

//------------------
//押し戻し
//------------------
void VectorCollision(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos);

//------------------
//真偽
//------------------
bool __stdcall VectorTrigger(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos);

//------------------
//反射
//------------------
void VectorReflection(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, D3DXVECTOR2& Move, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos);

//----------
//当たり判定
//----------
bool VectorInside(D3DXVECTOR2& Movingpos, float MovingWidth, D3DXVECTOR2* pPos);
#endif // _VECTERCOLLISION_H_