//---------------------------------------
//
//�C���^���N�g�����̒�`�E�錾[interact.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _INTERACT_H_
#define _INTERACT_H_

#include"main.h"

#define INTERACT_TEX_KEY "data\\texture\\sato\\keyboard_f_outline.png"          //�L�[�{�[�h�e�N�X�`��
#define INTERACT_TEX_JOY "data\\texture\\sato\\xbox_button_color_x_outline.png" //�R���g���[���[�e�N�X�`��
#define INTERACT_WIDTH (20.0f)                                                  //��
#define INTERACT_HEIGHT (20.0f)                                                 //����

//�C���^���N�g�^�C�v�̗񋓌^��`
typedef enum
{
	INTERACT_TYPE_KEY = 0,
	INTERACT_TYPE_JOY,
	INTERACT_TYPE_MAX
}INTERACT_TYPE;

//�C���^���N�g�\����
typedef struct
{
	D3DXVECTOR3 pos;      //�ʒu
	D3DXVECTOR3 scale;    //�傫��
	INTERACT_TYPE Type;   //�^�C�v
	D3DXMATRIX mtxWorld;  //�}�g���b�N�X
	bool bUse;            //�g�p
}Interact;

void InitInteract(void);                              //����������
void UninitInteract(void);                            //�I������
void UpdateInteract(void);                            //�X�V����
void DrawInteract(void);                              //�`�揈��
void SetInteract(D3DXVECTOR3 pos, D3DXVECTOR3 scale); //�ݒ�
void EndInteract(void);                               //�j��
void SetInteractType(INTERACT_TYPE Type);             //�^�C�v�ύX

#endif _INTERACT_H_