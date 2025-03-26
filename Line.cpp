//---------------------------------------
//
//�{�[������[Line.cpp]
//Author fuma sato
//
//---------------------------------------
#include"Line.h"
#include"mesh.h"
#include"input.h"
#include"vectorcollision.h"
#include"rotation.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine = NULL;//�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureLine = NULL;
Line g_Line[LINE_MAX];
//-----------------
// ����������
//-----------------
void InitLine(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * VT_MAX * LINE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine,
		NULL
	);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		LINE_TEX,
		&g_pTextureLine
	);

	for (int nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		g_Line[nCntLine].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Line[nCntLine].fAngle = 0.0f;
		g_Line[nCntLine].bUse = false;
		g_Line[nCntLine].bHold = false;
	}
	//1��

	SetVertex2D
	(
		&g_pVtxBuffLine,
		0, LINE_MAX,
		1, 1,
		D3DXVECTOR2(0.0f, 0.0f), 0.0f,
		LINE_WIDTH, LINE_HEIGHT,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		LINE_WIDTH, LINE_HEIGHT
	);

	HoldLine();
}

//-----------------
// �I������
//-----------------
void UninitLine(void)
{
	SAFE_RELEASE(g_pTextureLine);
	SAFE_RELEASE(g_pVtxBuffLine);
}

//-----------------
// �X�V����
//-----------------
void UpdateLine(void)
{
	for (int nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		if (g_Line[nCntLine].bUse == true)
		{
			SetVertex2D
			(
				&g_pVtxBuffLine,
				nCntLine, 1,
				1, 1,
				g_Line[nCntLine].pos, g_Line[nCntLine].fAngle,
				LINE_WIDTH, LINE_HEIGHT,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				LINE_WIDTH, LINE_HEIGHT
			);
		}
		else if (g_Line[nCntLine].bHold == true)
		{
			POINT Point = GetCursorPoint();
			D3DXVECTOR2 CursorPos = D3DXVECTOR2((float)Point.x, (float)Point.y);

			static float fAngle;

			if (GetMouseWheel() > 0.0f)
			{
				fAngle += D3DX_PI * LINE_ROT_SPEED;
			}
			else if (GetMouseWheel() < 0.0f)
			{
				fAngle -= D3DX_PI * LINE_ROT_SPEED;
			}

			NormalizeAngle(fAngle);

			SetVertex2D
			(
				&g_pVtxBuffLine,
				nCntLine, 1,
				1, 1,
				CursorPos, fAngle,
				LINE_WIDTH, LINE_HEIGHT,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
				LINE_WIDTH, LINE_HEIGHT
			);

			if (GetMouseTrigger(MOUSE_LEFT))
			{
				SetLine(nCntLine, CursorPos, fAngle);
			}
		}
	}
}

//-----------------
// �`�揈��
//-----------------
void DrawLine(void) 
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�փ|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		if (g_Line[nCntLine].bUse || g_Line[nCntLine].bHold)
		{
			//���_�o�b�t�@
			pDevice->SetStreamSource(0, g_pVtxBuffLine, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureLine);

			//�|���S���̕`��
			HRESULT hr = pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,//�^�C�v
				nCntLine * VT_MAX,//�n�܂�̔ԍ�
				2//�|���S���̌�
			);
		}
	}
}

//-----------------
// �ݒ�
//-----------------
void SetLine(int HoldIdx, D3DXVECTOR2 pos, float fAngle)
{
	g_Line[HoldIdx].pos = pos;
	g_Line[HoldIdx].fAngle = fAngle;
	g_Line[HoldIdx].bUse = true;
	g_Line[HoldIdx].bHold = false;
	HoldLine();
}

//-----------------
// �ҋ@���
//-----------------
void HoldLine(void)
{
	for (int nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		if (g_Line[nCntLine].bUse == false)
		{
			g_Line[nCntLine].bHold = true;
			break;
		}
	}
}

//--------------------------------
// ���t���N�V����
//--------------------------------
void ReflectionLine(D3DXVECTOR2& pos, D3DXVECTOR2& posOld, D3DXVECTOR2& move, float fWidth)
{
	for (int nCntLine = 0; nCntLine < LINE_MAX; nCntLine++)
	{
		if (g_Line[nCntLine].bUse)
		{
			D3DXVECTOR3 RightUp = D3DXVECTOR3(LINE_WIDTH * 0.5f, -LINE_HEIGHT * 0.5f, 0.0f),
				LeftUp = D3DXVECTOR3(-LINE_WIDTH * 0.5f, -LINE_HEIGHT * 0.5f, 0.0f),
				LeftDown = D3DXVECTOR3(-LINE_WIDTH * 0.5f, LINE_HEIGHT * 0.5f, 0.0f),
				RightDown = D3DXVECTOR3(LINE_WIDTH * 0.5f, LINE_HEIGHT * 0.5f, 0.0f);
			RotationofShaftbyMatrix(RightUp, RightUp, D3DXVECTOR3(0.0f, 0.0f, g_Line[nCntLine].fAngle), TYPE_Z);
			RotationofShaftbyMatrix(LeftUp, LeftUp, D3DXVECTOR3(0.0f, 0.0f, g_Line[nCntLine].fAngle), TYPE_Z);
			RotationofShaftbyMatrix(LeftDown, LeftDown, D3DXVECTOR3(0.0f, 0.0f, g_Line[nCntLine].fAngle), TYPE_Z);
			RotationofShaftbyMatrix(RightDown, RightDown, D3DXVECTOR3(0.0f, 0.0f, g_Line[nCntLine].fAngle), TYPE_Z);

			D3DXVECTOR2 RightUp2 = (D3DXVECTOR2)RightUp,
				LeftUp2 = (D3DXVECTOR2)LeftUp,
				LeftDown2 = (D3DXVECTOR2)LeftDown,
				RightDown2 = (D3DXVECTOR2)RightDown;

			RightUp2 += g_Line[nCntLine].pos;
			LeftUp2 += g_Line[nCntLine].pos;
			LeftDown2 += g_Line[nCntLine].pos;
			RightDown2 += g_Line[nCntLine].pos;

			for (int nCnt10 = 0; nCnt10 < 10; nCnt10++)
			{
				VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, RightUp2, LeftUp2);
				VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, LeftUp2, LeftDown2);
				VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, LeftDown2, RightDown2);
				VectorReflection(pos, posOld, move, fWidth - (fWidth / 10.0f) * nCnt10, RightDown2, RightUp2);
			}
		}
	}
}