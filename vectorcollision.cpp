//---------------------------------------
//
//ベクトルの当たり判定処理の定義・宣言[vectorcollision.h]
//Author fuma sato
//
//---------------------------------------
#include "vectorcollision.h"

//------------------
//押し戻し
//------------------
void VectorCollision(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos)
{
	D3DXVECTOR2 Staticvec = {}, Collvec = {}, CollOldvec = {}, Movingvec = {}, Norvec = {}, Dovec = {}, Hit = {};
	float StaticCross, CollCross;

	Staticvec = StaticEndpos - StaticStartpos;	//ベクトル

	Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
	D3DXVec2Normalize(&Norvec, &Norvec);

	// 体分の計算
	D3DXVECTOR2 Pos = Movingpos + -Norvec * MovingWidth, PosOld = MovingposOld + -Norvec * MovingWidth;

	Collvec = Pos - StaticStartpos;		        //壁に対するプレイヤーのベクトル
	CollOldvec = PosOld - StaticStartpos;		//壁に対するプレイヤーの旧ベクトル
	Movingvec = Pos - PosOld;			        //プレイヤーの移動ベクトル

	if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) <= 0.0f && (Staticvec.y * CollOldvec.x) - (Staticvec.x * CollOldvec.y) >= 0.0f)
	{//壁の外側
		StaticCross = (Staticvec.y * Movingvec.x) - (Staticvec.x * Movingvec.y);
		CollCross = (Collvec.y * Movingvec.x) - (Collvec.x * Movingvec.y);
		CollCross /= StaticCross;
		if (CollCross >= -0.05f && CollCross < 1.05f)
		{//壁の範囲
			Hit = StaticStartpos + Staticvec * CollCross;
			Movingvec = Pos - Hit;//プレイヤーの移動ベクトル
			Dovec = Norvec * ((-Movingvec.x * Norvec.x) + (-Movingvec.y * Norvec.y));
			Movingpos += Dovec * 1.1f;
		}
	}
}

//------------------
//真偽
//------------------
bool __stdcall VectorTrigger(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos)
{
	D3DXVECTOR2 Staticvec = {}, Collvec = {}, CollOldvec = {}, Movingvec = {}, Norvec = {};
	float StaticCross, CollCross;

	Staticvec = StaticEndpos - StaticStartpos;	//ベクトル

	Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
	D3DXVec2Normalize(&Norvec, &Norvec);

	// 体分の計算
	D3DXVECTOR2 Pos = Movingpos + -Norvec * MovingWidth, PosOld = MovingposOld + -Norvec * MovingWidth;

	Collvec = Pos - StaticStartpos;		        //壁に対するプレイヤーのベクトル
	CollOldvec = MovingposOld - StaticStartpos;		//壁に対するプレイヤーの旧ベクトル
	Movingvec = Pos - PosOld;			        //プレイヤーの移動ベクトル

	if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) <= 0.0f && (Staticvec.y * CollOldvec.x) - (Staticvec.x * CollOldvec.y) >= 0.0f)
	{//壁の外側
		StaticCross = (Staticvec.y * Movingvec.x) - (Staticvec.x * Movingvec.y);
		CollCross = (Collvec.y * Movingvec.x) - (Collvec.x * Movingvec.y);
		CollCross /= StaticCross;
		if (CollCross >= 0.0f && CollCross < 1.0f)
		{//壁の範囲
			return true;
		}
	}

	return false;
}

//------------------
//反射
//------------------
bool VectorReflection(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, D3DXVECTOR2& Move, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos)
{
	D3DXVECTOR2 Staticvec = {}, Collvec = {}, CollOldvec = {}, Movingvec = {}, Norvec = {}, Dovec = {}, Hit = {};
	float StaticCross, CollCross;

	Staticvec = StaticEndpos - StaticStartpos;	//ベクトル

	Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
	D3DXVec2Normalize(&Norvec, &Norvec);

	// 体分の計算
	D3DXVECTOR2 Pos = Movingpos + -Norvec * MovingWidth, PosOld = MovingposOld + -Norvec * MovingWidth;

	Collvec = Pos - StaticStartpos;		    //壁に対するプレイヤーのベクトル
	CollOldvec = PosOld - StaticStartpos;		//壁に対するプレイヤーの旧ベクトル
	Movingvec = Pos - PosOld;			//プレイヤーの移動ベクトル

	if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) > 0.0f && (Staticvec.y * CollOldvec.x) - (Staticvec.x * CollOldvec.y) <= 0.0f)
	{//壁の外側
		StaticCross = (Staticvec.y * Movingvec.x) - (Staticvec.x * Movingvec.y);
		CollCross = (Collvec.y * Movingvec.x) - (Collvec.x * Movingvec.y);
		CollCross /= StaticCross;
		if (CollCross >= -0.05f && CollCross < 1.05f)
		{//壁の範囲
			Hit = StaticStartpos + Staticvec * CollCross;
			Movingvec = Pos - Hit;//プレイヤーの移動ベクトル
			Dovec = Norvec * ((Movingvec.x * Norvec.x) + (Movingvec.y * Norvec.y));
			Movingpos -= Dovec * 2.0f;
			Move -= Dovec * 2.0f;

			return true;
		}
	}

	return false;
}

//----------
//当たり判定
//----------
bool VectorInside(D3DXVECTOR2& Movingpos, float MovingWidth, D3DXVECTOR2* pPos)
{
	D3DXVECTOR2 Staticvec = {}, Collvec = {}, Norvec = {};

	Staticvec = pPos[1] - pPos[0];	//ベクトル

	Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
	D3DXVec2Normalize(&Norvec, &Norvec);

	// 体分の計算
	D3DXVECTOR2 Pos = Movingpos + Norvec * MovingWidth;

	Collvec = Pos - pPos[0];		        //壁に対するプレイヤーのベクトル

	if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) >= 0.0f)
	{//壁の外側
		Staticvec = pPos[2] - pPos[1];	//ベクトル

		Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
		D3DXVec2Normalize(&Norvec, &Norvec);

		// 体分の計算
		D3DXVECTOR2 Pos = Movingpos + Norvec * MovingWidth;

		Collvec = Pos - pPos[1];		        //壁に対するプレイヤーのベクトル

		if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) >= 0.0f)
		{//壁の外側
			Staticvec = pPos[3] - pPos[2];	//ベクトル

			Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
			D3DXVec2Normalize(&Norvec, &Norvec);

			// 体分の計算
			D3DXVECTOR2 Pos = Movingpos + Norvec * MovingWidth;

			Collvec = Pos - pPos[2];		        //壁に対するプレイヤーのベクトル

			if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) >= 0.0f)
			{//壁の外側
				Staticvec = pPos[0] - pPos[3];	//ベクトル

				Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
				D3DXVec2Normalize(&Norvec, &Norvec);

				// 体分の計算
				D3DXVECTOR2 Pos = Movingpos + Norvec * MovingWidth;

				Collvec = Pos - pPos[3];		        //壁に対するプレイヤーのベクトル

				if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) >= 0.0f)
				{//壁の外側
					return true;
				}
			}
		}
	}
	return false;
}