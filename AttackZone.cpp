//---------------------------------------
//
//�A�^�b�N�]�[������[AttackZone.cpp]
//Author fuma sato
//
//---------------------------------------
#include "AttackZone.h"
#include "camera.h"
#include "mesh.h"
#include "light.h"

AttackZone g_aAttackZone[ATTACK_ZONE_MAX];	// �A�^�b�N�]�[�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAttackZone = NULL; //�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureAttackZone = NULL;      //�e�N�X�`���̃|�C���^
//******************************************************
// �A�^�b�N�]�[��������
//******************************************************
void InitAttackZone(void)
{
	for (int nCntAttackZone = 0; nCntAttackZone < ATTACK_ZONE_MAX; nCntAttackZone++)
	{// �ő�A�^�b�N�]�[������
		// �e��ϐ��̏�����
		g_aAttackZone[nCntAttackZone].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	    // �ʒu
		g_aAttackZone[nCntAttackZone].fRadius = 0.0f;						    // ���a
		g_aAttackZone[nCntAttackZone].bLess = 0.0f;						        // ���a
		g_aAttackZone[nCntAttackZone].bUse = false;						        // �g�p
		g_aAttackZone[nCntAttackZone].col = D3DXCOLOR(0.3f, 0.0f, 0.0f, 0.1f);	// �F
	}

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4 * ATTACK_ZONE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_DEFAULT,
		&g_pVtxBuffAttackZone,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFileEx
	(
		pDevice,
		ATTACK_ZONE_TEX,
		D3DX_DEFAULT,              // �e�N�X�`���̕��iD3DX_DEFAULT�Ȃ玩�������j
		D3DX_DEFAULT,              // �e�N�X�`���̍����iD3DX_DEFAULT�Ȃ玩�������j
		D3DX_DEFAULT,              // �~�b�v�}�b�v���x���iD3DX_DEFAULT�Ŏ����ݒ�j
		0,                         // �g�p���Ȃ��ꍇ��0�i���I�e�N�X�`���Ȃ�D3DUSAGE_DYNAMIC�j
		D3DFMT_X8R8G8B8,           // �t�H�[�}�b�g�iA8R8G8B8 png X8R8G8B8 jpg�j
		D3DPOOL_DEFAULT,           // �������v�[���i�ʏ�� D3DPOOL_MANAGED�j
		D3DX_FILTER_TRIANGLE,      // �摜�̊g�k�t�B���^�iD3DX_FILTER_LINEAR �Ȃǁj
		D3DX_FILTER_TRIANGLE,      // �~�b�v�}�b�v�̃t�B���^
		0,                         // �J���[�L�[�i�����ɂ������F�j
		NULL,                      // `D3DXIMAGE_INFO`�i�摜�����擾����ꍇ�j
		NULL,                      // �p���b�g�f�[�^�i�p���b�g�Ȃ��Ȃ�NULL�j
		&g_pTextureAttackZone
	);

	//���_�̐ݒ�
	SetVertex3DZX
	(
		&g_pVtxBuffAttackZone,
		0, ATTACK_ZONE_MAX,
		1, 1,
		1.0f, 1.0f,
		D3DXVECTOR3(0.0f, 1.0f, 0.0f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
		1.0f, 1.0f
	);
}

//-----------------------------------------------------
//�I������
//-----------------------------------------------------
void UninitAttackZone(void)
{
	for (int nCntAttackZone = 0; nCntAttackZone < ATTACK_ZONE_MAX; nCntAttackZone++)
	{// �ő�A�^�b�N�]�[������
		// �e��ϐ��̏�����
		g_aAttackZone[nCntAttackZone].bUse = false;	// �g�p
		EndLight(4 + nCntAttackZone);				// ���C�g�̏I��
	}
	if (g_pTextureAttackZone != NULL)
	{
		g_pTextureAttackZone->Release();
		g_pTextureAttackZone = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffAttackZone != NULL)
	{
		g_pVtxBuffAttackZone->Release();
		g_pVtxBuffAttackZone = NULL;
	}
}

//------------------------------------------------------
//�`�揈��
//------------------------------------------------------
void DrawAttackZone(void)
{
	LPDIRECT3DDEVICE9 pDevice; // �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxTrans; // �v�Z�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0); // 0�̕����K�� sato
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// Depth Bias �ݒ� sato
	float depthBias = -0.000001f; //Z�o�b�t�@���J���������ɃI�t�Z�b�g����l

	// �����ق�����`�悷��
	static int nIdx[ATTACK_ZONE_MAX]; // �������i�[�p
	static int nLimit = 0;
	if (nLimit % 60 == 0)
	{// �t���[�����Ƃɏ��� (���t���[�����Əd���Ȃ�\�������邽��)
		D3DXVECTOR3 PosList[ATTACK_ZONE_MAX]; // �|�X���X�g
		Camera* pCamera = GetCamera();
		for (int nCnt = 0; nCnt < ATTACK_ZONE_MAX; nCnt++)
		{// �|�X���X�g�쐬
			if (g_aAttackZone[nCnt].bUse)
			{
				PosList[nCnt] = g_aAttackZone[nCnt].pos;
			}
			else
			{
				PosList[nCnt] = pCamera->posV;
			}
		}
		DrawCameraFarSort(nIdx, PosList, ATTACK_ZONE_MAX); //�������Ƀ\�[�g
	}
	nLimit++;

	for (int nCntAttackZone = 0; nCntAttackZone < ATTACK_ZONE_MAX; nCntAttackZone++)
	{
		if (g_aAttackZone[nIdx[nCntAttackZone]].bUse == false)
		{
			break;
		}

		if (g_aAttackZone[nIdx[nCntAttackZone]].bLess)
		{
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		else
		{
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		depthBias += -0.000001f; //�e���m�̏d�Ȃ�������
		pDevice->SetRenderState(D3DRS_DEPTHBIAS, *(DWORD*)&depthBias); //Z�o�C�A�X�ݒ�

		// �}�g���b�N�X������
		D3DXMatrixIdentity(&g_aAttackZone[nIdx[nCntAttackZone]].mtxWorld);

		// �ʒu�̌v�Z
		D3DXMatrixTranslation(&mtxTrans, g_aAttackZone[nIdx[nCntAttackZone]].pos.x, g_aAttackZone[nIdx[nCntAttackZone]].pos.y, g_aAttackZone[nIdx[nCntAttackZone]].pos.z);
		D3DXMatrixMultiply(&g_aAttackZone[nIdx[nCntAttackZone]].mtxWorld, &g_aAttackZone[nIdx[nCntAttackZone]].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aAttackZone[nIdx[nCntAttackZone]].mtxWorld);

		// ���_�o�b�t�@
		pDevice->SetStreamSource(0, g_pVtxBuffAttackZone, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureAttackZone);

		for (int nCnt = 0; nCnt < 20; nCnt++)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,        // �^�C�v
				4 * nIdx[nCntAttackZone],
				2                          // �|���S���̌�
			);
		}
	}

	// Depth Bias �ݒ������ sato
	float resetBias = 0.0f;
	pDevice->SetRenderState(D3DRS_DEPTHBIAS, *(DWORD*)&resetBias);

	// Z�e�X�g��߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// �A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �ݒ�������ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//******************************************************
// �A�^�b�N�]�[���ݒ�
//******************************************************
int SetAttackZone(D3DXVECTOR3 pos, float fRadius, D3DXCOLOR col, bool Less)
{
	for (int nCntAttackZone = 0; nCntAttackZone < ATTACK_ZONE_MAX; nCntAttackZone++)
	{// �ő�A�^�b�N�]�[������
		if (g_aAttackZone[nCntAttackZone].bUse == false)
		{// �g���Ă��Ȃ��A�^�b�N�]�[��
			g_aAttackZone[nCntAttackZone].pos = pos;		    // �ʒu
			g_aAttackZone[nCntAttackZone].fRadius = fRadius;	// ���a
			g_aAttackZone[nCntAttackZone].col = col;	        // ���a
			g_aAttackZone[nCntAttackZone].bLess = Less;		// ���Z
			g_aAttackZone[nCntAttackZone].bUse = true;		// �g�p

			//���_�̐ݒ�
			SetVertex3DZX
			(
				&g_pVtxBuffAttackZone,
				nCntAttackZone,
				1,
				1,
				1,
				g_aAttackZone[nCntAttackZone].fRadius * 2.0f,
				g_aAttackZone[nCntAttackZone].fRadius * 2.0f,
				D3DXVECTOR3(0.0f, 1.0f, 0.0f),
				g_aAttackZone[nCntAttackZone].col,
				g_aAttackZone[nCntAttackZone].fRadius * 2.0f,
				g_aAttackZone[nCntAttackZone].fRadius * 2.0f
			);
			SetLight(4 + nCntAttackZone, g_aAttackZone[nCntAttackZone].fRadius, g_aAttackZone[nCntAttackZone].col * 20.0f, g_aAttackZone[nCntAttackZone].pos + D3DXVECTOR3(0.0f, g_aAttackZone[nCntAttackZone].fRadius * 0.5f, 0.0f));
			return nCntAttackZone;
		}
	}
	return -1;
}

//******************************************************
// �A�^�b�N�]�[���j��
//******************************************************
void EndAttackZone(int nIdx)
{
	g_aAttackZone[nIdx].bUse = false;		// �g�p
	EndLight(4 + nIdx);
}