#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

// �T���L���[�w�i�̗�
typedef enum
{
	BACKGROUND = 0,
	MOVING_BACKGROUND,
	TITLE_BUTTON,
	TITLE_MAX
}THANKYOUTYPE;

// �񋓌^�Ƀe�N�X�`��������
static const char* THANKYOU_BACKGROUND[TITLE_MAX] =
{
	"data\\TEXTURE\\Bg new.png",		// Spaceship Background Move
	"data\\TEXTURE\\buildings.png",		// Girl Background
	"data\\TEXTURE\\TAP TO START.png",		// Logo
};

// �T���L���[���
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	float fWidth;			// ��
	float fHeight;			// ����
}THANKYOU;

//�v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
#endif