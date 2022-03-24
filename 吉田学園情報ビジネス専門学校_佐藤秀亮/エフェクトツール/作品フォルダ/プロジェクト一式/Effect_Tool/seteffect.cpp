//*****************************************************************************
// エフェクト設置処理(SetEffect.cpp)
// Author : 佐藤秀亮
//*****************************************************************************
//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "SetEffect.h"
#include "Scene2D.h"
#include "manager.h"
#include "renderer.h"

#include "mouse.h"
#include "keyboard.h"
#include "control.h"

#include "Movement.h"
#include "MouseTracking.h"

#include <assert.h>

#define RAND_MOVE ((float(rand() % 100) + 1))//ランダム移動値
#define RAND_MOVEMIN ((float(rand() % 100)) - (float(rand() % 100)))//ランダム移動値

//*****************************************************************************
//静的
//*****************************************************************************
int CSetEffect::m_nSerectEffect = 0;
D3DXVECTOR3 CSetEffect::m_pos = {};
bool CSetEffect::m_bOnce = false;

float CSetEffect::m_fSizeX2 = 0;
float CSetEffect::m_fSizeY2 = 0;
POINT CSetEffect::m_po = {};

D3DXVECTOR3 CSetEffect::m_Pos1 = {};
D3DXVECTOR3 CSetEffect::m_Pos2 = {};
D3DXVECTOR3 CSetEffect::m_OldPos1 = {};
D3DXVECTOR3 CSetEffect::m_OldPos2 = {};

//*****************************************************************************
//マクロ
//*****************************************************************************

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CSetEffect::CSetEffect(int nPriority) : CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUninit = false;
	m_nSerectEffect = 0;

	m_Pos1 = {};
	m_Pos2 = {};
	m_OldPos1 = {};
	m_OldPos2 = {};

	m_po.x = SCREEN_WIDTH / 2;
	m_po.y = SCREEN_HEIGHT /2;

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CSetEffect::~CSetEffect()
{

}
#endif

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CSetEffect::Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType)
{
	CScene2D::Init(pos);

	m_pKeyboard = CManager::GetKeyboard();
	m_pMouse = CManager::GetMouse();

	SetObjType(CScene::OBJECTTYPE_UI);

	m_fSizeX = SizeX;
	m_fSizeY = SizeY;

	m_fSizeX2 = SizeX;
	m_fSizeY2 = SizeY;

	m_pos = pos;
	m_bUninit = false;

	m_Pos1 = D3DXVECTOR3(m_pos.x + (m_fSizeX), m_pos.y - (m_fSizeY / 2), 0.0f);
	m_Pos2 = D3DXVECTOR3(m_pos.x - (m_fSizeX), m_pos.y + (m_fSizeY / 2), 0.0f);


	CScene2D::SetTexture(nType);	//選択した番号のテクスチャを貼る
	CScene2D::SetWhidth(SizeX);		//サイズの適応
	CScene2D::SetHight(SizeY);
	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CSetEffect::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CSetEffect::Update()
{
	bool bMousecursor = CControl::GetMouseCursor();
	bool bTap = CControl::GetTap();

	if (bMousecursor == true)
	{
		m_pos.x = CManager::GetRenderer()->GetMousePos().x;
		m_pos.y = CManager::GetRenderer()->GetMousePos().y;
	}
	if (bTap == true)
	{
		if (m_pMouse->GetMouseButton(CMouse::DIM_L) == true)
		{
			SetEffect(CControl::GetPattern());
		}
	}
	else
	{
		SetEffect(CControl::GetPattern());
	}
	m_Color.r = 255;
	m_Color.g = 255;
	m_Color.b = 255;
	m_Color.a = 255;

	m_Pos1 = D3DXVECTOR3(m_pos.x + (m_fSizeX / 2), m_pos.y - (m_fSizeY / 2), 0.0f);
	m_Pos2 = D3DXVECTOR3(m_pos.x - (m_fSizeX / 2), m_pos.y + (m_fSizeY / 2), 0.0f);

	CScene2D::ColorChange(m_Color);
	CScene2D::SetPosition(m_pos);
	//削除
	if (m_bUninit == true)
	{
		Uninit();
	}
}

//描画・作成
#if 1
//*****************************************************************************
//描画
//*****************************************************************************
void CSetEffect::Draw()
{
#if _DEBUG
	//CScene2D::Draw();
#endif

	m_OldPos1 = m_Pos1;
	m_OldPos2 = m_Pos2;
}

//*****************************************************************************
//作成
//*****************************************************************************
CSetEffect *CSetEffect::Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType)
{
	CSetEffect * pUI = NULL;
	pUI = new CSetEffect(CManager::PRIORITY_SET);
	if (pUI != NULL)
	{
		pUI->Init(pos, SizeX, SizeY, nType);
	}
	return pUI;
}
#endif

//*****************************************************************************
//エフェクトを作成
//*****************************************************************************
void CSetEffect::SetEffect(int nPatern)
{
	D3DXVECTOR2 move = CControl::GetMove();

	for (int nCnt = 0; nCnt < CControl::GetDensity(); nCnt++)
	{
		if (CControl::GetRandMoveX() == true)
		{
			move.x = RAND_MOVEMIN;
			move.x /= 10;
		}

		if (CControl::GetRandMoveY() == true)
		{
			move.y = RAND_MOVEMIN;
			move.y /= 10;
		}

		switch (nPatern)
		{
		case(1):
			CMovement::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
				move,
				D3DXCOLOR((float)CControl::GetControlCoror(1), (float)CControl::GetControlCoror(2), (float)CControl::GetControlCoror(3), (float)CControl::GetControlCoror(4)),
				D3DXCOLOR((float)CControl::GetChangeCol(1), (float)CControl::GetChangeCol(2), (float)CControl::GetChangeCol(3), (float)CControl::GetChangeCol(4)),
				D3DXVECTOR2(CControl::GetSize(), CControl::GetSize()),
				D3DXVECTOR2(CControl::GetChangeSize(), CControl::GetChangeSize()),
				CControl::GetLife(), CControl::GetTex(),
				CControl::GetAddMove());
			break;
		case(2):
			CMouseTracking::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
				move,
				D3DXCOLOR((float)CControl::GetControlCoror(1), (float)CControl::GetControlCoror(2), (float)CControl::GetControlCoror(3), (float)CControl::GetControlCoror(4)),
				D3DXCOLOR((float)CControl::GetChangeCol(1), (float)CControl::GetChangeCol(2), (float)CControl::GetChangeCol(3), (float)CControl::GetChangeCol(4)),
				D3DXVECTOR2(CControl::GetSize(), CControl::GetSize()),
				D3DXVECTOR2(CControl::GetChangeSize(), CControl::GetChangeSize()),
				CControl::GetLife(), CControl::GetTex(),
				D3DXVECTOR3(CManager::GetRenderer()->GetMousePos().x, CManager::GetRenderer()->GetMousePos().y,0.0f),
				CControl::GetDiffusion(),
				CControl::GetUninitVectl());
			break;

		default:
			assert(false);
			break;
		}
	}
}
