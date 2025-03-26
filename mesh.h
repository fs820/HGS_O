//---------------------------------------
//
//バッファ生成処理の定義・宣言[mesh.h]
//Author fuma sato
//
//---------------------------------------
#ifndef _MESH_H_
#define _MESH_H_
#include"main.h"

//プロトタイプ宣言
HRESULT SetVertex2D(LPDIRECT3DVERTEXBUFFER9* ppVtxBuff, int StartIdx, int BuffMax, int Ynum, int Xnum, float Width, float Height, float rhw, D3DXCOLOR col, float TexWidth, float TexHeight);
HRESULT SetVertex3DYX(LPDIRECT3DVERTEXBUFFER9* ppVtxBuff, int StartIdx, int BuffMax, int Ynum, int Xnum, float Width, float Height, D3DXVECTOR3 nor, D3DXCOLOR col, float TexWidth, float TexHeight, bool PosSenter, bool TexMalti);
HRESULT SetVertex3DZX(LPDIRECT3DVERTEXBUFFER9* ppVtxBuff, int StartIdx, int BuffMax, int Znum, int Xnum, float Width, float Depth, D3DXVECTOR3 nor, D3DXCOLOR col, float TexWidth, float TexDepth);
HRESULT SetIndex(LPDIRECT3DINDEXBUFFER9* ppIdxBuff, int YZnum, int Xnum);
#endif //_MESH_H_