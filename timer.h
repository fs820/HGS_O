#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

// �P�u���u���y���|�u�~�y�u ���y�����r ���u�{�������� �t�|�� ���p�z�}�u���p
typedef enum
{
    TIMER_LABEL = 0,  // "Time: "
    TIMER_DIGITS,      // �X�y���|���r���u �������q���p�w�u�~�y�u �r���u�}�u�~�y
    TIMER_MAX
} TIMERTYPE;

// �P�����y �{ ���u�{���������p�} ���p�z�}�u���p
static const char* TIMER_TEXTURES[TIMER_MAX] =
{
    "data\\TEXTURE\\Time.png",  // �S�u�{���� "Time: "
    "data\\TEXTURE\\Numbers.png"  // �X�y���|�p �r���u�}�u�~�y
};

// �R�������{�������p ���p�z�}�u���p
typedef struct
{
    D3DXVECTOR3 pos;  // �P���x�y���y�� �~�p ���{���p�~�u
    float fWidth;      // �Y�y���y�~�p ���u�{����������
    float fHeight;     // �B���������p ���u�{����������
} TIMER;

// �P�����������y���� �����~�{���y�z
void InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);

#endif
