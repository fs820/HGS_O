//---------------------------------------
//
//�G�t�F�N�g�\������[effect.cpp]
//Author fuma sato
//
//---------------------------------------

#include"effect.h"
#include"ball.h"

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
	VERTEX_2D* pVtx;

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

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[i].pos.x - EFFECT_SIZE_DEF, g_aEffect[i].pos.y + EFFECT_SIZE_DEF, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[i].pos.x + EFFECT_SIZE_DEF, g_aEffect[i].pos.y + EFFECT_SIZE_DEF, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[i].pos.x - EFFECT_SIZE_DEF, g_aEffect[i].pos.y - EFFECT_SIZE_DEF, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[i].pos.x + EFFECT_SIZE_DEF, g_aEffect[i].pos.y - EFFECT_SIZE_DEF, 0.0f);

		//�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += VT_MAX;//�|���S��1���i�߂�
	}
	g_pVtxBuffEffect->Unlock();//�o�b�t�@�̃A�����b�N
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

			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += i * VT_MAX;//�|���S��1���i�߂�
			BYTE alpha = (BYTE)(((float)g_aEffect[i].nLife) / ((float)g_nLifeDef[i]) * 255.0f);
			pVtx[0].col = (pVtx[0].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[1].col = (pVtx[1].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[2].col = (pVtx[2].col & 0x00FFFFFF) | (alpha << 24);
			pVtx[3].col = (pVtx[3].col & 0x00FFFFFF) | (alpha << 24);

			g_pVtxBuffEffect->Unlock();//�o�b�t�@�̃A�����b�N

			Oldpos[i] = g_aEffect[i].pos;

			g_aEffect[i].pos.x += g_aEffect[i].move.x;
			g_aEffect[i].pos.y += g_aEffect[i].move.y;

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
	D3DXMATRIX mtxScale, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�A���t�@�e�X�g�I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//Z�e�X�g�I�t
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
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
	//Z�e�X�g�I��
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	//�A���t�@�e�X�g�I��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
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