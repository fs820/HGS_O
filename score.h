//---------------------------------------
//
//�X�R�A�����̒�`�E�錾[score.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _SCORE_H_
#define _SCORE_H_

#include"main.h"

#define SCORE_MAX (5)//����
#define U_MAX_S (11)//�e�N�X�`����(��)
#define V_MAX_S (1)//�e�N�X�`����(�c)
#define SCORE_WIDTH (160.0f)//�T�C�Y
#define SCORE_HEIGHT (64.0f)//�T�C�Y
#define DIGIT (10)//�i��

extern int totalScore;//���v�X�R�A

// �T���L���[�w�i�̗�
typedef enum
{
	SCORE_UI = 0,
	SCORE_UI_ONE,
	SCORE_UI_TWO,
	SCORE_UI_THREE,
	SCORE_UI_MAX
}SCORETYPE;

// �񋓌^�Ƀe�N�X�`��������
static const char* SCORE_TEXTURES[SCORE_UI_MAX] =
{
	"data\\TEXTURE\\Score.png",		
	"data\\TEXTURE\\Numbers.png",		
	"data\\TEXTURE\\Numbers.png",
	"data\\TEXTURE\\Numbers.png",		
};

// �T���L���[���
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	float fWidth;			// ��
	float fHeight;			// ����
}THANKYOU;

void InitScore(void);
void UninitScore(void);
void UpdateScore(int score);
void DrawScore(void);
int Digit(int nData, int nDigit);//��������
void AddScore(int scoreToAdd);
void SaveScore(int score);

#endif _SCORE_H_