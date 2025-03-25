//----------------------------------------
//
//�C���^���N�g����[interact.cpp]
//Author fuma sato
//
//----------------------------------------

#include"interact.h"
#include"mesh.h"
#include"camera.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffInteract = NULL;                   //�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureInteract[INTERACT_TYPE_MAX] = { NULL }; //�e�N�X�`���̃|�C���^
Interact g_Interact;                                                 //����
//----------------------
//�|���S���̏���������
//----------------------
void InitInteract(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_DEFAULT,
		&g_pVtxBuffInteract,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFileEx
	(
		pDevice,
		INTERACT_TEX_KEY,
		D3DX_DEFAULT,              // �e�N�X�`���̕��iD3DX_DEFAULT�Ȃ玩�������j
		D3DX_DEFAULT,              // �e�N�X�`���̍����iD3DX_DEFAULT�Ȃ玩�������j
		D3DX_DEFAULT,              // �~�b�v�}�b�v���x���iD3DX_DEFAULT�Ŏ����ݒ�j
		0,                         // �g�p���Ȃ��ꍇ��0�i���I�e�N�X�`���Ȃ�D3DUSAGE_DYNAMIC�j
		D3DFMT_A8R8G8B8,           // �t�H�[�}�b�g�iD3DFMT_A8R8G8B8 �Ȃǁj
		D3DPOOL_DEFAULT,           // �������v�[���i�ʏ�� D3DPOOL_MANAGED�j
		D3DX_FILTER_BOX,           // �摜�̊g�k�t�B���^�iD3DX_FILTER_LINEAR �Ȃǁj
		D3DX_FILTER_BOX,           // �~�b�v�}�b�v�̃t�B���^
		0,                         // �J���[�L�[�i�����ɂ������F�j
		NULL,                      // `D3DXIMAGE_INFO`�i�摜�����擾����ꍇ�j
		NULL,                      // �p���b�g�f�[�^�i�p���b�g�Ȃ��Ȃ�NULL�j
		&g_pTextureInteract[INTERACT_TYPE_KEY]
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFileEx
	(
		pDevice,
		INTERACT_TEX_JOY,
		D3DX_DEFAULT,              // �e�N�X�`���̕��iD3DX_DEFAULT�Ȃ玩�������j
		D3DX_DEFAULT,              // �e�N�X�`���̍����iD3DX_DEFAULT�Ȃ玩�������j
		D3DX_DEFAULT,              // �~�b�v�}�b�v���x���iD3DX_DEFAULT�Ŏ����ݒ�j
		0,                         // �g�p���Ȃ��ꍇ��0�i���I�e�N�X�`���Ȃ�D3DUSAGE_DYNAMIC�j
		D3DFMT_A8R8G8B8,           // �t�H�[�}�b�g�iA8R8G8B8 png X8R8G8B8 jpg�j
		D3DPOOL_DEFAULT,           // �������v�[���i�ʏ�� D3DPOOL_MANAGED�j
		D3DX_FILTER_TRIANGLE,      // �摜�̊g�k�t�B���^�iD3DX_FILTER_LINEAR �Ȃǁj
		D3DX_FILTER_TRIANGLE,      // �~�b�v�}�b�v�̃t�B���^
		0,                         // �J���[�L�[�i�����ɂ������F�j
		NULL,                      // `D3DXIMAGE_INFO`�i�摜�����擾����ꍇ�j
		NULL,                      // �p���b�g�f�[�^�i�p���b�g�Ȃ��Ȃ�NULL�j
		&g_pTextureInteract[INTERACT_TYPE_JOY]
	);

	//���̂̏�����
	g_Interact.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Interact.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_Interact.Type = INTERACT_TYPE_KEY;
	g_Interact.bUse = false;

	//���_�̐ݒ�
	SetVertex3DYX
	(
		&g_pVtxBuffInteract,
		0,
		1,
		1,
		1,
		INTERACT_WIDTH,
		INTERACT_HEIGHT,
		D3DXVECTOR3(0.0f, 0.0f, -1.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		INTERACT_WIDTH,
		INTERACT_HEIGHT,
		false, false
	);
}

//-------------------
//�|���S���I������
//-------------------
void UninitInteract(void)
{
	g_Interact.bUse = false;

	//�e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < INTERACT_TYPE_MAX; nCntTex++)
	{
		if (g_pTextureInteract[nCntTex] != NULL)
		{
			g_pTextureInteract[nCntTex]->Release();
			g_pTextureInteract[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffInteract != NULL)
	{
		g_pVtxBuffInteract->Release();
		g_pVtxBuffInteract = NULL;
	}
}

//-------------------
//�|���S���X�V����
//-------------------
void UpdateInteract(void)
{

}

//-------------------
//�|���S���`�揈��
//-------------------
void DrawInteract(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^
	D3DXMATRIX mtxScale, mtxTrans;//�v�Z�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	if (g_Interact.bUse)
	{//�g���Ă���
		//�}�g���b�N�X������
		D3DXMatrixIdentity(&g_Interact.mtxWorld);

		//�r���[�}�g���b�N�X�擾
		D3DXMATRIX mtxView;
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�J�����̋t�s���ݒ�
		g_Interact.mtxWorld._11 = mtxView._11;
		g_Interact.mtxWorld._12 = mtxView._21;
		g_Interact.mtxWorld._13 = mtxView._31;
		g_Interact.mtxWorld._21 = mtxView._12;
		g_Interact.mtxWorld._22 = mtxView._22;
		g_Interact.mtxWorld._23 = mtxView._32;
		g_Interact.mtxWorld._31 = mtxView._13;
		g_Interact.mtxWorld._32 = mtxView._23;
		g_Interact.mtxWorld._33 = mtxView._33;

		//�傫���̔��f
		D3DXMatrixScaling(&mtxScale, g_Interact.scale.x, g_Interact.scale.y, g_Interact.scale.z);
		D3DXMatrixMultiply(&g_Interact.mtxWorld, &g_Interact.mtxWorld, &mtxScale);

		//�ʒu�̌v�Z
		D3DXMatrixTranslation(&mtxTrans, g_Interact.pos.x, g_Interact.pos.y, g_Interact.pos.z);
		D3DXMatrixMultiply(&g_Interact.mtxWorld, &g_Interact.mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Interact.mtxWorld);

		//���_�o�b�t�@
		pDevice->SetStreamSource(0, g_pVtxBuffInteract, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureInteract[g_Interact.Type]);

		//�|���S���̕`��
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,//�^�C�v
			0,//�n�܂�̔ԍ�
			2//�|���S���̌�
		);
	}

	// Z�e�X�g��߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);


	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//----------
//�ݒ�
//----------
void SetInteract(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	g_Interact.pos = pos;      //�ʒu
	g_Interact.pos.y += 50.0f; //�����グ��
	g_Interact.scale = scale;  //�傫��
	g_Interact.bUse = true;    //�g�p
}

//----------------------
//�j��
//----------------------
void EndInteract(void)
{
	g_Interact.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   //�ʒu
	g_Interact.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f); //�傫��
	g_Interact.bUse = false;                          //�g�p
}

//---------------------
//�^�C�v�ύX
//---------------------
void SetInteractType(INTERACT_TYPE Type)
{
	g_Interact.Type = Type;
}