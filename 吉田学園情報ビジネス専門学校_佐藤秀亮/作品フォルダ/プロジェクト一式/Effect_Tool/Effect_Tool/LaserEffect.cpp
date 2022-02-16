//*****************************************************************************
// (レーザー)エフェクト処理 [LaserEffect.cpp]
// Author : 佐藤秀亮
//*****************************************************************************

#include "LaserEffect.h"
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CLaserEffect::CLaserEffect(int nPriority) : CEffect(nPriority)
{
	m_Vector1 = {};
	m_Vector2 = {};
	m_OldVector1 = {};
	m_OldVector2 = {};
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CLaserEffect::~CLaserEffect()
{

}

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CLaserEffect::Init(
	D3DXVECTOR3 Vector1,
	D3DXVECTOR3 Vector2,
	D3DXVECTOR3 OldVector1,
	D3DXVECTOR3 OldVector2,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nLife, int nType)
{
	CEffect::Init(D3DXVECTOR3(0.0f,0.0f,0.0f), color, Mincolor, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 (0.0f,0.0f), nLife, nType);
	
	m_Vector1 = Vector1;
	m_Vector2 = Vector2;
	m_OldVector1 = OldVector1;
	m_OldVector2 = OldVector2;

	CEffect::UpdateLaser(m_Vector1, m_Vector2, m_OldVector1, m_OldVector2);

	return S_OK;

}

//*****************************************************************************
//終了
//*****************************************************************************
void CLaserEffect::Uninit()
{
	CEffect::Uninit();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CLaserEffect::Update()
{
	D3DXVECTOR3 pos = GetPosition();

	CEffect::UpdateLaser(m_Vector1, m_Vector2, m_OldVector1, m_OldVector2);

	CEffect::Update();
}

//*****************************************************************************
//描画
//*****************************************************************************
void CLaserEffect::Draw()
{
	CEffect::Draw();
}

//*****************************************************************************
//作成
//*****************************************************************************
CLaserEffect *CLaserEffect::Create(
	D3DXVECTOR3 Vector1,
	D3DXVECTOR3 Vector2,
	D3DXVECTOR3 OldVector1,
	D3DXVECTOR3 OldVector2,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nLife, int nType)
{
	CLaserEffect *pLaserEffect = NULL;
	pLaserEffect = new CLaserEffect(3);		//メモリ確保
												//NULLチェック
	if (pLaserEffect != NULL)
	{
		pLaserEffect->Init(Vector1, Vector2, OldVector1, OldVector2, color, Mincolor, nLife, nType);
	}

	return pLaserEffect;
}