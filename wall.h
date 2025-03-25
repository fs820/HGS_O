//---------------------------------------
//
//壁処理の定義・宣言[wall.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _WALL_H_
#define _WALL_H_

#include"main.h"

#define WALL_FILE "data\\txt\\sato\\wall.txt"                        //位置保存ファイル
#define WALL_FILE_TUTORIAL "data\\txt\\misaki\\tutorialwall000.txt"  //位置保存ファイル チュートリアル
#define WALL_TEX "data\\texture\\Tutorial\\wall.jpg"			     //テクスチャ
#define WALL_MAX (512)                        //最大数
#define DISPWALL_MAX (64)                     //見える壁の最大数
#define WALL_WIDTH (1000.0f)                  //基本比率
#define WALL_HEIGHT (1000.0f)                 //基本比率
#define WALL_Z (0.0f)                         //0
#define WALL_WIDTH_DEF (1000.0f)              //テクスチャ用
#define WALL_HEIGHT_DEF (1000.0f)             //テクスチャ用
#define WALL_Z_DEF (0.0f)                     //テクスチャ用
#define WALL_XNUM (1)                         //分割数X
#define WALL_YNUM (1)                         //分割数Y
#define WALL_WIDTH_MIN (100.0f)               //最小の幅
#define WALL_WIDTH_MAX (10000.0f)             //最大の幅
#define WALL_HEIGHT_MIN (50.0f)               //最小の高さ
#define WALL_HEIGHT_MAX (5000.0f)             //最大の高さ
#define VT_MAX_WALL ((WALL_XNUM + 1) * (WALL_YNUM + 1))                 //頂点数
#define INDEX_NUM_WALL (((WALL_XNUM+1)*2)*WALL_YNUM+(WALL_YNUM-1)*2)    //インデックス数
#define POLYGON_NUM_WALL (WALL_XNUM*WALL_YNUM*2+(WALL_YNUM-1)*4)        //ポリゴン数

#define BACK_WALL_ALPHA (0.5f)

//壁のタイプ
typedef enum
{
	WTYPE_NORMAL = 0,
	WTYPE_INVISIBLE,
	WTYPE_MAX
}WALL_TYPE;

//見えない壁構造体
typedef struct
{
	D3DXVECTOR3 pos;     //位置
	D3DXVECTOR3 rot;     //回転
	D3DXMATRIX mtxWorld; //マトリックス
	float Width;         //幅
	float Height;        //高さ
	bool bAlpha;         //透明
	bool bBack;          //バックの壁
	bool bUse;           //使用
	WALL_TYPE Type;      //タイプ
}Wall;

void InitWall(void);//初期化処理
void UninitWall(void);//終了処理
void UpdateWall(void);//更新処理
void DrawWall(void);//描画処理
int SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Width, float Height, WALL_TYPE Type); //設置
Wall* GetWall(void);                                               //取得
void CollisionWall(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, float Width, float fHeight); // 当たり判定
bool TriggerWall(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, float fHeight);   // 当たり判定
void LoadWall(void); //読み込み
void SaveWall(void); //書き込み
void UpdateWallEdit(D3DXVECTOR3 Epos, D3DXVECTOR3 Erot);    //エディター

int GetWallNum(WALL_TYPE);                                               //数
int GetWallType(void);                                                   //タイプ
int GetDelWall(void);                                                    //タイプ

#endif _WALL_H_