//---------------------------------------
//
//弾表示処理[particle.cpp]
//Author fuma sato
//
//---------------------------------------

#include"particle.h"
#include"effect.h"

//弾構造体
typedef struct
{
	D3DXVECTOR2 pos;//位置
	int nLife;//寿命
	bool bUse;//使用しているかどうか
}PARTICLE;

//グローバル
PARTICLE g_aParticle[MAX_PARTICLE];//弾の情報

//-----------------
//弾の初期化処理
//-----------------
void InitParticle(void)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		g_aParticle[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_aParticle[i].nLife = PARTICLE_LIFE;
		g_aParticle[i].bUse = false;//使用していない状態にする
	}
}

//----------------
//弾の終了処理
//----------------
void UninitParticle(void)
{

}

//----------------
//弾の更新処理
//----------------
void UpdateParticle(void)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (g_aParticle[i].bUse == true)
		{//弾が使用されている

			for (int i2 = 0; i2 < PARTICLE_NUM; i2++)
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f), move = D3DXVECTOR2(0.0f, 0.0f), dir = D3DXVECTOR2(0.0f, 0.0f);
				D3DCOLOR col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
				float fangle = 0.0f, fspeed = 0.0f, fscale = 0.0f, length = 0.0f;
				int nLife=0;
				pos=g_aParticle[i].pos;
				fangle = (float)(rand() % 629 - 314) / 100.0f;
				fspeed = (float)(rand() % 100) / 10.0f + 1.0f;
				dir.x = (float)(rand() % 201 - 100) / 100.0f;
				dir.y = (float)(rand() % 201 - 100) / 100.0f;
				length = sqrtf(dir.x * dir.x + dir.y * dir.y);
				dir.x /= length;
				dir.y /= length;
				move.x = dir.x * fspeed;
				move.y = dir.y * fspeed;
				col = D3DXCOLOR((float)(rand() % 101) / 100.0f, (float)(rand() % 101) / 100.0f, (float)(rand() % 101) / 100.0f, (float)(rand() % 51) / 100.0f);
				nLife = g_aParticle[i].nLife;

				SetEffect(pos, move, col, nLife, EFFECT_TYPE_NORMAL);
			}

			g_aParticle[i].nLife--;

			if (g_aParticle[i].nLife <= 0)
			{
				g_aParticle[i].bUse = false;
			}
		}
	}
}

//-------------------
//発通常弾
//-------------------
void SetParticle(D3DXVECTOR2 pos)
{
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		if (g_aParticle[i].bUse == false)
		{//弾が使用されていない
			g_aParticle[i].pos = pos;
			g_aParticle[i].nLife = PARTICLE_LIFE;
			g_aParticle[i].bUse = true;
			break;
		}
	}
}