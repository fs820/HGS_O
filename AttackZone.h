//---------------------------------------
//
//�A�^�b�N�]�[�������̒�`�E�錾[AttackZone.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _ATTACK_ZONE_H_
#define _ATTACK_ZONE_H_
#include "main.h"

#define ATTACK_ZONE_TEX   "data\\texture\\base\\shadow000.jpg"
#define ATTACK_ZONE_MAX (4)

//�e���g���[�\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	float fRadius;			// ���a
	bool bLess;             // ���Z
	bool bUse;				// �g�p
	D3DXCOLOR col;          // ����
	D3DXMATRIX mtxWorld;    // �}�g���b�N�X
}AttackZone;

void InitAttackZone(void);   //����������
void UninitAttackZone(void); //�I������
void DrawAttackZone(void);   //�`�揈��
int SetAttackZone(D3DXVECTOR3 pos, float fRadius, D3DXCOLOR col, bool Less); //�ݒ菈��
void EndAttackZone(int nIdx);
#endif //_TERRITORY_H_