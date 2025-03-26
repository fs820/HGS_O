//---------------------------------------
//
//セーブ・ロード処理[file.cpp]
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
	FILE* pFile;//ファイルポインタを宣言
	MODE Mode = GetMode();
	int nCount = 0;
	int nNumber = 0;
	D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);
	float fAngle = 0.0f;

	pFile = fopen(SHARP_FILE, "r");//ファイルを開く

	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < BLOCK_MAX; nCount++)
		{//最大数回す
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &fAngle) == EOF)break;//数値を書き入れ


			fAngle=D3DXToRadian(fAngle);
			//オブジェクト設置
			SetSharp(pos,fAngle);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		Error();
	}
}
void SaveSharp(void)
{
	FILE* pFile;//ファイルポインタを宣言
	MODE Mode = GetMode();
	float fAngle;
	int nCount = 0;

	pFile = fopen(SHARP_FILE, "w");//ファイルを開く

	if (pFile != NULL)
	{//開けたら
		extern Sharp g_Sharp[SHARP_MAX];
		for (nCount = 0; nCount < SHARP_MAX; nCount++)
		{//最大数回す
			if (g_Sharp[nCount].bUse)
			{//使用している
				//角度変換
				fAngle = D3DXToDegree(g_Sharp[nCount].fAngle);

				fprintf(pFile, "%.1f ", g_Sharp[nCount].pos.x);//数値を書き入れ
				fprintf(pFile, "%.1f\n\n", g_Sharp[nCount].pos.y);//数値を書き入れ
				fprintf(pFile, "%.1f\n\n", fAngle);//数値を書き入れ
			}
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		Error();
	}
}
void LoadBrick(void)
{
	FILE* pFile;//ファイルポインタを宣言
	MODE Mode = GetMode();
	int nCount = 0;
	int nNumber = 0;
	D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);
	float fAngle = 0.0f;

	pFile = fopen(BRICK_FILE, "r");//ファイルを開く

	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < BLOCK_MAX; nCount++)
		{//最大数回す
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &fAngle) == EOF)break;//数値を書き入れ

			fAngle = D3DXToRadian(fAngle);
			//オブジェクト設置
			SetBrick(pos, fAngle);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		Error();
	}
}
void SaveBrick(void)
{
	FILE* pFile;//ファイルポインタを宣言
	MODE Mode = GetMode();
	float fAngle;
	int nCount = 0;

	pFile = fopen(BRICK_FILE, "w");//ファイルを開く

	if (pFile != NULL)
	{//開けたら
		extern Brick g_Brick[BRICK_MAX];
		for (nCount = 0; nCount < BRICK_MAX; nCount++)
		{//最大数回す
			if (g_Brick[nCount].bUse)
			{//使用している
				//角度変換
				fAngle = D3DXToDegree(g_Brick[nCount].fAngle);

				fprintf(pFile, "%.1f ", g_Brick[nCount].pos.x);//数値を書き入れ
				fprintf(pFile, "%.1f\n\n", g_Brick[nCount].pos.y);//数値を書き入れ
				fprintf(pFile, "%.1f\n\n", fAngle);//数値を書き入れ
			}
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		Error();
	}
}
void LoadBlock(void)
{
	FILE* pFile;//ファイルポインタを宣言
	MODE Mode = GetMode();
	int nCount = 0;
	int nNumber = 0;
	D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);

	pFile = fopen(BLOCK_FILE, "r");//ファイルを開く

	if (pFile != NULL)
	{//開けたら
		for (nCount = 0; nCount < BLOCK_MAX; nCount++)
		{//最大数回す
			if (fscanf(pFile, "%f", &pos.x) == EOF)break;//数値を書き入れ
			if (fscanf(pFile, "%f", &pos.y) == EOF)break;//数値を書き入れ

			//オブジェクト設置
			SetBlock(pos);
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
		Error();
	}
}
void SaveBlock(void)
{
	FILE* pFile;//ファイルポインタを宣言
	MODE Mode = GetMode();
	int nCount = 0;

	pFile = fopen(BLOCK_FILE, "w");//ファイルを開く

	if (pFile != NULL)
	{//開けたら
		extern Block g_Block[BLOCK_MAX];
		for (nCount = 0; nCount < BLOCK_MAX; nCount++)
		{//最大数回す
			if (g_Block[nCount].bUse)
			{//使用している
				fprintf(pFile, "%.1f ", g_Block[nCount].pos.x);//数値を書き入れ
				fprintf(pFile, "%.1f\n\n", g_Block[nCount].pos.y);//数値を書き入れ
			}
		}
		fclose(pFile);//ファイルを閉じる
	}
	else
	{//開けなかった
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