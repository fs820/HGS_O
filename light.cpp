#include "light.h"

//グローバル変数宣言
D3DLIGHT9 g_light[8];	//ライト情報

//*****************************************
//ライトの初期化
//*****************************************
void InitLight(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ライトの方向ベクトル
	D3DXVECTOR3 vecDir[8];

	for (int nCntLight = 0;nCntLight < 3;nCntLight++)
	{
		// ライトをクリアする
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ライトの方向を設定
		vecDir[0] = D3DXVECTOR3(0.2f , -0.8f, -0.4f);
		vecDir[1] = D3DXVECTOR3(-12.0f , -14.0f, 15.0f);
		vecDir[2] = D3DXVECTOR3(-5.0f , -5.57f, -3.3f);

		// 正規化する(大きさ１のベクトルにする)
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		g_light[nCntLight].Direction = vecDir[nCntLight];

		// ライトを設定する
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}

	// ライトをクリアする
	ZeroMemory(&g_light[3], sizeof(D3DLIGHT9));

	//種類
	g_light[3].Type = D3DLIGHT_POINT;
	//拡散光
	g_light[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
	//環境光
	g_light[3].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
	//鏡面反射光
	g_light[3].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
	//位置
	g_light[3].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//範囲
	g_light[3].Range = 0.0f;
	//距離減衰率(一定)
	g_light[3].Attenuation0 = 0.1f;
	//距離減衰率(距離)
	g_light[3].Attenuation1 = 0.0f;
	//距離減衰率(距離*2)
	g_light[3].Attenuation2 = 0.0f;
	//ライトセット
	pDevice->SetLight(3, &g_light[3]);
	//有効化
	pDevice->LightEnable(3, FALSE);

	for (int nCnt = 4; nCnt < 8; nCnt++)
	{
		//種類
		g_light[nCnt].Type = D3DLIGHT_SPOT;
		//拡散光
		g_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//環境光
		g_light[nCnt].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//鏡面反射光
		g_light[nCnt].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//位置
		g_light[nCnt].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//方向
		vecDir[nCnt] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		//正規化
		D3DXVec3Normalize(&vecDir[nCnt], &vecDir[nCnt]);
		g_light[nCnt].Direction = vecDir[nCnt];
		//範囲
		g_light[nCnt].Range = 0.0f;
		//コーン減衰率
		g_light[nCnt].Falloff = 0.01f;
		//距離減衰率
		g_light[nCnt].Attenuation0 = 0.1f;
		//コーン角度(内)
		g_light[nCnt].Theta = D3DXToRadian(90.0f);
		//コーン角度(外)
		g_light[nCnt].Phi = D3DXToRadian(360.0f);
		//ライトセット
		pDevice->SetLight(nCnt, &g_light[nCnt]);
		//有効化
		pDevice->LightEnable(nCnt, FALSE);
	}
}

//*****************************************
//ライトの終了
//*****************************************
void UninitLight(void)
{
	

}

//*****************************************
//ライトの更新
//*****************************************
void UpdateLight(void)
{

}

D3DLIGHT9* GetLight(void)
{
	return &g_light[0];
}

//--------------------------
//セット
//--------------------------
void SetLight(int nIdx, float Range, D3DXCOLOR col, D3DXVECTOR3 pos)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 距離
	g_light[nIdx].Range = Range;
	//拡散光
	g_light[nIdx].Diffuse = col;
	//環境光
	g_light[nIdx].Ambient = col;
	//鏡面反射光
	g_light[nIdx].Specular = col;
	//位置
	g_light[nIdx].Position = pos;

	//ライトセット
	pDevice->SetLight(nIdx, &g_light[nIdx]);
	//有効化
	pDevice->LightEnable(nIdx, TRUE);
}

//--------------------------
//破棄
//--------------------------
void EndLight(int nIdx)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//有効化
	pDevice->LightEnable(nIdx, FALSE);
}