//=============================================================================
// �}�l�[�W�� [Manager.h]
// Author : �����G��
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

#include "keyboard.h"
#include "mouse.h"
#include "plane.h"

#include "2DScene.h"
#include "3DScene.h"
#include "control.h"

#include "MeshEffect.h"
#include <assert.h>
//�ÓI�����o�ϐ�
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CMouse *CManager::m_pMouse = NULL;
//CGamePad *CManager::m_pGamepad = NULL;

CManager::MODE CManager::m_aMode = CManager::MODE_2D;

C2DScene *CManager::m_p2DScene = NULL;
C3DScene *CManager::m_p3DScene = NULL;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CManager::CManager()
{

}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CManager::~CManager()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_pKeyboard = new CKeyboard;
	m_pKeyboard->Init(hInstance, hWnd);
	m_pMouse = new CMouse;
	m_pMouse->Init(hInstance, hWnd);
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	SetMode(m_aMode);

	//�e�N�X�`���ǂݍ���	
	CScene2D::CreateTexture();
	CPlane::CreateTextureFiled();
	CMeshEffect::CreateTextureMesh();

	CControl::Init();
	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CManager::Uninit()
{
	CScene2D::UninitTexture();
	CPlane::UninitTexture();
	CMeshEffect::UninitTextureMesh();

	CScene::ReleaseAll();
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}


}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CManager::Update()
{
	CControl::Update();

	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//*****************************************************************************
//�`��
//*****************************************************************************
void CManager::Draw()
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
//	�����_���[�擾
//=============================================================================
CRenderer *CManager::GetRenderer()
{
	return m_pRenderer;
}

//=============================================================================
//	�L�[�{�[�h�擾
//=============================================================================
CKeyboard *CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//=============================================================================
//	�}�E�X�擾
//=============================================================================
CMouse *CManager::GetMouse()
{
	return m_pMouse;
}

//=============================================================================
//���[�h�Z�b�g
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	CScene::ReleaseAll();

	switch (mode)
	{
	case (MODE_2D):
		m_p2DScene = C2DScene::Create();
		break;

	case (MODE_3D):
		m_p3DScene = C3DScene::Create();
		break;

	default:
		assert(false);		//��O����(�����s�\�j
		break;
	}
	m_aMode = mode;
}

//=============================================================================
//���[�h�Z�b�g
//=============================================================================
CManager::MODE CManager::GetMode()
{
	return m_aMode;
}
