//---------------------------------------
//
// アイテム処理の定義・宣言[item.h]
// Author fuma sato
//
//---------------------------------------

#ifndef _ITEM_H_
#define _ITEM_H_

#include"main.h"
#include"game.h"

#define IMANAGER_FILE "data\\txt\\sato\\itemManager.txt"
#define ITEM_FILE   "data\\txt\\sato\\Item.txt"

#define ITEM_TUTO_FILE   "data\\txt\\misaki\\tutorialitem000.txt"

#define ITEM_MAX (32)					// 最大数
#define ITEM_SUBSET_MAX (2)             // サブセット数
#define ITEM_TEXTURE_MAX (2)			// テクスチャ数
#define ITEM_SCALE_MAX (20.0f)			// 大きさの最大
#define ITEM_SCALE_MIN (0.5f)			// 大きさの最小
#define ITEM_TRIGGER_SPACE (200.0f)		// 取得可能範囲
#define ITEMUI_TEXTUREW_MAX (90.0f)	// アイテムUIの横幅			misaki
#define ITEMUI_TEXTUREH_MAX (100.0f)	// アイテムUIの縦幅			misaki
#define ITEMUI_DISTANCE_MAX (8.0f)		// アイテムUI同士の距離		misaki

#define ITYPE_TUTO_MAX (0)              // チュートリアルのアイテム数

// アイテムUIの列挙型定義
typedef enum
{
	ITEMUITYPE_FRAME0 = 0,
	ITEMUITYPE_FRAME1,
	ITEMUITYPE_FRAME2,
	ITEMUITYPE_ITEM0,
	ITEMUITYPE_ITEM1,
	ITEMUITYPE_ITEM2,
	ITEMUITYPE_MAX
}ItemUIType;

// アイテムタイプの列挙型定義
typedef enum
{
	ITYPE_1=0,
	ITYPE_2,
	ITYPE_3,
	ITYPE_MAX
}ITYPE;

// アイテムUIの列挙型にテクスチャ名を代入する
static const char* ITEM_TEXTURE[ITEMUITYPE_MAX] =
{
	"data\\texture\\misaki\\Unknown_Items.png",
	"data\\texture\\misaki\\Unknown_Items.png",
	"data\\texture\\misaki\\Unknown_Items.png",
	"data\\texture\\misaki\\Colored_Items.png",
	"data\\texture\\misaki\\Colored_Items.png",
	"data\\texture\\misaki\\Colored_Items.png",
};

// アイテムモデル構造体
typedef struct
{
	String Pass;                                    // ファイルパスの格納
	LPD3DXMESH pMesh;                               // メッシュ
	LPD3DXBUFFER pBuffMat;                          // マテリアル
	DWORD dwNumMat;                                 // マテリアル数
	int TexIdx[ITEM_SUBSET_MAX];                  //マテリアルインデックス
	D3DXVECTOR3 vtxMin;                             // 最小
	D3DXVECTOR3 vtxMax;                             // 最大
	int nNumVtx;                                    // 頂点数
	DWORD sizeFVF;                                  // サイズ
	BYTE* pVtxBuff;                                 // バッファのポインタ
}ItemModel;

// アイテムマネージャー構造体
typedef struct
{
	int ItemNum;						            // 読み込むファイル数
	ItemModel ItemModel[ITYPE_MAX];		            // ファイルの格納
	LPDIRECT3DTEXTURE9 apTexture[ITEM_TEXTURE_MAX]; // テクスチャ
}ItemManager;

// アイテムUIの構造体
typedef struct
{
	D3DXVECTOR3 UIpos;	// アイテムUIの位置
	D3DCOLOR UIcol;		// アイテムUIの色
	float fWidth;		// アイテムUIの横幅
	float fHeight;		// アイテムUIの縦幅
	bool bUse;			// アイテムを所持しているかどうか
}ItemUI;

// アイテム構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	float fLength;			// 長さ
	D3DXVECTOR3 scale;		// 大きさ
	D3DXMATRIX mtxWorld;	// マトリックス
	int nIdxShadow;			// 影
	int nRadarIdx;			// レーダーのインデックス
	ITYPE Type;				// タイプ識別子
	bool bAlpha;			// 透明
	bool bUse;				// 使用
}Item;

void InitItem(void);															// 初期化処理
void UninitItem(void);															// 終了処理
void UpdateItem(void);															// 更新処理
void DrawItem(void);															// 描画処理
void DrawItemUI(void);															// アイテムUIの描画処理 misaki
void SetItemManager(ItemManager ItemManager);									// 読み込んだファイル情報を格納する
int SetItem(ITYPE Type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);	// アイテムを設置する
Item* GetItem(void);															// アイテムの取得
int GetItemNum(void);															// 種類数の取得
bool TriggerItem(D3DXVECTOR3 pos, Item** pItem);								// 当たり判定
char* GetItemName(int nNumber);													// ファイルパスの取得(Debug表示用)

void LoadItemManager(void);														// ファイル情報読み込み
void LoadItem(void);															// 設置情報読み込み
void SaveItem(void);															// 設置情報書き出し
																				   
void UpdateItemEdit(D3DXVECTOR3 Epos, D3DXVECTOR3 Erot);						// アイテムエディター
int GetInumber(void);															// 現在のXファイルナンバー
int GetIDelnumber(void);														// 現在のデリートナンバー

void DisplayItem(bool bDisp,int nType);											// アイテムUIを表示する処理 misaki

#endif _ITEM_H_