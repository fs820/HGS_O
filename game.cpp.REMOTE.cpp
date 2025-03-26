//------------------------------------------
//
//�Q�[�����C���̏���[game.cpp]
//Author fuma sato
//
//------------------------------------------

#include"game.h"
#include"input.h"
#include"ball.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"pause.h"
#include"time.h"
#include"fade.h"
#include"sound.h"
#include"file.h"
#include "Back.h"
#include "timer.h"
#include "Line.h"
#include "block.h"
#include "Brick.h"
#include "score.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;
int g_nCounterGameState = 0;
int g_GameTime = 0;
bool g_bSnow = false;
bool g_bClear = false;
//--------------------
//����������
//--------------------
void InitGame(void)
{
	InitBack();
	InitBrick();
	InitBlock();
	InitBall();
	InitLine();
	InitEffect();
	InitParticle();
    InitTimer();
	InitScore();

	SetBall(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(1.0f, 0.0f));

	D3DXVECTOR3 posScore;//�X�R�A�̈ʒu
	g_gameState = GAMESTATE_NORMAL;
	g_nCounterGameState = 0;
	g_GameTime = 0;
	g_bSnow = false;
	g_bClear = false;
}

//------------------
//�I������
//------------------
void UninitGame(void)
{
	g_gameState = GAMESTATE_NONE;

	UninitParticle();
	UninitEffect();
	UninitLine();
	UninitBall();
	UninitBlock();
	UninitBrick();
	UninitBack();
	UninitTimer();
	UninitScore();
}

//--------------
//�X�V����
//--------------
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) == true || GetJoykeyTrigger(JOYKEY_START, CONTROLLER_MAX) == true || GetMouseTrigger(MOUSE_SENTER) == true)
	{
		FADE fade;
		fade = GetFade();
		if (fade == FADE_NONE)
		{
			Pause();
		}
	}
	for (int i = 0; i < ControllerNum(CONTYPE_D); i++)
	{
		if (!strcmp(ControllerName((CONTROLLER)i), ELE_CON))
		{
			if (GetdJoykeyTrigger(ELEKEY_START, (CONTROLLER)i))
			{
				Pause();
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), PS_CON))
		{
			if (GetdJoykeyTrigger(PSKEY_START, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause();
				}
			}
		}
		else if (!strcmp(ControllerName((CONTROLLER)i), NIN_CON))
		{
			if (GetdJoykeyTrigger(NINKEY_�{, (CONTROLLER)i))
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					Pause();
				}
			}
		}
		else if (!IsXInputControllerConnected((CONTROLLER)i) && IsDirectInputControllerConnected((CONTROLLER)i))
		{
			if (GetdJoykeyTrigger(DKEY_START, (CONTROLLER)i))
			{
				Pause();
			}
		}
	}
	
	if (!bPause())
	{
		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
			g_GameTime++;
			if (g_GameTime / FRAME >= TIME_LIMIT)
			{
				g_gameState = GAMESTATE_END;
				g_bClear = true;
			}
			break;
		case GAMESTATE_END:
			g_nCounterGameState++;
			if (g_nCounterGameState >= INTER)
			{
				FADE fade;
				fade = GetFade();
				if (fade == FADE_NONE)
				{
					//�ؑ�
					SetFade(MODE_RESULT, true);
				}
			}
			break;
		}

		float Rot = ROT_RAND;
		SetBall(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(sinf(Rot), cosf(Rot)));
		SetBlock(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + sinf(Rot) * 500.f, SCREEN_HEIGHT * 0.5f + cosf(Rot) * 500.f));
		SetBrick(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + sinf(Rot) * 400.f, SCREEN_HEIGHT * 0.5f + cosf(Rot) * 400.f), Rot);

		UpdateBack();
		UpdateBrick();
		UpdateBlock();
		UpdateBall();
		UpdateLine();
		UpdateEffect();
		UpdateParticle();
		UpdateTimer();
		UpdateScore(totalScore);
	}
}

//-------------------
//�`�揈��
//-------------------
void DrawGame(void)
{
	DrawBack();
	DrawBrick();
	DrawBlock();
	DrawLine();
	DrawEffect();
	DrawBall();
	DrawTimer();
	DrawScore();
}

//----------------------
//�Q�[����Ԑؑ�
//----------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}

//-----------------------
//�Q�[����Ԏ擾
//-----------------------
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//-----------------------
//�X�m�[�擾
//-----------------------
bool GetbSnow(void)
{
	return g_bSnow;
}

//---------------------
//�N���A�擾
//---------------------
bool GetClear(void)
{
	return g_bClear;
}

//---------------------
//�N���A�擾
//---------------------
int GetClearTime(void)
{
	int H = (((g_GameTime / FRAME) * (int)(HOUR * ((float)MINUTE / (float)TIME_LIMIT))) / MINUTE) * 100;
	int M = ((g_GameTime / FRAME) * (int)(HOUR * ((float)MINUTE / (float)TIME_LIMIT))) % MINUTE;
	return H + M;
}

//---------------------
//�N���A�擾
//---------------------
int GetTime(void)
{
	return g_GameTime / FRAME;
}

//---------------------
//���ԏ�����
//---------------------
void TimeReset(void)
{
	g_GameTime = 0;
}