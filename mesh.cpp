//---------------------------------------
//
//バッファ生成処理[mesh.cpp]
//Author fuma sato
//
//---------------------------------------
#include"mesh.h"

//----------------------------------------------------
//2DのYX軸の頂点バッファを生成する
//----------------------------------------------------
HRESULT SetVertex2D(LPDIRECT3DVERTEXBUFFER9* ppVtxBuff, int StartIdx, int BuffMax, int Ynum, int Xnum, D3DXVECTOR2 pos, float Width, float Height, D3DXCOLOR col, float TexWidth, float TexHeight)
{
	HRESULT hr; //成功確認
	VERTEX_2D* pVtx;//頂点情報ポインタ
	int nCnt, nCnt2, nCnt3; //カウント変数

	//頂点バッファをロック
	hr = (*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
	if (FAILED(hr))
	{
		return hr;
	}

	pVtx += (Xnum + 1) * (Ynum + 1) * StartIdx; //指定のインデックスに移動

	for (nCnt = 0; nCnt < BuffMax; nCnt++)
	{//指定数ループ
		for (nCnt2 = 0; nCnt2 < Ynum + 1; nCnt2++)
		{//1枚分のZ軸のループ
			for (nCnt3 = 0; nCnt3 < Xnum + 1; nCnt3++)
			{//1枚分のX軸のループ
				//座標設定
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].pos = D3DXVECTOR3(pos.x - Width * 0.5f + (Width / Xnum) * nCnt3, pos.y - Height * 0.5f + (Height / Ynum) * nCnt2, 0.0f);

				//カラー
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].rhw = 1.0f;

				//カラー
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].col = col;

				//テクスチャ
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].tex = D3DXVECTOR2(((Width / TexWidth) / Xnum) * nCnt3, ((Height / TexHeight) / Ynum) * nCnt2);
			}
		}
		pVtx += (Xnum + 1) * (Ynum + 1);
	}

	//頂点バッファをアンロック
	hr = (*ppVtxBuff)->Unlock();

	return hr;
}

//----------------------------------------------------
//3DのYX軸の頂点バッファを生成する
//----------------------------------------------------
HRESULT SetVertex3DYX(LPDIRECT3DVERTEXBUFFER9* ppVtxBuff, int StartIdx, int BuffMax, int Ynum, int Xnum, float Width, float Height, D3DXVECTOR3 nor, D3DXCOLOR col, float TexWidth, float TexHeight, bool PosSenter, bool TexMalti)
{
	HRESULT hr; //成功確認
	int nCnt, nCnt2, nCnt3; //カウント変数

	if (TexMalti)
	{
		VERTEX_3D_MULTI* pVtx;//頂点情報ポインタ

		//頂点バッファをロック
		hr = (*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
		if (FAILED(hr))
		{
			return hr;
		}

		pVtx += (Xnum + 1) * (Ynum + 1) * StartIdx; //指定のインデックスに移動

		for (nCnt = 0; nCnt < BuffMax; nCnt++)
		{//指定数ループ
			for (nCnt2 = 0; nCnt2 < Ynum + 1; nCnt2++)
			{//1枚分のZ軸のループ
				for (nCnt3 = 0; nCnt3 < Xnum + 1; nCnt3++)
				{//1枚分のX軸のループ
					//座標設定
					if (PosSenter)
					{
						pVtx[nCnt2 * (Xnum + 1) + nCnt3].pos = D3DXVECTOR3(-Width * 0.5f + (Width / Xnum) * nCnt3, Height * 0.5f - (Height / Ynum) * nCnt2, 0.0f);
					}
					else
					{
						pVtx[nCnt2 * (Xnum + 1) + nCnt3].pos = D3DXVECTOR3(-Width * 0.5f + (Width / Xnum) * nCnt3, Height - (Height / Ynum) * nCnt2, 0.0f);
					}

					//nor
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].nor = nor;

					//カラー
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].col = col;

					//テクスチャ
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].tex1 = D3DXVECTOR2(((Width / TexWidth) / Xnum) * nCnt3, ((Height / TexHeight) / Ynum) * nCnt2);

					//テクスチャ
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].tex2 = D3DXVECTOR2(((Width / TexWidth) / Xnum) * nCnt3, ((Height / TexHeight) / Ynum) * nCnt2);
				}
			}
			pVtx += (Xnum + 1) * (Ynum + 1);
		}

		//頂点バッファをアンロック
		hr = (*ppVtxBuff)->Unlock();
	}
	else
	{
		VERTEX_3D* pVtx;//頂点情報ポインタ

		//頂点バッファをロック
		hr = (*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
		if (FAILED(hr))
		{
			return hr;
		}

		pVtx += (Xnum + 1) * (Ynum + 1) * StartIdx; //指定のインデックスに移動

		for (nCnt = 0; nCnt < BuffMax; nCnt++)
		{//指定数ループ
			for (nCnt2 = 0; nCnt2 < Ynum + 1; nCnt2++)
			{//1枚分のZ軸のループ
				for (nCnt3 = 0; nCnt3 < Xnum + 1; nCnt3++)
				{//1枚分のX軸のループ
					//座標設定
					if (PosSenter)
					{
						pVtx[nCnt2 * (Xnum + 1) + nCnt3].pos = D3DXVECTOR3(-Width * 0.5f + (Width / Xnum) * nCnt3, Height * 0.5f - (Height / Ynum) * nCnt2, 0.0f);
					}
					else
					{
						pVtx[nCnt2 * (Xnum + 1) + nCnt3].pos = D3DXVECTOR3(-Width * 0.5f + (Width / Xnum) * nCnt3, Height - (Height / Ynum) * nCnt2, 0.0f);
					}

					//nor
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].nor = nor;

					//カラー
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].col = col;

					//テクスチャ
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].tex = D3DXVECTOR2(((Width / TexWidth) / Xnum) * nCnt3, ((Height / TexHeight) / Ynum) * nCnt2);
				}
			}
			pVtx += (Xnum + 1) * (Ynum + 1);
		}

		//頂点バッファをアンロック
		hr = (*ppVtxBuff)->Unlock();
	}

	return hr;
}

//----------------------------------------------------
//3DのZX軸の頂点バッファを生成する
//----------------------------------------------------
HRESULT SetVertex3DZX(LPDIRECT3DVERTEXBUFFER9* ppVtxBuff, int StartIdx, int BuffMax, int Znum, int Xnum, float Width, float Depth, D3DXVECTOR3 nor, D3DXCOLOR col, float TexWidth, float TexDepth)
{
	HRESULT hr; //成功確認
	VERTEX_3D* pVtx;//頂点情報ポインタ
	int nCnt, nCnt2, nCnt3; //カウント変数

	//頂点バッファをロック
	hr = (*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
	if (FAILED(hr))
	{
		return hr;
	}

	pVtx += (Xnum + 1) * (Znum + 1) * StartIdx; //指定のインデックスに移動

	for (nCnt = 0; nCnt < BuffMax; nCnt++)
	{//指定数ループ
		for (nCnt2 = 0; nCnt2 < Znum + 1; nCnt2++)
		{//1枚分のZ軸のループ
			for (nCnt3 = 0; nCnt3 < Xnum + 1; nCnt3++)
			{//1枚分のX軸のループ
				//座標設定
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].pos = D3DXVECTOR3(-Width * 0.5f + (Width / Xnum) * nCnt3, 0.0f, Depth * 0.5f - (Depth / Znum) * nCnt2);

				//nor
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].nor = nor;

				//カラー
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].col = col;

				//テクスチャ
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].tex = D3DXVECTOR2(((Width / TexWidth) / Xnum) * nCnt3, ((Depth / TexDepth) / Znum) * nCnt2);
			}
		}
		pVtx += (Xnum + 1) * (Znum + 1);
	}

	//頂点バッファをアンロック
	hr = (*ppVtxBuff)->Unlock();

	return hr;
}

//----------------------------------------------------
//インデックスバッファを生成する
//----------------------------------------------------
HRESULT SetIndex(LPDIRECT3DINDEXBUFFER9* ppIdxBuff, int YZnum, int Xnum)
{
	HRESULT hr; //成功確認
	WORD* pIdx;
	int nCnt;

	hr = (*ppIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);
	if (FAILED(hr))
	{
		return hr;
	}

	for (nCnt = 0; nCnt < (((Xnum + 1) * 2) * YZnum + (YZnum - 1) * 2) - (YZnum - 1) * 2; nCnt++)
	{//インデックス数回す
		if (nCnt % ((Xnum + 1) * 2) == 0 && nCnt != 0)
		{
			//インデックス指定
			pIdx[nCnt - 2 + ((nCnt / ((Xnum + 1) * 2)) * 2)] = (Xnum + 1) - (Xnum + 1) * ((nCnt - 1) % 2) + ((nCnt - 1) / 2);
			//インデックス指定
			pIdx[nCnt - 1 + ((nCnt / ((Xnum + 1) * 2)) * 2)] = (Xnum + 1) - (Xnum + 1) * (nCnt % 2) + (nCnt / 2);
		}

		//インデックス指定
		pIdx[nCnt + ((nCnt / ((Xnum + 1) * 2)) * 2)] = (Xnum + 1) - (Xnum + 1) * (nCnt % 2) + (nCnt / 2);
	}

	hr = (*ppIdxBuff)->Unlock();

	return hr;
}