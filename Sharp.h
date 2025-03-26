//---------------------------------------
//
//�{�[�������̒�`�E�錾[Sharp.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _SHARP_H_
#define _SHARP_H_

#include"main.h"

#define BRICK_TEX "data\\TEXTURE\\Sharp.png"
#define BRICK_MAX (128)
#define BRICK_WIDTH (184.0f)
#define BRICK_HEIGHT (92.0f)

typedef struct
{
	D3DXVECTOR2 pos;
	float fAngle;
	bool bUse;
}Sharp;

void InitSharp(void);//�|���S���̏���������
void UninitSharp(void);//�|���S���̏I������
void UpdateSharp(void);//�|���S���̍X�V����
void DrawSharp(void);//�|���S���̕`�揈��
void SetSharp(D3DXVECTOR2 pos, float fAngle);

void ReflectionSharp(D3DXVECTOR2& pos, D3DXVECTOR2& posOld, D3DXVECTOR2& move, float fWidth);
#endif //_BALL_H_