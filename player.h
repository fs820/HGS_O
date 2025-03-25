//---------------------------------------
//
//モデル表示処理の定義・宣言[player.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"main.h"
#include"model.h"
#include "object.h"

#define PLAYER_BODY_NAME "data\\MODEL\\Playermodel\\00_Player_Body.x"
#define PLAYER_HEAD_NAME "data\\MODEL\\Playermodel\\01_Player_Head.x"
#define PLAYER_RIGHTARM_NAME "data\\MODEL\\Playermodel\\02_Player_RightArm.x"
#define PLAYER_RIGHTHAND_NAME "data\\MODEL\\Playermodel\\03_Player_RightHand.x"
#define PLAYER_LEFTARM_NAME "data\\MODEL\\Playermodel\\04_Player_LeftArm.x"
#define PLAYER_LEFTHAND_NAME "data\\MODEL\\Playermodel\\05_Player_LeftHand.x"
#define PLAYER_RIGHTLEG_NAME "data\\MODEL\\Playermodel\\06_Player_RightLeg.x"
#define PLAYER_RIGHTFOOT_NAME "data\\MODEL\\Playermodel\\07_Player_RightFoot.x"
#define PLAYER_LEFTLEG_NAME "data\\MODEL\\Playermodel\\08_Player_LeftLeg.x"
#define PLAYER_LEFTFOOT_NAME "data\\MODEL\\Playermodel\\09_Player_LeftFoot.x"
#define PLAYER_HAT_NAME "data\\MODEL\\Playermodel\\10_Player_Hat.x"
#define MAX_MODEL (16)
#define NUM_MODEL (11)
#define MAX_KEY (16)
#define NUM_KEY (5)
#define MAX_MOTION (16)
#define NUM_MOTION (5)
#define SPEED (0.2f)
#define SPEED_DEF (0.0f)
#define JUMP (2.0f)
#define JUMP_INA (0.9f)
#define PLAYER_INA (0.1f)
#define ROT_SPEED (0.1f)
#define SCALE_SPEED (0.2f)
#define SCALE_MIN (0.05f)
#define SCALE_MAX (1.0f)
#define START_Z (0.0f)
#define START_X (0.0f)
#define PLAYER_LIFE (1000)
#define BLEND_FRAME (10.0f)
#define PLAYER_SIZE (0.5f)

//プレイヤー状態の列挙型定義
typedef enum
{
	PLAYERSTATE_APPEAR = 0,//復活状態
	PLAYERSTATE_NORMAL,//通常
	PLAYERSTATE_DAMAGE,//ダメージ
	PLAYERSTATE_DIE,//死
	PLAYERSTATE_MAX//数
}PLAYERSTATE;

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_MOVE,
	MOTIONTYPE_ACTION,
	MOTIONTYPE_JUMP,
	MOTIONTYPE_LANDING,
	MOTIONTYPE_MAX
}MOTIONTYPE;

//キーの構造体
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//キー情報の構造体
typedef struct
{
	int nFrame;
	KEY aKey[MAX_MODEL];
}KEY_INFO;

typedef struct
{
	bool bLoop;
	int nNumKey;
	KEY_INFO aKeyInfo[MAX_KEY];
}MOTION_INFO;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 scale;
	bool bJump;
	int nLife;
	PLAYERSTATE state;
	D3DXMATRIX mtxWorld;
	int nIdxShadow;
	int nIdxLife;
	Model aModel[MAX_MODEL];
	int nNumModel;
	MOTION_INFO aMotionInfo[MAX_MOTION];
	int nNumMotion;
	MOTIONTYPE motionType;
	bool bLoopMotion;
	int nNumKey;
	int nKey;
	int nCounterMotion;
	Object* pObject;
	bool bUse;
}Player;

void InitPlayer(void);//ポリゴンの初期化処理
void UninitPlayer(void);//ポリゴンの終了処理
void UpdatePlayer(void);//ポリゴンの更新処理
void DrawPlayer(void);//ポリゴンの描画処理
Player* GetPlayer(void);

void UpdateMotion(void);
#endif _PLAYER_H_