//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : 
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include <thread> // �P���t�{�|�����p�u�} �t�|�� ���p�q������ �� ���������{�p�}�y

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TEST,	// Test
	SOUND_LABEL_BGM,	// BGM
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label, float volume = 1.0f);
void StopSound(SOUND_LABEL label);
void StopSound(void);
void StopSound_Ex(void);
HRESULT SetSoundVolume(SOUND_LABEL label, float volume);

#endif
