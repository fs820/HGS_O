//---------------------------------------
//
//�X�R�A����[score.cpp]
//Author fuma sato
//
//---------------------------------------

#include "score.h"
#include "fade.h"
#include "sound.h"
#include <math.h>
#include "input.h"

#include <fstream>

// �C�|���q�p�|���~�p�� ���u���u�}�u�~�~�p�� �t�|�� ���q���u�s�� �����u���p
int totalScore = 0;



// �O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureScore[SCORE_UI_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
THANKYOU g_score[SCORE_UI_MAX];							// �X�R�A�̏��

//*********************************************
// �X�R�A��ʂ̏���������
//*********************************************
void InitScore(void)
{
	VERTEX_2D* pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SCORE_UI_MAX, // �K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_DEFAULT,
		&g_pVtxBuffScore,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < SCORE_UI_MAX; nCount++)
	{
		// �X�R�A�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFileEx(pDevice,
			SCORE_TEXTURES[nCount],
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
			&g_pTextureScore[nCount]);

		switch (nCount)
		{
		case SCORE_UI:		// �X�R�A�w�i
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.81f, SCREEN_HEIGHT * 0.18f, 0.0f);	// �ʒu�̐ݒ�
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.06f;										// ���̐ݒ�
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// �����̐ݒ�
			break;

		case SCORE_UI_ONE:		// �����i1�j
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.89f, SCREEN_HEIGHT * 0.18f, 0.0f);	// �ʒu�̐ݒ�
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.015f;										// ���̐ݒ�
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// �����̐ݒ�
			break;

		case SCORE_UI_TWO:		// �����i2�j
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.92f, SCREEN_HEIGHT * 0.18f, 0.0f);	// �ʒu�̐ݒ�
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.015f;										// ���̐ݒ�
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// �����̐ݒ�
			break;

		case SCORE_UI_THREE:		// �����i3�j
			g_score[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.95f, SCREEN_HEIGHT * 0.18f, 0.0f);	// �ʒu�̐ݒ�
			g_score[nCount].fWidth = SCREEN_WIDTH * 0.015f;										// ���̐ݒ�
			g_score[nCount].fHeight = SCREEN_HEIGHT * 0.025f;										// �����̐ݒ�
			break;
		}

		// ���_���W�̐ݒ�
		pVtx[0 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(-g_score[nCount].fWidth, -g_score[nCount].fHeight, 0.0f);
		pVtx[1 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(g_score[nCount].fWidth, -g_score[nCount].fHeight, 0.0f);
		pVtx[2 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(-g_score[nCount].fWidth, g_score[nCount].fHeight, 0.0f);
		pVtx[3 + (4 * nCount)].pos = g_score[nCount].pos + D3DXVECTOR3(g_score[nCount].fWidth, g_score[nCount].fHeight, 0.0f);

		// rhw�̐ݒ�
		pVtx[0 + (4 * nCount)].rhw = 1.0f;
		pVtx[1 + (4 * nCount)].rhw = 1.0f;
		pVtx[2 + (4 * nCount)].rhw = 1.0f;
		pVtx[3 + (4 * nCount)].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3 + (4 * nCount)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2 + (4 * nCount)].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3 + (4 * nCount)].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//*********************************************
// �X�R�A��ʂ̏I������
//*********************************************
void UninitScore(void)
{
	for (int nCount = 0; nCount < SCORE_UI_MAX; nCount++)
	{
		// ���_�o�b�t�@�̔j��
		if (g_pTextureScore[nCount] != NULL)
		{
			g_pTextureScore[nCount]->Release();
			g_pTextureScore[nCount] = NULL;
		}
	}

	// �w�i�e�N�X�`���̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

// �U���~�{���y�� �t�|�� ���q�~���r�|�u�~�y�� �������q���p�w�p�u�}���s�� �����u���p
void UpdateScore(int score)  // �S�u���u���� ���u���u�t�p�u�} ���p���p�}�u���� `score` �r �����~�{���y��
{
	VERTEX_2D* pVtx;  // �P���z�~���u�� �~�p �r�u�����y�~��

	// �Q�p�x�q�y�r�p�u�} �����u�� �~�p �t�u�������{�y, �������~�y �y �u�t�y�~�y����
	int scoreHundreds = (score / 100) % 10; // �W�y�����p �������u�~
	int scoreTens = (score / 10) % 10;      // �W�y�����p �t�u�������{���r
	int scoreOnes = score % 10;             // �W�y�����p �u�t�y�~�y��

	// �L���{�y�����u�} �q�����u�� �r�u�����y�~
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// �T�����p�~�p�r�|�y�r�p�u�} ���u�{���������~���u �{�������t�y�~�p���� �t�|�� �������u�~
	pVtx[4].tex = D3DXVECTOR2(scoreHundreds * 0.1f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(scoreHundreds * 0.1f + 0.1f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(scoreHundreds * 0.1f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(scoreHundreds * 0.1f + 0.1f, 1.0f);

	// �T�����p�~�p�r�|�y�r�p�u�} ���u�{���������~���u �{�������t�y�~�p���� �t�|�� �t�u�������{���r
	pVtx[8].tex = D3DXVECTOR2(scoreTens * 0.1f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(scoreTens * 0.1f + 0.1f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(scoreTens * 0.1f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(scoreTens * 0.1f + 0.1f, 1.0f);

	// �T�����p�~�p�r�|�y�r�p�u�} ���u�{���������~���u �{�������t�y�~�p���� �t�|�� �u�t�y�~�y��
	pVtx[12].tex = D3DXVECTOR2(scoreOnes * 0.1f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(scoreOnes * 0.1f + 0.1f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(scoreOnes * 0.1f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(scoreOnes * 0.1f + 0.1f, 1.0f);

	// �Q�p�x�q�|���{�y�����u�} �q�����u�� �r�u�����y�~
	g_pVtxBuffScore->Unlock();
}



void DrawScore(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 180);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���Z�b�g
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�X�R�AUI��`��
	for (int nCount = 0; nCount < SCORE_UI_MAX; nCount++)
	{
		pDevice->SetTexture(0, g_pTextureScore[nCount]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount, 2);
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}


//--------------------
//����������
//--------------------
int Digit(int nData, int nDigit)
{
	int aNumber[SCORE_MAX - 1] = { 0 };//�����p�z��
	int nData2 = 1;//�v�Z�p

	for (int i = SCORE_MAX - 2; i >= 0; i--)
	{//������
		if (i == 0)
		{
			aNumber[i] = nData / nData2;//�ŏ�ʂ̌�
		}
		aNumber[i] = nData % (nData2 * DIGIT) / nData2;//�v�Z
		nData2 *= DIGIT;//�������グ
	}

	return aNumber[nDigit];//�w��̌���Ԃ�
}

// �U���~�{���y�� �t�|�� �t���q�p�r�|�u�~�y�� �����{���r
void AddScore(int scoreToAdd) {
	totalScore += scoreToAdd;
	UpdateScore(totalScore);
}

// �U���~�{���y�� �t�|�� ���������p�~�u�~�y�� �����u���p �r ���p�z�| (�u���|�y �~���w�~��)
void SaveScore(int score) {
	const char* fileName = "score.txt"; // �I�}�� ���p�z�|�p �t�|�� ���������p�~�u�~�y��

	// �O���{�����r�p�u�} ���p�z�| �t�|�� �x�p���y���y
	std::ofstream outFile(fileName, std::ios::app);  // �O���{�����r�p�u�} �r ���u�w�y�}�u �t���q�p�r�|�u�~�y�� (append)
	if (outFile.is_open()) {
		outFile << "Score: " << score << std::endl;
		outFile.close();
	}
}