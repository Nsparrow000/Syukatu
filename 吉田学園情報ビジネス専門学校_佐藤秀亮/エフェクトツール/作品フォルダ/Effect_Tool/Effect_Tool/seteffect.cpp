//*****************************************************************************
// �G�t�F�N�g�ݒu����(SetEffect.cpp)
// Author : �����G��
//*****************************************************************************
//*****************************************************************************
//�C���N���[�h�t�@�C��
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
#include "Rotate.h"

#include <assert.h>

//*****************************************************************************
//�ÓI
//*****************************************************************************
int CSetEffect::m_nSerectEffect = 0;
D3DXVECTOR3 CSetEffect::m_pos = {};
bool CSetEffect::m_bOnce = false;

float CSetEffect::m_fSizeX2 = 0;
float CSetEffect::m_fSizeY2 = 0;
POINT CSetEffect::m_po = {};

//*****************************************************************************
//�}�N��
//*****************************************************************************

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CSetEffect::CSetEffect(int nPriority) : CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUninit = false;
	m_nSerectEffect = 0;

	m_po.x = SCREEN_WIDTH / 2;
	m_po.y = SCREEN_HEIGHT /2;

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CSetEffect::~CSetEffect()
{

}
#endif

//*****************************************************************************
//������
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



	CScene2D::SetTexture(nType);	//�I�������ԍ��̃e�N�X�`����\��
	CScene2D::SetWhidth(SizeX);		//�T�C�Y�̓K��
	CScene2D::SetHight(SizeY);
	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CSetEffect::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V
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
		if (m_pMouse->GetMouseButton(CMouse::DIM_R) == true)
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
	m_Color.a = 0;


	CScene2D::ColorChange(m_Color);
	CScene2D::SetPosition(m_pos);
	//�폜
	if (m_bUninit == true)
	{
		Uninit();
	}
}

//�`��E�쐬
#if 1
//*****************************************************************************
//�`��
//*****************************************************************************
void CSetEffect::Draw()
{

}

//*****************************************************************************
//�쐬
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
//�G�t�F�N�g���쐬
//*****************************************************************************
void CSetEffect::SetEffect(int nPatern)
{
	D3DXVECTOR2 move = D3DXVECTOR2(1.0f, 1.0f);
	move = CControl::GetMove();

	for (int nCnt = 0; nCnt < CControl::GetDensity(); nCnt++)
	{
		if (CControl::GetPattern() == 1)
		{
			move.x = (float(rand() % (int)move.x));
			move.x /= 10;
		}
		else
		{
			move.x = (float(rand() % (int)CControl::GetMove().x)) - (float(rand() % (int)CControl::GetMove().x));
			move.x /= 10;
			move.y = (float(rand() % (int)CControl::GetMove().y)) - (float(rand() % (int)CControl::GetMove().y));
			move.y /= 10;
		}
		switch (nPatern)
		{
		case(0):
			CMovement::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
				move,
				D3DXCOLOR((float)CControl::GetControlCoror(1), (float)CControl::GetControlCoror(2), (float)CControl::GetControlCoror(3), (float)CControl::GetControlCoror(4)),
				D3DXCOLOR((float)CControl::GetChangeCol(1), (float)CControl::GetChangeCol(2), (float)CControl::GetChangeCol(3), (float)CControl::GetChangeCol(4)),
				D3DXVECTOR2(CControl::GetSize(), CControl::GetSize()),
				D3DXVECTOR2(CControl::GetChangeSize(), CControl::GetChangeSize()),
				CControl::GetLife(), CControl::GetTex(),
				CControl::GetAddMove(),CControl::GetSynthetic());
			break;
		case(1):
			CMouseTracking::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
				move,
				D3DXCOLOR((float)CControl::GetControlCoror(1), (float)CControl::GetControlCoror(2), (float)CControl::GetControlCoror(3), (float)CControl::GetControlCoror(4)),
				D3DXCOLOR((float)CControl::GetChangeCol(1), (float)CControl::GetChangeCol(2), (float)CControl::GetChangeCol(3), (float)CControl::GetChangeCol(4)),
				D3DXVECTOR2(CControl::GetSize(), CControl::GetSize()),
				D3DXVECTOR2(CControl::GetChangeSize(), CControl::GetChangeSize()),
				CControl::GetLife(), CControl::GetTex(),
				D3DXVECTOR3(CManager::GetRenderer()->GetMousePos().x, CManager::GetRenderer()->GetMousePos().y,0.0f),
				CControl::GetDiffusion(),
				CControl::GetUninitVectl(),CControl::GetSynthetic());
			break;
		case(2):
			CRotate::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f),
				move,
				D3DXCOLOR((float)CControl::GetControlCoror(1), (float)CControl::GetControlCoror(2), (float)CControl::GetControlCoror(3), (float)CControl::GetControlCoror(4)),
				D3DXCOLOR((float)CControl::GetChangeCol(1), (float)CControl::GetChangeCol(2), (float)CControl::GetChangeCol(3), (float)CControl::GetChangeCol(4)),
				D3DXVECTOR2(CControl::GetSize(), CControl::GetSize()),
				D3DXVECTOR2(CControl::GetChangeSize(), CControl::GetChangeSize()),
				CControl::GetLife(), CControl::GetTex(),
				CControl::GetRotate(), CControl::GetSynthetic());
			break;
		case(3):
			break;
		default:
			break;
		}
	}
}
