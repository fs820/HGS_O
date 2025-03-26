//---------------------------------------
//
//�x�N�g���̓����蔻�菈���̒�`�E�錾[vectorcollision.h]
//Author fuma sato
//
//---------------------------------------
#include "vectorcollision.h"

//------------------
//�����߂�
//------------------
void VectorCollision(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos)
{
	D3DXVECTOR2 Staticvec = {}, Collvec = {}, CollOldvec = {}, Movingvec = {}, Norvec = {}, Dovec = {}, Hit = {};
	float StaticCross, CollCross;

	Staticvec = StaticEndpos - StaticStartpos;	//�x�N�g��

	Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
	D3DXVec2Normalize(&Norvec, &Norvec);

	// �̕��̌v�Z
	D3DXVECTOR2 Pos = Movingpos + -Norvec * MovingWidth, PosOld = MovingposOld + -Norvec * MovingWidth;

	Collvec = Pos - StaticStartpos;		        //�ǂɑ΂���v���C���[�̃x�N�g��
	CollOldvec = PosOld - StaticStartpos;		//�ǂɑ΂���v���C���[�̋��x�N�g��
	Movingvec = Pos - PosOld;			        //�v���C���[�̈ړ��x�N�g��

	if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) <= 0.0f && (Staticvec.y * CollOldvec.x) - (Staticvec.x * CollOldvec.y) >= 0.0f)
	{//�ǂ̊O��
		StaticCross = (Staticvec.y * Movingvec.x) - (Staticvec.x * Movingvec.y);
		CollCross = (Collvec.y * Movingvec.x) - (Collvec.x * Movingvec.y);
		CollCross /= StaticCross;
		if (CollCross >= -0.05f && CollCross < 1.05f)
		{//�ǂ͈̔�
			Hit = StaticStartpos + Staticvec * CollCross;
			Movingvec = Pos - Hit;//�v���C���[�̈ړ��x�N�g��
			Dovec = Norvec * ((-Movingvec.x * Norvec.x) + (-Movingvec.y * Norvec.y));
			Movingpos += Dovec * 1.1f;
		}
	}
}

//------------------
//�^�U
//------------------
bool __stdcall VectorTrigger(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos)
{
	D3DXVECTOR2 Staticvec = {}, Collvec = {}, CollOldvec = {}, Movingvec = {}, Norvec = {};
	float StaticCross, CollCross;

	Staticvec = StaticEndpos - StaticStartpos;	//�x�N�g��

	Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
	D3DXVec2Normalize(&Norvec, &Norvec);

	// �̕��̌v�Z
	D3DXVECTOR2 Pos = Movingpos + -Norvec * MovingWidth, PosOld = MovingposOld + -Norvec * MovingWidth;

	Collvec = Pos - StaticStartpos;		        //�ǂɑ΂���v���C���[�̃x�N�g��
	CollOldvec = MovingposOld - StaticStartpos;		//�ǂɑ΂���v���C���[�̋��x�N�g��
	Movingvec = Pos - PosOld;			        //�v���C���[�̈ړ��x�N�g��

	if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) <= 0.0f && (Staticvec.y * CollOldvec.x) - (Staticvec.x * CollOldvec.y) >= 0.0f)
	{//�ǂ̊O��
		StaticCross = (Staticvec.y * Movingvec.x) - (Staticvec.x * Movingvec.y);
		CollCross = (Collvec.y * Movingvec.x) - (Collvec.x * Movingvec.y);
		CollCross /= StaticCross;
		if (CollCross >= 0.0f && CollCross < 1.0f)
		{//�ǂ͈̔�
			return true;
		}
	}

	return false;
}

//------------------
//����
//------------------
bool VectorReflection(D3DXVECTOR2& Movingpos, D3DXVECTOR2& MovingposOld, D3DXVECTOR2& Move, float MovingWidth, D3DXVECTOR2& StaticStartpos, D3DXVECTOR2& StaticEndpos)
{
	D3DXVECTOR2 Staticvec = {}, Collvec = {}, CollOldvec = {}, Movingvec = {}, Norvec = {}, Dovec = {}, Hit = {};
	float StaticCross, CollCross;

	Staticvec = StaticEndpos - StaticStartpos;	//�x�N�g��

	Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
	D3DXVec2Normalize(&Norvec, &Norvec);

	// �̕��̌v�Z
	D3DXVECTOR2 Pos = Movingpos + -Norvec * MovingWidth, PosOld = MovingposOld + -Norvec * MovingWidth;

	Collvec = Pos - StaticStartpos;		    //�ǂɑ΂���v���C���[�̃x�N�g��
	CollOldvec = PosOld - StaticStartpos;		//�ǂɑ΂���v���C���[�̋��x�N�g��
	Movingvec = Pos - PosOld;			//�v���C���[�̈ړ��x�N�g��

	if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) > 0.0f && (Staticvec.y * CollOldvec.x) - (Staticvec.x * CollOldvec.y) <= 0.0f)
	{//�ǂ̊O��
		StaticCross = (Staticvec.y * Movingvec.x) - (Staticvec.x * Movingvec.y);
		CollCross = (Collvec.y * Movingvec.x) - (Collvec.x * Movingvec.y);
		CollCross /= StaticCross;
		if (CollCross >= -0.05f && CollCross < 1.05f)
		{//�ǂ͈̔�
			Hit = StaticStartpos + Staticvec * CollCross;
			Movingvec = Pos - Hit;//�v���C���[�̈ړ��x�N�g��
			Dovec = Norvec * ((Movingvec.x * Norvec.x) + (Movingvec.y * Norvec.y));
			Movingpos -= Dovec * 2.0f;
			Move -= Dovec * 2.0f;

			return true;
		}
	}

	return false;
}

//----------
//�����蔻��
//----------
bool VectorInside(D3DXVECTOR2& Movingpos, float MovingWidth, D3DXVECTOR2* pPos)
{
	D3DXVECTOR2 Staticvec = {}, Collvec = {}, Norvec = {};

	Staticvec = pPos[1] - pPos[0];	//�x�N�g��

	Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
	D3DXVec2Normalize(&Norvec, &Norvec);

	// �̕��̌v�Z
	D3DXVECTOR2 Pos = Movingpos + Norvec * MovingWidth;

	Collvec = Pos - pPos[0];		        //�ǂɑ΂���v���C���[�̃x�N�g��

	if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) >= 0.0f)
	{//�ǂ̊O��
		Staticvec = pPos[2] - pPos[1];	//�x�N�g��

		Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
		D3DXVec2Normalize(&Norvec, &Norvec);

		// �̕��̌v�Z
		D3DXVECTOR2 Pos = Movingpos + Norvec * MovingWidth;

		Collvec = Pos - pPos[1];		        //�ǂɑ΂���v���C���[�̃x�N�g��

		if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) >= 0.0f)
		{//�ǂ̊O��
			Staticvec = pPos[3] - pPos[2];	//�x�N�g��

			Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
			D3DXVec2Normalize(&Norvec, &Norvec);

			// �̕��̌v�Z
			D3DXVECTOR2 Pos = Movingpos + Norvec * MovingWidth;

			Collvec = Pos - pPos[2];		        //�ǂɑ΂���v���C���[�̃x�N�g��

			if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) >= 0.0f)
			{//�ǂ̊O��
				Staticvec = pPos[0] - pPos[3];	//�x�N�g��

				Norvec = D3DXVECTOR2(-Staticvec.y, Staticvec.x);
				D3DXVec2Normalize(&Norvec, &Norvec);

				// �̕��̌v�Z
				D3DXVECTOR2 Pos = Movingpos + Norvec * MovingWidth;

				Collvec = Pos - pPos[3];		        //�ǂɑ΂���v���C���[�̃x�N�g��

				if ((Staticvec.y * Collvec.x) - (Staticvec.x * Collvec.y) >= 0.0f)
				{//�ǂ̊O��
					return true;
				}
			}
		}
	}
	return false;
}