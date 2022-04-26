//*****************************************************************************
// (マウスに向かって飛んでく)エフェクト処理 [MouseTracking.cpp]
// Author : 佐藤秀亮
//*****************************************************************************
#include "MouseTracking.h"
#include "manager.h"
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CMouseTracking::CMouseTracking(int nPriority) : CEffect(nPriority)
{
	m_move = {};
	m_Vec = {};
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CMouseTracking::~CMouseTracking()
{

}

//*****************************************************************************
//	初期化
//*****************************************************************************
HRESULT CMouseTracking::Init(D3DXVECTOR3 pos,
	D3DXVECTOR2 move,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	D3DXVECTOR2 Size,
	D3DXVECTOR2 MinSize,
	int nLife, int nType,
	D3DXVECTOR3 Endpos,
	int Diffusion,
	int UninitVectl,
	int Synthetic)
{
	CEffect::Init(pos, color, Mincolor, Size, MinSize, nLife, nType, Synthetic);
	m_Endpos = pos;
	m_Vec = pos - Endpos;
	m_move = move;

	m_UninitVectl = UninitVectl;

	float randAngle = float(rand() % Diffusion) - float(rand() % Diffusion);
	randAngle /= 100.0f;

	m_fAngle = (float)atan2(m_Vec.x, m_Vec.y);		//角度

	m_fAngle += randAngle;


	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CMouseTracking::Uninit()
{
	CEffect::Uninit();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CMouseTracking::Update()
{
	D3DXVECTOR3 pos = GetPosition();

	m_Vec = pos - m_Endpos;

	m_Vectl = sqrtf(m_Vec.x * m_Vec.x + m_Vec.y *  m_Vec.y);

	if (m_Vectl >= m_UninitVectl)
	{
		m_bUninit = true;
	}

	pos += D3DXVECTOR3(sinf(m_fAngle) * -m_move.x, cosf(m_fAngle) * -m_move.x, 0.0f);

	SetPosition(pos);

	CEffect::Update();
}

//*****************************************************************************
//描画
//*****************************************************************************
void CMouseTracking::Draw()
{
	CEffect::Draw();
}

//*****************************************************************************
//作成
//*****************************************************************************
CMouseTracking *CMouseTracking::Create(D3DXVECTOR3 pos,
	D3DXVECTOR2 move,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	D3DXVECTOR2 Size,
	D3DXVECTOR2 MinSize,
	int nLife, int nType,
	D3DXVECTOR3 Endpos,
	int Diffusion,
	int UninitVectl,
	int Synthetic)
{
	CMouseTracking *pMouseTracking = NULL;
	pMouseTracking = new CMouseTracking(CManager::PRIORITY_EFFECT);		//メモリ確保
										//NULLチェック
	if (pMouseTracking != NULL)
	{
		pMouseTracking->Init(pos, move, color, Mincolor, Size, MinSize, nLife, nType, Endpos,Diffusion, UninitVectl,Synthetic);
	}

	return pMouseTracking;
}
