//---------------------------------------
//
//�Z�[�u�E���[�h����[file.cpp]
//Author fuma sato
//
//---------------------------------------

#include"file.h"

#include "input.h"

#include "block.h"
#include "Brick.h"
#include "Sharp.h"

void LoadSharp(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	MODE Mode = GetMode();
	int nCount = 0;
	int nNumber = 0;
	D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);
	float fAngle = 0.0f;

	pFile = fopen(SHARP_FILE, "r");//�t�@�C�����J��

	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < BLOCK_MAX; nCount++)
		{//�ő吔��
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &fAngle) == EOF)break;//���l����������


			fAngle=D3DXToRadian(fAngle);
			//�I�u�W�F�N�g�ݒu
			SetSharp(pos,fAngle);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		Error();
	}
}
void SaveSharp(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	MODE Mode = GetMode();
	float fAngle;
	int nCount = 0;

	pFile = fopen(SHARP_FILE, "w");//�t�@�C�����J��

	if (pFile != NULL)
	{//�J������
		extern Sharp g_Sharp[SHARP_MAX];
		for (nCount = 0; nCount < SHARP_MAX; nCount++)
		{//�ő吔��
			if (g_Sharp[nCount].bUse)
			{//�g�p���Ă���
				//�p�x�ϊ�
				fAngle = D3DXToDegree(g_Sharp[nCount].fAngle);

				fprintf(pFile, "%.1f ", g_Sharp[nCount].pos.x);//���l����������
				fprintf(pFile, "%.1f\n\n", g_Sharp[nCount].pos.y);//���l����������
				fprintf(pFile, "%.1f\n\n", fAngle);//���l����������
			}
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		Error();
	}
}
void LoadBrick(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	MODE Mode = GetMode();
	int nCount = 0;
	int nNumber = 0;
	D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);
	float fAngle = 0.0f;

	pFile = fopen(BRICK_FILE, "r");//�t�@�C�����J��

	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < BLOCK_MAX; nCount++)
		{//�ő吔��
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &fAngle) == EOF)break;//���l����������

			fAngle = D3DXToRadian(fAngle);
			//�I�u�W�F�N�g�ݒu
			SetBrick(pos, fAngle);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		Error();
	}
}
void SaveBrick(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	MODE Mode = GetMode();
	float fAngle;
	int nCount = 0;

	pFile = fopen(BRICK_FILE, "w");//�t�@�C�����J��

	if (pFile != NULL)
	{//�J������
		extern Brick g_Brick[BRICK_MAX];
		for (nCount = 0; nCount < BRICK_MAX; nCount++)
		{//�ő吔��
			if (g_Brick[nCount].bUse)
			{//�g�p���Ă���
				//�p�x�ϊ�
				fAngle = D3DXToDegree(g_Brick[nCount].fAngle);

				fprintf(pFile, "%.1f ", g_Brick[nCount].pos.x);//���l����������
				fprintf(pFile, "%.1f\n\n", g_Brick[nCount].pos.y);//���l����������
				fprintf(pFile, "%.1f\n\n", fAngle);//���l����������
			}
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		Error();
	}
}
void LoadBlock(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	MODE Mode = GetMode();
	int nCount = 0;
	int nNumber = 0;
	D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);

	pFile = fopen(BLOCK_FILE, "r");//�t�@�C�����J��

	if (pFile != NULL)
	{//�J������
		for (nCount = 0; nCount < BLOCK_MAX; nCount++)
		{//�ő吔��
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//���l����������
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//���l����������

			//�I�u�W�F�N�g�ݒu
			SetBlock(pos);
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		Error();
	}
}
void SaveBlock(void)
{
	FILE* pFile;//�t�@�C���|�C���^��錾
	MODE Mode = GetMode();
	int nCount = 0;

	pFile = fopen(BLOCK_FILE, "w");//�t�@�C�����J��

	if (pFile != NULL)
	{//�J������
		extern Block g_Block[BLOCK_MAX];
		for (nCount = 0; nCount < BLOCK_MAX; nCount++)
		{//�ő吔��
			if (g_Block[nCount].bUse)
			{//�g�p���Ă���
				fprintf(pFile, "%.1f ", g_Block[nCount].pos.x);//���l����������
				fprintf(pFile, "%.1f\n\n", g_Block[nCount].pos.y);//���l����������
			}
		}
		fclose(pFile);//�t�@�C�������
	}
	else
	{//�J���Ȃ�����
		Error();
	}
}

void Edit(void)
{
	D3DXVECTOR2 CursorPos = D3DXVECTOR2((float)GetCursorPoint().x, (float)GetCursorPoint().y);

	extern Block g_Block[BLOCK_MAX];
	extern Brick g_Brick[BRICK_MAX];
	extern Sharp g_Sharp[SHARP_MAX];

	static float fAngle;
	static int nType = 0;

	static int nIdx[3] = { 0 };

	if (GetMouseTrigger(MOUSE_B1) == true)
	{
		nType++;
	}
	else if (GetMouseTrigger(MOUSE_B2) == true)
	{
		nType--;
	}

	if (nType<0)
	{
		nType = 2;
	}
	nType %= 3;

	if (GetMouseWheel() > 0.0f)
	{
		fAngle += D3DX_PI * 0.1f;
	}
	else if (GetMouseWheel() < 0.0f)
	{
		fAngle -= D3DX_PI * 0.1f;
	}

	if (GetMouseTrigger(MOUSE_LEFT) == true)
	{
		switch (nType)
		{
		case 0:
			nIdx[0] = SetBlock(CursorPos);
			break;
		case 1:
			nIdx[1] = SetBrick(CursorPos, fAngle);
			break;
		case 2:
			nIdx[2] = SetSharp(CursorPos, fAngle);
			break;
		}
	}

	if (GetMouseTrigger(MOUSE_RIGHT) == true)
	{
		switch (nType)
		{
		case 0:
			g_Block[nIdx[0]].bUse = false;
			break;
		case 1:
			g_Brick[nIdx[1]].bUse = false;
			break;
		case 2:
			g_Sharp[nIdx[2]].bUse = false;
			break;
		}
	}

	if (GetMouseTrigger(MOUSE_SENTER) == true)
	{
		SaveBlock();
		SaveBrick();
		SaveSharp();
	}
}