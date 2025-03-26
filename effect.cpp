//---------------------------------------
//
//�G�t�F�N�g�\������[effect.cpp]
//Author fuma sato
//
//---------------------------------------

#include"effect.h"
#include"ball.h"
#include"mesh.h"

//�e�\����
typedef struct
{
	D3DXVECTOR2 pos;//�ʒu
	D3DXVECTOR2 move;
	D3DXCOLOR col;
	int nLife;//����
	EFFECT_TYPE Type;
	bool bUse;//�g�p���Ă��邩�ǂ���
}Effect;

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//�o�b�t�@�̃|�C���^
Effect g_aEffect[MAX_EFFECT];//�e�̏��
int g_nLifeDef[MAX_EFFECT] = { 0 };

//-----------------
//�e�̏���������
//-----------------
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾
	pDevice = GetDevice();

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_aEffect[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_aEffect[i].move = D3DXVECTOR2(0.0f, 0.0f);
		g_aEffect[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect[i].nLife = 0;
		g_aEffect[i].Type = EFFECT_TYPE_NORMAL;
		g_aEffect[i].bUse = false;//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		EFFECT_TEX,
		&g_pTextureEffect
	);


	SetVertex2D
	(
		&g_pVtxBuffEffect,
		0, MAX_EFFECT,
		1, 1,
		D3DXVECTOR2(0.0f, 0.0f),0.0f,
		EFFECT_SIZE_DEF, EFFECT_SIZE_DEF,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		EFFECT_SIZE_DEF, EFFECT_SIZE_DEF
	);
}

//----------------
//�e�̏I������
//----------------
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//----------------
//�e�̍X�V����
//----------------
void UpdateEffect(void)
{
	VERTEX_2D* pVtx;
	static D3DXVECTOR2 Oldpos[MAX_EFFECT];

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_aEffect[i].bUse == true)
		{//�e���g�p����Ă���

			Oldpos[i] = g_aEffect[i].pos;

			g_aEffect[i].pos.x += g_aEffect[i].move.x;
			g_aEffect[i].pos.y += g_aEffect[i].move.y;

			SetVertex2D
			(
				&g_pVtxBuffEffect,
				i, 1,
				1, 1,
				g_aEffect[i].pos,0.0f,
				EFFECT_SIZE_DEF * ((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i]), EFFECT_SIZE_DEF * ((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i]),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				EFFECT_SIZE_DEF * ((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i]), EFFECT_SIZE_DEF * ((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i])
			);

			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += i * VT_MAX;//�|���S��1���i�߂�
			BYTE alpha = (BYTE)(((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i]) * 255.0f);
			pVtx[0].col = (pVtx[0].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[1].col = (pVtx[1].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[2].col = (pVtx[2].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[3].col = (pVtx[3].col & 0x00FFFFFF) | (alpha << 24);

			g_pVtxBuffEffect->Unlock();//�o�b�t�@�̃A�����b�N

			g_aEffect[i].nLife--;

			if (g_aEffect[i].nLife <= 0)
			{
				g_aEffect[i].bUse = false;
			}
		}
	}
}

//----------------
//�e�̕`�揈��
//----------------
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	int nCntEffect;
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse)
		{
			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			//�|���S���̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				nCntEffect * VT_MAX,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}

	//�ʏ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//-------------------
//���ʏ�e
//-------------------
void SetEffect(D3DXVECTOR2 pos, D3DXVECTOR2 move, D3DXCOLOR col, int nLife, EFFECT_TYPE Type)
{
	VERTEX_3D* pVtx;

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_aEffect[i].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aEffect[i].pos = pos;
			g_aEffect[i].move = move;
			g_aEffect[i].col = col;

			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

			//���_���W�ݒ�
			pVtx += i * VT_MAX;//�|���S��1���i�߂�
			pVtx[0].col = g_aEffect[i].col;
			pVtx[1].col = g_aEffect[i].col;
			pVtx[2].col = g_aEffect[i].col;
			pVtx[3].col = g_aEffect[i].col;

			g_pVtxBuffEffect->Unlock();//�o�b�t�@�̃A�����b�N

			g_aEffect[i].nLife = nLife;
			g_nLifeDef[i] = g_aEffect[i].nLife;
			g_aEffect[i].Type = Type;
			g_aEffect[i].bUse = true;

			break;
		}
	}
}