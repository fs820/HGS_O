//---------------------------------------
//
//�x�N�g���̓����蔻�菈���̒�`�E�錾[vectorcollision.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _VECTERCOLLISION_H_
#define _VECTERCOLLISION_H_
#include "main.h"

//------------------
//�����߂�
//------------------
void VectorCollision(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos);

//------------------
//�^�U
//------------------
bool __stdcall VectorTrigger(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos);

//------------------
//����
//------------------
void VectorReflection(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, D3DXVECTOR2& Move, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos);

//----------
//�����蔻��
//----------
bool VectorInside(D3DXVECTOR2& Movingpos, float MovingWidth, D3DXVECTOR2* pPos);
#endif // _VECTERCOLLISION_H_