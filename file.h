//---------------------------------------
//
//セーブ・ロード処理の定義・宣言[file.h]
//Author fuma sato
//
//---------------------------------------

#ifndef _FILE_H_
#define _FILE_H_

#include"main.h"

#define BLOCK_FILE "data\\TXT\\Block.txt"
#define BRICK_FILE "data\\TXT\\Brick.txt"
#define SHARP_FILE "data\\TXT\\Sharp.txt"

//プロトタイプ宣言

void LoadBlock(void);
void SaveBlock(void);
void LoadBrick(void);
void SaveBrick(void);
void LoadSharp(void);
void SaveSharp(void);
void Edit(void);
#endif // _FILE_H_
