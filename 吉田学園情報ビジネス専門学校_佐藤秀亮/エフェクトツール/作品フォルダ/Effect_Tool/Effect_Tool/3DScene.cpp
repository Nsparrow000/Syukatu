//=============================================================================
// 3D���G�t�F�N�g�Ǘ�[3DScene.h]
// Author : �����G��
//=============================================================================
//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#if 1
#include "3DScene.h"
#include "Fade.h"
#include "load.h"
#include "control.h"

#include "keyboard.h"

#include "SetEffect3d.h"

#include "LoadEffect.h"
#include "PresetSetEffect.h"
#include "Butten.h"

#endif

//*****************************************************************************
//�ÓI
//*****************************************************************************
int C3DScene::m_nDirey = 0;
bool C3DScene::m_bPresetStart = false;
int C3DScene::m_nPattarn = 0;

//*****************************************************************************
//�}�N��
//*****************************************************************************
#define FILE3D "data/3DMode.txt"
#define SET_TEXT_3D "data/3DSetTex.txt"

#define LOAD_PRESET_TEXT "data/Preset.txt"

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
C3DScene::C3DScene()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
C3DScene::~C3DScene()
{
}
#endif

//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT C3DScene::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();

	CLoad::Load(FILE3D);
	CLoad::LoadButten(SET_TEXT_3D);

	CLoadEffect::EffectOrder(LOAD_PRESET_TEXT);
	CLoadEffect::EffectStateLoad(LOAD_PRESET_TEXT);

	CControl::SetPlayerMode(true);
	//�t�F�[�h
	CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	m_bPresetStart = false;

	m_nDirey = 0;
	//�G�t�F�N�g�o�����
	CSetEffect3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, +15.0f, 0.0f),
		D3DXVECTOR2(0.0f, 0.0f));

	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void C3DScene::Uninit()
{
	CScene::Release();
}

//*****************************************************************************
// kousinn
//***************************************************************************** 
void C3DScene::Update()
{
	if (m_pKeyboard != NULL)
	{
		if (m_pKeyboard->GetKey(DIK_RETURN) == true)
		{
			CControl::SetPlayerMode(true);
			CFade::SetFade(CManager::MODE_2D);
			CControl::SetPattern(0);
			CButten::ResetPatten();
		}

		if (m_pKeyboard->GetKey(DIK_F1) == true)
		{
			CPresetEffect::SetEffect3D(m_nPattarn, D3DXVECTOR3(0.0f, 0.0f, 0.0f), {});
		}

		if (m_pKeyboard->GetKey(DIK_F2) == true)
		{
			for (int nCnt = 0; nCnt < CLoadEffect::GetPresetTotal(); nCnt++)
			{
				CPresetEffect::SetEffect3D(nCnt, D3DXVECTOR3(0.0f, 50.0f, 0.0f), {});
			}
		}
		if (m_pKeyboard->GetKey(DIK_F3) == true)
		{
			CPresetEffect::CallOrder3D(0, D3DXVECTOR3(0.0f, 50.0f, 0.0f), {});
		}

	}

}

#if 1
//*****************************************************************************
//�`��
//***************************************************************************** 
void C3DScene::Draw()
{

}

//*****************************************************************************
//�`��
//***************************************************************************** 
C3DScene *C3DScene::Create()
{
	C3DScene *p2DScene = NULL;
	p2DScene = new C3DScene;		//�������m��
									//NULL�`�F�b�N
	if (p2DScene != NULL)
	{
		p2DScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return p2DScene;
}
#endif

#if 1
#endif
