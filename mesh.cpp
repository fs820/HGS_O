//---------------------------------------
//
//�o�b�t�@��������[mesh.cpp]
//Author fuma sato
//
//---------------------------------------
#include"mesh.h"

//----------------------------------------------------
//2D��YX���̒��_�o�b�t�@�𐶐�����
//----------------------------------------------------
HRESULT SetVertex2D(LPDIRECT3DVERTEXBUFFER9* ppVtxBuff, int StartIdx, int BuffMax, int Ynum, int Xnum, D3DXVECTOR2 pos, float Width, float Height, D3DXCOLOR col, float TexWidth, float TexHeight)
{
	HRESULT hr; //�����m�F
	VERTEX_2D* pVtx;//���_���|�C���^
	int nCnt, nCnt2, nCnt3; //�J�E���g�ϐ�

	//���_�o�b�t�@�����b�N
	hr = (*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
	if (FAILED(hr))
	{
		return hr;
	}

	pVtx += (Xnum + 1) * (Ynum + 1) * StartIdx; //�w��̃C���f�b�N�X�Ɉړ�

	for (nCnt = 0; nCnt < BuffMax; nCnt++)
	{//�w�萔���[�v
		for (nCnt2 = 0; nCnt2 < Ynum + 1; nCnt2++)
		{//1������Z���̃��[�v
			for (nCnt3 = 0; nCnt3 < Xnum + 1; nCnt3++)
			{//1������X���̃��[�v
				//���W�ݒ�
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].pos = D3DXVECTOR3(pos.x - Width * 0.5f + (Width / Xnum) * nCnt3, pos.y - Height * 0.5f + (Height / Ynum) * nCnt2, 0.0f);

				//�J���[
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].rhw = 1.0f;

				//�J���[
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].col = col;

				//�e�N�X�`��
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].tex = D3DXVECTOR2(((Width / TexWidth) / Xnum) * nCnt3, ((Height / TexHeight) / Ynum) * nCnt2);
			}
		}
		pVtx += (Xnum + 1) * (Ynum + 1);
	}

	//���_�o�b�t�@���A�����b�N
	hr = (*ppVtxBuff)->Unlock();

	return hr;
}

//----------------------------------------------------
//3D��YX���̒��_�o�b�t�@�𐶐�����
//----------------------------------------------------
HRESULT SetVertex3DYX(LPDIRECT3DVERTEXBUFFER9* ppVtxBuff, int StartIdx, int BuffMax, int Ynum, int Xnum, float Width, float Height, D3DXVECTOR3 nor, D3DXCOLOR col, float TexWidth, float TexHeight, bool PosSenter, bool TexMalti)
{
	HRESULT hr; //�����m�F
	int nCnt, nCnt2, nCnt3; //�J�E���g�ϐ�

	if (TexMalti)
	{
		VERTEX_3D_MULTI* pVtx;//���_���|�C���^

		//���_�o�b�t�@�����b�N
		hr = (*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
		if (FAILED(hr))
		{
			return hr;
		}

		pVtx += (Xnum + 1) * (Ynum + 1) * StartIdx; //�w��̃C���f�b�N�X�Ɉړ�

		for (nCnt = 0; nCnt < BuffMax; nCnt++)
		{//�w�萔���[�v
			for (nCnt2 = 0; nCnt2 < Ynum + 1; nCnt2++)
			{//1������Z���̃��[�v
				for (nCnt3 = 0; nCnt3 < Xnum + 1; nCnt3++)
				{//1������X���̃��[�v
					//���W�ݒ�
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

					//�J���[
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].col = col;

					//�e�N�X�`��
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].tex1 = D3DXVECTOR2(((Width / TexWidth) / Xnum) * nCnt3, ((Height / TexHeight) / Ynum) * nCnt2);

					//�e�N�X�`��
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].tex2 = D3DXVECTOR2(((Width / TexWidth) / Xnum) * nCnt3, ((Height / TexHeight) / Ynum) * nCnt2);
				}
			}
			pVtx += (Xnum + 1) * (Ynum + 1);
		}

		//���_�o�b�t�@���A�����b�N
		hr = (*ppVtxBuff)->Unlock();
	}
	else
	{
		VERTEX_3D* pVtx;//���_���|�C���^

		//���_�o�b�t�@�����b�N
		hr = (*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
		if (FAILED(hr))
		{
			return hr;
		}

		pVtx += (Xnum + 1) * (Ynum + 1) * StartIdx; //�w��̃C���f�b�N�X�Ɉړ�

		for (nCnt = 0; nCnt < BuffMax; nCnt++)
		{//�w�萔���[�v
			for (nCnt2 = 0; nCnt2 < Ynum + 1; nCnt2++)
			{//1������Z���̃��[�v
				for (nCnt3 = 0; nCnt3 < Xnum + 1; nCnt3++)
				{//1������X���̃��[�v
					//���W�ݒ�
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

					//�J���[
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].col = col;

					//�e�N�X�`��
					pVtx[nCnt2 * (Xnum + 1) + nCnt3].tex = D3DXVECTOR2(((Width / TexWidth) / Xnum) * nCnt3, ((Height / TexHeight) / Ynum) * nCnt2);
				}
			}
			pVtx += (Xnum + 1) * (Ynum + 1);
		}

		//���_�o�b�t�@���A�����b�N
		hr = (*ppVtxBuff)->Unlock();
	}

	return hr;
}

//----------------------------------------------------
//3D��ZX���̒��_�o�b�t�@�𐶐�����
//----------------------------------------------------
HRESULT SetVertex3DZX(LPDIRECT3DVERTEXBUFFER9* ppVtxBuff, int StartIdx, int BuffMax, int Znum, int Xnum, float Width, float Depth, D3DXVECTOR3 nor, D3DXCOLOR col, float TexWidth, float TexDepth)
{
	HRESULT hr; //�����m�F
	VERTEX_3D* pVtx;//���_���|�C���^
	int nCnt, nCnt2, nCnt3; //�J�E���g�ϐ�

	//���_�o�b�t�@�����b�N
	hr = (*ppVtxBuff)->Lock(0, 0, (void**)&pVtx, 0);
	if (FAILED(hr))
	{
		return hr;
	}

	pVtx += (Xnum + 1) * (Znum + 1) * StartIdx; //�w��̃C���f�b�N�X�Ɉړ�

	for (nCnt = 0; nCnt < BuffMax; nCnt++)
	{//�w�萔���[�v
		for (nCnt2 = 0; nCnt2 < Znum + 1; nCnt2++)
		{//1������Z���̃��[�v
			for (nCnt3 = 0; nCnt3 < Xnum + 1; nCnt3++)
			{//1������X���̃��[�v
				//���W�ݒ�
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].pos = D3DXVECTOR3(-Width * 0.5f + (Width / Xnum) * nCnt3, 0.0f, Depth * 0.5f - (Depth / Znum) * nCnt2);

				//nor
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].nor = nor;

				//�J���[
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].col = col;

				//�e�N�X�`��
				pVtx[nCnt2 * (Xnum + 1) + nCnt3].tex = D3DXVECTOR2(((Width / TexWidth) / Xnum) * nCnt3, ((Depth / TexDepth) / Znum) * nCnt2);
			}
		}
		pVtx += (Xnum + 1) * (Znum + 1);
	}

	//���_�o�b�t�@���A�����b�N
	hr = (*ppVtxBuff)->Unlock();

	return hr;
}

//----------------------------------------------------
//�C���f�b�N�X�o�b�t�@�𐶐�����
//----------------------------------------------------
HRESULT SetIndex(LPDIRECT3DINDEXBUFFER9* ppIdxBuff, int YZnum, int Xnum)
{
	HRESULT hr; //�����m�F
	WORD* pIdx;
	int nCnt;

	hr = (*ppIdxBuff)->Lock(0, 0, (void**)&pIdx, 0);
	if (FAILED(hr))
	{
		return hr;
	}

	for (nCnt = 0; nCnt < (((Xnum + 1) * 2) * YZnum + (YZnum - 1) * 2) - (YZnum - 1) * 2; nCnt++)
	{//�C���f�b�N�X����
		if (nCnt % ((Xnum + 1) * 2) == 0 && nCnt != 0)
		{
			//�C���f�b�N�X�w��
			pIdx[nCnt - 2 + ((nCnt / ((Xnum + 1) * 2)) * 2)] = (Xnum + 1) - (Xnum + 1) * ((nCnt - 1) % 2) + ((nCnt - 1) / 2);
			//�C���f�b�N�X�w��
			pIdx[nCnt - 1 + ((nCnt / ((Xnum + 1) * 2)) * 2)] = (Xnum + 1) - (Xnum + 1) * (nCnt % 2) + (nCnt / 2);
		}

		//�C���f�b�N�X�w��
		pIdx[nCnt + ((nCnt / ((Xnum + 1) * 2)) * 2)] = (Xnum + 1) - (Xnum + 1) * (nCnt % 2) + (nCnt / 2);
	}

	hr = (*ppIdxBuff)->Unlock();

	return hr;
}