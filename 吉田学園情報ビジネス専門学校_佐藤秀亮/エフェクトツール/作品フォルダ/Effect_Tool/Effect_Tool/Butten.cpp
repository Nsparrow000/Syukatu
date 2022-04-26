//*****************************************************************************
// �{�^��(Butten.cpp)
// Author : �����G��
//*****************************************************************************
#include "Butten.h"
#include "manager.h"
#include "control.h"
#include "renderer.h"
#include "mouse.h"
#include "IntermediateSave.h"
#include "LoadEffect.h"

#include <assert.h>

//*****************************************************************************
//�ÓI
//*****************************************************************************
POINT CButten::m_po = {};
D3DXVECTOR2 CButten::m_Mousepos = {};

//*****************************************************************************
//�}�N��
//*****************************************************************************
#define LOAD_PRESET_TEXT "data/Preset.txt"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CButten::CButten(int nPriority) : CScene2D(nPriority)
{
	m_Mousepos = {};
	m_po.x = SCREEN_WIDTH / 2;
	m_po.y = SCREEN_HEIGHT / 2;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CButten::~CButten(void)
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CButten::Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, OPERATION Operation, float nIndeNum, DISPLAY Display, DISPLAY_PATTERN Pattern)
{
	CScene2D::Init(pos);

	m_pKeyboard = CManager::GetKeyboard();
	m_pMouse = CManager::GetMouse();

	m_aOperation = Operation;
	aDisplay = Display;

	m_nIndeNum = nIndeNum;

	if (Pattern == NONE)
	{
		aDisplayPattern = {};
	}
	else
	{
		aDisplayPattern = Pattern;
	}
	m_Size = D3DXVECTOR2(SizeX, SizeY);
	m_bUninit = false;

	CScene2D::SetTexture(nType);	//�I�������ԍ��̃e�N�X�`����\��
	CScene2D::SetWhidth(m_Size.x);
	CScene2D::SetHight(m_Size.y);

	return S_OK;

}

//*****************************************************************************
//�I��
//*****************************************************************************
void CButten::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CButten::Update()
{
	D3DXVECTOR3 pos = GetPosition();

	bool bMousecursor = CControl::GetMouseCursor();

	//�}�E�X���W
	m_Mousepos.x = CManager::GetRenderer()->GetMousePos().x;
	m_Mousepos.y = CManager::GetRenderer()->GetMousePos().y;

	if (CControl::GetPlayerMode() == false)
	{
		//�}�E�X���|���S���͈͓̔���
		if (pos.x - (m_Size.x / 2) < m_Mousepos.x &&
			pos.x + (m_Size.x / 2) > m_Mousepos.x &&
			pos.y - (m_Size.y / 2) < m_Mousepos.y &&
			pos.y + (m_Size.y / 2) > m_Mousepos.y)
		{
			m_fAlpha = 255.0f;
			//���N���b�N
			if (m_pMouse->GetMouseButton(CMouse::DIM_L) == true)
			{
				m_fAlpha = 150.0f;
				Set(m_aOperation, m_nNum, m_nIndeNum);
			}
		}
		else
		{
			m_fAlpha = 100.0f;
		}
	}
	else
	{
		m_fAlpha = 0.0f;
	}



	if (aDisplay == CHANGE)
	{
		if (aDisplayPattern - 1 != CControl::GetPattern())
		{
			m_bUninit = true;
		}
	}

	CScene2D::FadeColorChange(m_fAlpha);
	SetPosition(pos);
	//�j��
	if (m_bUninit == true)
	{
		Uninit();
	}

}

//*****************************************************************************
// �`��
//*****************************************************************************
void CButten::Draw()
{
	CScene2D::Draw();
}

//*****************************************************************************
//�쐬
//*****************************************************************************
CButten *CButten::Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, OPERATION Operation, float nIndeNum, DISPLAY Display, DISPLAY_PATTERN Pattern)
{
	CButten *pButten = NULL;
	pButten = new CButten(CManager::PRIORITY_BUTTEN);		//�������m��
	//NULL�`�F�b�N
	if (pButten != NULL)
	{
		pButten->Init(pos, SizeX, SizeY, nType, Operation, nIndeNum, Display, Pattern);
	}
	return pButten;
}

//*****************************************************************************
//���l�̕ω�
//*****************************************************************************
void CButten::Set(OPERATION Operation, int nNum, float nIndeNum)
{
	switch (Operation)
	{
	case(PATTERN):
		CControl::AddPattern(nIndeNum);
		
		break;
	case(COLSELECT):
		CControl::AddSelectCol(nIndeNum);
		break;
	case(COL):
		CControl::AddColor(nIndeNum, CControl::GetSerectColor());
		break;
	case(ADDCOL):
		CControl::AddChangeCol(nIndeNum, CControl::GetSerectColor());
		break;
	case(SIZE):
		CControl::AddSize(nIndeNum);
		break;
	case(ADDSIZE):
		CControl::AddChangeSize(nIndeNum);
		break;
	case(LIFE):
		CControl::AddLife(nIndeNum);
		break;
	case(DENSITY):
		CControl::AddDensity(nIndeNum);
		break;
	case(DIFFUSION):
		CControl::AddDiffusion(nIndeNum);
		break;
	case(TEXTURE):
		CControl::AddTexture(nIndeNum);
		break;
	case(ROTATE):
		CControl::AddRotateAdd(nIndeNum);
		break;
	case(SAVE):
		CControl::SaveEffect(CManager::GetMode(), CControl::GetPattern());
		if (CManager::GetMode() == CManager::MODE_2D)
		{
			CIntermeiateSave::IntermeiateSave(CManager::GetMode(), CControl::GetPattern(), INTERMEDIATE_TEXT2D);	//���ԃZ�[�u
		}
		else if (CManager::GetMode() == CManager::MODE_3D)
		{
			CIntermeiateSave::IntermeiateSave(CManager::GetMode(), CControl::GetPattern(), INTERMEDIATE_TEXT3D);	//���ԃZ�[�u
		}
		break;
	case(LOAD):
		if (CManager::GetMode() == CManager::MODE_2D)
		{
			CIntermeiateSave::IntermeiateLoad(CManager::GetMode(), INTERMEDIATE_TEXT2D);	//���ԃ��[�h
		}
		else if (CManager::GetMode() == CManager::MODE_3D)
		{
			CIntermeiateSave::IntermeiateLoad(CManager::GetMode(), INTERMEDIATE_TEXT3D);	//���ԃ��[�h
		}
		break;
	case(MOVEX):
		CControl::AddMoveX(nIndeNum);
		break;
	case(MOVEY):
		CControl::AddMoveY(nIndeNum);
		break;
	case(ADDMOVEX):
		CControl::AddMoveXAdd(nIndeNum);
		break;
	case(ADDMOVEY):
		CControl::AddMoveYAdd(nIndeNum);
		break;
	case(DESTROY):
		CControl::AddUninitVectl(nIndeNum);
		break;

	case(TRAJECTTOP):
		CControl::AddTrajectTop(nIndeNum);
		break;
	case(TRAJECTTOPCOL):
		CControl::TrajectColor(nIndeNum, CControl::GetSerectColor());
		break;
	case(TRAJECTTOPADDCOL):
		CControl::AddTrajectCol(nIndeNum, CControl::GetSerectColor());
		break;
	case(TRAJECTCUR):
		CControl::AddTrajectCur(nIndeNum);
		break;
	case(MOVE3DX):
		CControl::Addmove3d(nIndeNum,0);
		break;
	case(MOVE3DY):
		CControl::Addmove3d(nIndeNum, 1);
		break;
	case(MOVE3DZ):
		CControl::Addmove3d(nIndeNum, 2);
		break;
	case(RANDMOVE3D):
		CControl::AddRandMove(nIndeNum);
		break;
	case(SYNTHETIC):
		CControl::AddSynthetic(nIndeNum);
		break;
	case(PARTICLESIZE):
		CControl::AddParticleSize(nIndeNum);
		break;
	case(PARTICLETIME):
		CControl::AddParticleTime(nIndeNum);
		break;
	case(DISTANCE):
		CControl::AddDistance(nIndeNum);
		break;
	case(ACTIVETIME):
		CControl::AddActiveTime(nIndeNum);
		break;
	case(MAXSIZE):
		CControl::AddMaxSize(nIndeNum);
		break;
	case(PARTICLEADDSIZE):
		CControl::AddParticleAddSize(nIndeNum);
		break;
	case(PARTICLECOLOR):
		CControl::AddParticleColor(nIndeNum, CControl::GetSerectColor());
		break;
	case(PARTICLEADDCOLOR):
		CControl::AddParticleAddCol(nIndeNum, CControl::GetSerectColor());
		break;
	case(PARTICLESYNSETIC):
		CControl::AddParticleSynthetic(nIndeNum);
		break;
	case(ACTIVEADDSIZE):
		CControl::AddAvctiveAddSize(nIndeNum);
		break;
	case(PRESETLOAD):
		//CLoadEffect::PresetTotal(LOAD_PRESET_TEXT);
		CLoadEffect::EffectStateLoad(LOAD_PRESET_TEXT);
		break;

	default:
		assert(false);
		break;
	}
}