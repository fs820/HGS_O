#include "timer.h"
#include "fade.h"
#include "sound.h"
#include <math.h>
#include "input.h"
#include "score.h"

// �O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTimer[TIMER_MAX] = {};    // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;        // ���_�o�b�t�@�ւ̃|�C���^
TIMER g_timer[TIMER_MAX];                               // �^�C�}�[�̏��

//*********************************************
// �^�C�}�[��ʂ̏���������
//*********************************************
void InitTimer(void)
{
    VERTEX_2D* pVtx;

    LPDIRECT3DDEVICE9 pDevice;

    // �f�o�C�X�̎擾
    pDevice = GetDevice();

    // ���_�o�b�t�@�̐���
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIMER_MAX, // �K�v�Ȓ��_��
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_2D,
        D3DPOOL_DEFAULT,
        &g_pVtxBuffTimer,
        NULL);

    // ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

    for (int nCount = 0; nCount < TIMER_MAX; nCount++)
    {
        // �^�C�}�[�֘A�̃e�N�X�`���̓ǂݍ���
        D3DXCreateTextureFromFileEx(pDevice,
            TIMER_TEXTURES[nCount],
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
            &g_pTextureTimer[nCount]);

        // �^�C�}�[�̈ʒu�ƃT�C�Y�ݒ�
        

        switch (nCount)
        {
        case TIMER_LABEL:		// ����
            g_timer[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.1f, 0.0f);  // �ʒu�̐ݒ�
            g_timer[nCount].fWidth = SCREEN_WIDTH * 0.05f;                                       // ���̐ݒ�
            g_timer[nCount].fHeight = SCREEN_HEIGHT * 0.025f;                                      // �����̐ݒ�
            break;

        case TIMER_DIGITS:		// ����
            g_timer[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.87f, SCREEN_HEIGHT * 0.1f, 0.0f);  // �ʒu�̐ݒ�
            g_timer[nCount].fWidth = SCREEN_WIDTH * 0.015f;                                       // ���̐ݒ�
            g_timer[nCount].fHeight = SCREEN_HEIGHT * 0.025f;                                      // �����̐ݒ�
            break;

        case TIMER_DIGITS_TWO:		// ����
            g_timer[nCount].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 0.1f, 0.0f);  // �ʒu�̐ݒ�
            g_timer[nCount].fWidth = SCREEN_WIDTH * 0.015f;                                       // ���̐ݒ�
            g_timer[nCount].fHeight = SCREEN_HEIGHT * 0.025f;                                      // �����̐ݒ�
            break;

        }
        // ���_���W�̐ݒ�
        pVtx[0 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(-g_timer[nCount].fWidth, -g_timer[nCount].fHeight, 0.0f);
        pVtx[1 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(g_timer[nCount].fWidth, -g_timer[nCount].fHeight, 0.0f);
        pVtx[2 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(-g_timer[nCount].fWidth, g_timer[nCount].fHeight, 0.0f);
        pVtx[3 + (4 * nCount)].pos = g_timer[nCount].pos + D3DXVECTOR3(g_timer[nCount].fWidth, g_timer[nCount].fHeight, 0.0f);

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
    g_pVtxBuffTimer->Unlock();
}

//*********************************************
// �^�C�}�[��ʂ̏I������
//*********************************************
void UninitTimer(void)
{
    for (int nCount = 0; nCount < TIMER_MAX; nCount++)
    {
        // �e�N�X�`���̔j��
        if (g_pTextureTimer[nCount] != NULL)
        {
            g_pTextureTimer[nCount]->Release();
            g_pTextureTimer[nCount] = NULL;
        }
    }

    // ���_�o�b�t�@�̔j��
    if (g_pVtxBuffTimer != NULL)
    {
        g_pVtxBuffTimer->Release();
        g_pVtxBuffTimer = NULL;
    }
}

//*********************************************
// �^�C�}�[��ʂ̍X�V����
//*********************************************
void UpdateTimer(void)
{
    VERTEX_2D* pVtx;  // �P���z�~���u�� �~�p �r�u�����y�~��
    static float timeElapsed = 100.0f; // �N�p���p�|���~���u �x�~�p���u�~�y�u �r���u�}�u�~�y (99)

    // �R�{������������ ���p�z�}�u���p
    const float timeSpeed = 0.012f;

    // �O�q�~���r�|�u�~�y�u �r���u�}�u�~�y
    timeElapsed -= timeSpeed;
    if (timeElapsed < 0.0f) {
        timeElapsed = 0.0f; // �B���u�}�� �~�u �t���|�w�~�� �q������ �}�u�~�����u 0
    }

    // �P���u���q���p�x���u�} �r���u�}�� �r ���u�|���u ���y���|��
    int timeInt = static_cast<int>(timeElapsed);

    // �Q�p�x�q�y�r�p�u�} �r���u�}�� �~�p �t�u�������{�y �y �u�t�y�~�y����
    int timeTens = (timeInt / 10) % 10; // �W�y�����p �t�u�������{���r
    int timeOnes = timeInt % 10;        // �W�y�����p �u�t�y�~�y��

    // �L���{�y�����u�} �q�����u�� �r�u�����y�~
    g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

    // �T�����p�~�p�r�|�y�r�p�u�} ���u�{���������~���u �{�������t�y�~�p���� �t�|�� �t�u�������{���r
    pVtx[4].tex = D3DXVECTOR2(timeTens * 0.1f, 0.0f);
    pVtx[5].tex = D3DXVECTOR2(timeTens * 0.1f + 0.1f, 0.0f);
    pVtx[6].tex = D3DXVECTOR2(timeTens * 0.1f, 1.0f);
    pVtx[7].tex = D3DXVECTOR2(timeTens * 0.1f + 0.1f, 1.0f);

    // �T�����p�~�p�r�|�y�r�p�u�} ���u�{���������~���u �{�������t�y�~�p���� �t�|�� �u�t�y�~�y��
    pVtx[8].tex = D3DXVECTOR2(timeOnes * 0.1f, 0.0f);
    pVtx[9].tex = D3DXVECTOR2(timeOnes * 0.1f + 0.1f, 0.0f);
    pVtx[10].tex = D3DXVECTOR2(timeOnes * 0.1f, 1.0f);
    pVtx[11].tex = D3DXVECTOR2(timeOnes * 0.1f + 0.1f, 1.0f);

	/*AddScore(1);*/
    // �Q�p�x�q�|���{�y�����u�} �q�����u�� �r�u�����y�~
    g_pVtxBuffTimer->Unlock();

    // �E���|�y �r���u�}�� �y�����u�{�|��, �x�p�{�p�~���y�r�p�u�} �y�s����
    if (timeElapsed <= 0.0f) {
        
        FADE fade = GetFade(); //sato
        if (fade == FADE_NONE)
        {//�J�ڒ��łȂ� sato
            SetFade(MODE_RESULT, 2.0f);
        }
        
    }

	// ��������X�R�A��ۑ�
    //if (isGameWon) {
    //    int remainingTimeInSeconds = static_cast<int>(timeElapsed);
    //    int score = remainingTimeInSeconds * 10; // 1 sec = 10 points
    //    SaveScore(score);
    //}
}



//*********************************************
// �^�C�}�[��ʂ̕`�揈��
//*********************************************
void DrawTimer(void)
{
    // �f�o�C�X�ւ̃|�C���^
    LPDIRECT3DDEVICE9 pDevice = GetDevice();

    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ALPHAREF, 180);
    pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

    pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));
    pDevice->SetFVF(FVF_VERTEX_2D);

    for (int nCount = 0; nCount < TIMER_MAX; nCount++)
    {
        pDevice->SetTexture(0, g_pTextureTimer[nCount]);
        pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCount, 2);
    }

    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
