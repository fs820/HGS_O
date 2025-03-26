//------------------------------------------
//
//�t�F�[�h����[fade.cpp]
//Author fuma sato
//
//------------------------------------------
#include"fade.h"
#include "mesh.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBack = NULL;//�o�b�t�@�̃|�C���^
//-------------
//����������
//-------------
void InitBack(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�o�b�t�@�[�̐ݒ�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_UI) * VT_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_UI,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBack,
		NULL
	);

	VERTEX_UI* pVtx;
	g_pVtxBuffBack->Lock(0, 0, (void**)&pVtx, 0);//�v���C���[�o�b�t�@�̃��b�N

	//���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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

	g_pVtxBuffBack->Unlock();//�v���C���[�o�b�t�@�̃A�����b�N
}

//-----------------
//�I������
//-----------------
void UninitBack(void)
{
	//���_�o�b�t�@�̔j��
	SAFE_RELEASE(g_pVtxBuffBack);
}

//-----------------
//�X�V����
//-----------------
void UpdateBack(void)
{

}

//----------------
//�`�揈��
//----------------
void DrawBack(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@
	pDevice->SetStreamSource(0, g_pVtxBuffBack, 0, sizeof(VERTEX_UI));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_UI);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�w�i�̕`��
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,//�^�C�v
		0,//�n�܂�̔ԍ�
		2//�|���S���̌�
	);
}