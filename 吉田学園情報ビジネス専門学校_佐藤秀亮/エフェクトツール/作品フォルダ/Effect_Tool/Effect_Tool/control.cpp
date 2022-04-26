//*****************************************************************************
// �G�t�F�N�g�̏��X�ݒ�(control.cpp)
// Author : �����G��
//*****************************************************************************
#include "manager.h"
#include "control.h"
#include "keyboard.h"
#include "IntermediateSave.h"

#include "seteffect.h"
#include "Butten.h"
#include <assert.h>
//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_SERECT_COLOR (5)	//�ő�I��F
#define MAX_COLOR (255)			//�ő�F�l

#define MAX_CHANGECOL (10)		//�ő呝���F�l

#define RAND_COLOR (float(rand()% 255) + 5)	//�����_���J���[

#define BUTTEN_SIZE (18)	//�{�^���T�C�Y

#define SAVE_TEXT "data/SaveText.txt"	//�Z�[�u����e�L�X�g�t�@�C��

//*****************************************************************************
//�ÓI�����o�ϐ��錾
//*****************************************************************************
CKeyboard *CControl::m_pKeyboard = NULL;

bool CControl::m_bMouseCursor = false;
bool CControl::m_bPlayerFollow = false;

bool CControl::m_bTap = false;
D3DCOLORVALUE CControl::m_ControlColor = {};
int CControl::m_SerectColor = 1;
D3DCOLORVALUE CControl::m_ControlChangeCol = {};

float CControl::m_ControlSize = 0;
float CControl::m_ControlChangeSize = 0;
int CControl::m_nLife = 0;
int CControl::m_nTex = 0;

int CControl::m_nDensity = 0;
int CControl::m_nPattern = 1;
int CControl::m_nRandMove1 = 1;

int CControl::m_ModelNum = 0;
int CControl::m_Diffusion = 1;
int CControl::m_ModelTrajecNum = 0;

int CControl::m_nUninitVectl = 300;

int CControl::nSynthetic = 0;
float CControl::ParticleSize = 0.0f;
int CControl::ParticleTime = 1;
float CControl::fDistance = 1.0f;

float CControl::fMaxSize = 100.0f;

int CControl::nActiveTime = 10;
float CControl::fParticleAddSize = 0;
float CControl::ActiveAddSize = 0.0f;


D3DXVECTOR2 CControl::m_move = D3DXVECTOR2(1.0f,1.0f);
D3DXVECTOR2 CControl::m_Addmove = {};

bool CControl::m_RandMoveX = false;
bool CControl::m_RandMoveY = false;

bool CControl::m_ColorR = false;
bool CControl::m_ColorG = false;
bool CControl::m_ColorB = false;

bool CControl::m_bPlayerMode = false;
float CControl::m_fAddRotate = 0;

D3DXVECTOR3 CControl::m_move3d = D3DXVECTOR3(1.0f, 1.0f,1.0f);

D3DCOLORVALUE CControl::m_TrajectColor = {};
D3DCOLORVALUE CControl::m_TrajectChangeCol = {};

D3DCOLORVALUE CControl::m_ParticleColor = {};
D3DCOLORVALUE CControl::m_ParticleAddCol = {};
int CControl::nParticleSynthetic = 0;


//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CControl::CControl()
{
	m_bMouseCursor = false;
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CControl::~CControl()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CControl::Init()
{
	m_pKeyboard = CManager::GetKeyboard();
	m_SerectColor = 1;

	m_ControlColor.r = MAX_COLOR;
	m_ControlColor.g = MAX_COLOR;
	m_ControlColor.b = MAX_COLOR;
	m_ControlColor.a = MAX_COLOR;

	m_ControlChangeCol.r = 0;
	m_ControlChangeCol.g = 0;
	m_ControlChangeCol.b = 0;
	m_ControlChangeCol.a = 0;

	m_TrajectColor.r = MAX_COLOR;
	m_TrajectColor.g = MAX_COLOR;
	m_TrajectColor.b = MAX_COLOR;
	m_TrajectColor.a = MAX_COLOR;

	m_TrajectChangeCol.r = 0;
	m_TrajectChangeCol.g = 0;
	m_TrajectChangeCol.b = 0;
	m_TrajectChangeCol.a = 0;

	m_ParticleColor.r = MAX_COLOR;
	m_ParticleColor.g = MAX_COLOR;
	m_ParticleColor.b = MAX_COLOR;
	m_ParticleColor.a = MAX_COLOR;

	m_ParticleAddCol.r = 0;
	m_ParticleAddCol.g = 0;
	m_ParticleAddCol.b = 0;
	m_ParticleAddCol.a = 0;


	m_ControlSize = 20;
	m_ControlChangeSize = 0;
	m_nLife = 100;
	m_nTex = 1;
	m_nDensity = 1;
	m_nPattern = 0;

	m_move = D3DXVECTOR2(1.0f, 1.0f);
	m_Addmove = D3DXVECTOR2(0.0f, 0.0f);
	m_move3d = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_ColorR = false;
	m_ColorG = false;
	m_ColorB = false;

	m_bMouseCursor = false;
	m_bTap = false;

	m_bPlayerMode = false;

	nSynthetic = 0;

	return S_OK;
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CControl::Update()
{
	CManager::MODE mode = CManager::GetMode();

	if (mode == CManager::MODE_2D)
	{
		Control();
	}
	else if (mode == CManager::MODE_3D)
	{
		//�^�b�vON�@OFF
		if (m_pKeyboard->GetKey(DIK_F5) == true)
		{
			if (m_bPlayerMode == false)
			{
				m_bPlayerMode = true;
			}
			else if (m_bPlayerMode == true)
			{
				m_bPlayerMode = false;
			}
		}

		if (m_bPlayerMode == false)
		{
			Control();
		}
	}
}

//*****************************************************************************
//����
//*****************************************************************************
void CControl::Control()
{
	CManager::MODE mode = CManager::GetMode();

	if (m_pKeyboard != NULL)
	{
		//�^�b�vON�@OFF
		if (m_pKeyboard->GetKey(DIK_N) == true)
		{
			if (m_bTap == false)
			{
				m_bTap = true;
			}
			else if (m_bTap == true)
			{
				m_bTap = false;
			}
		}
		//���
		if (m_SerectColor <= 0)
		{
			m_SerectColor = MAX_SERECT_COLOR - 1;
		}
		else if (m_SerectColor >= MAX_SERECT_COLOR)
		{
			m_SerectColor = 1;
		}


		if (m_nTex <= 1)
		{
			m_nTex = 1;
		}


		if (m_ColorR == true)
		{
			m_ControlColor.r = RAND_COLOR;
		}
		if (m_ColorG == true)
		{
			m_ControlColor.g = RAND_COLOR;
		}
		if (m_ColorB == true)
		{
			m_ControlColor.b = RAND_COLOR;
		}
		if (mode == CManager::MODE_2D)
		{
			CControl::Control2D();
		}
		else if (mode == CManager::MODE_3D)
		{
			CControl::Control3D();
		}
	}
}
//*****************************************************************************
//2D��p����
//*****************************************************************************
void CControl::Control2D()
{
	if (m_pKeyboard != NULL)
	{
		//�J�[�\���Ǐ]ON�@OFF
		if (m_pKeyboard->GetKey(DIK_M) == true)
		{
			if (m_bMouseCursor == false)
			{
				m_bMouseCursor = true;
			}
			else if (m_bMouseCursor == true)
			{
				m_bMouseCursor = false;
			}
		}
	}
}

//*****************************************************************************
//3D��p����
//*****************************************************************************
void CControl::Control3D()
{
	if (m_pKeyboard != NULL)
	{
		//�v���C���[�Ǐ]ON�@OFF
		if (m_pKeyboard->GetKey(DIK_M ) == true)
		{
			if (m_bPlayerFollow == false)
			{
				m_bPlayerFollow = true;
			}
			else if (m_bPlayerFollow == true)
			{
				m_bPlayerFollow = false;
			}
		}
	}
}

//*****************************************************************************
//�{�^���̐���
//*****************************************************************************
void CControl::SetButten(int nPattern)
{
	if (CManager::GetMode() == CManager::MODE_2D)
	{
		switch (nPattern)
		{
		case(0):	//����
			//�ړ�X
			CButten::Create(D3DXVECTOR3(77.0f, 416.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVEX, 5, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(100.0f, 416.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVEX, -5, CButten::CHANGE, CButten::PATTERN0);
			//�ړ�Y
			CButten::Create(D3DXVECTOR3(77.0f, 434.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVEY, 5, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(100.0f, 434.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVEY, -5, CButten::CHANGE, CButten::PATTERN0);
			//�ړ����ZX
			CButten::Create(D3DXVECTOR3(110.0f, 451.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ADDMOVEX, 0.1f, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(134.0f, 451.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ADDMOVEX, -0.1f, CButten::CHANGE, CButten::PATTERN0);
			//�ړ����ZY
			CButten::Create(D3DXVECTOR3(110.0f, 471.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ADDMOVEY, 0.1f, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(134.0f, 471.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ADDMOVEY, -0.1f, CButten::CHANGE, CButten::PATTERN0);
			//����
			CButten::Create(D3DXVECTOR3(56.0f, 561.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, -1, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(88.0f, 561.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, 1, CButten::CHANGE, CButten::PATTERN0);

			break;
		case(1):
			//�ړ�
			CButten::Create(D3DXVECTOR3(68.0f, 415.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVEX, 1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(93.0f, 416.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVEX, -1, CButten::CHANGE, CButten::PATTERN1);
			//�g�U
			CButten::Create(D3DXVECTOR3(68.0f, 434.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DIFFUSION, 1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(93.0f, 434.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DIFFUSION, -1, CButten::CHANGE, CButten::PATTERN1);
			//�폜�͈�
			CButten::Create(D3DXVECTOR3(102.0f, 451.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DESTROY, 1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(125.0f, 451.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DESTROY, -1, CButten::CHANGE, CButten::PATTERN1);
			//����
			CButten::Create(D3DXVECTOR3(56.0f, 561.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, -1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(88.0f, 561.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, 1, CButten::CHANGE, CButten::PATTERN1);

			break;
		case(2):
			//�ړ�X
			CButten::Create(D3DXVECTOR3(77.0f, 416.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVEX, 5, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(100.0f, 416.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVEX, -5, CButten::CHANGE, CButten::PATTERN2);
			//�ړ�Y
			CButten::Create(D3DXVECTOR3(77.0f, 434.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVEY, 5, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(100.0f, 434.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVEY, -5, CButten::CHANGE, CButten::PATTERN2);
			//��]
			CButten::Create(D3DXVECTOR3(52.0f, 453.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ROTATE, 0.01f, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(76.0f, 453.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ROTATE, -0.01f, CButten::CHANGE, CButten::PATTERN2);
			//����
			CButten::Create(D3DXVECTOR3(56.0f, 543.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, -1, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(88.0f, 543.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, 1, CButten::CHANGE, CButten::PATTERN2);

			break;
		default:
			break;
		}
	}
	else if (CManager::GetMode() == CManager::MODE_3D)
	{
		switch (nPattern)
		{
		case(0)://�O��
			//�e�N�X�`��
			CButten::Create(D3DXVECTOR3(105.0f, 218.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TEXTURE, -1, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(136.0f, 218.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TEXTURE, 1, CButten::CHANGE, CButten::PATTERN0);
			//�O�Ր�[�F
			CButten::Create(D3DXVECTOR3(133.0f, 290.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTTOPCOL, 5, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(156.0f, 290.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTTOPCOL, -5, CButten::CHANGE, CButten::PATTERN0);
			//�O�Ր�[����
			CButten::Create(D3DXVECTOR3(117.0f, 307.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTTOPADDCOL, 1, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(142.0f, 307.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTTOPADDCOL, -1, CButten::CHANGE, CButten::PATTERN0);
			//��[���f��
			CButten::Create(D3DXVECTOR3(133.0f, 324.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTCUR, 1, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(156.0f, 324.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTCUR, -1, CButten::CHANGE, CButten::PATTERN0);
			//�茳���f��
			CButten::Create(D3DXVECTOR3(135.0f, 344.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTTOP, 1, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(156.0f, 344.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTTOP, -1, CButten::CHANGE, CButten::PATTERN0);
			//�Z�[�u
			CButten::Create(D3DXVECTOR3(120.0f, 397.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SAVE, 0, CButten::CHANGE, CButten::PATTERN0);
			//����
			CButten::Create(D3DXVECTOR3(56.0f, 470.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, -1, CButten::CHANGE, CButten::PATTERN0);
			CButten::Create(D3DXVECTOR3(88.0f, 470.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, 1, CButten::CHANGE, CButten::PATTERN0);
			//���[�h
			CButten::Create(D3DXVECTOR3(106.0f, 416.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::LOAD, 0, CButten::CHANGE, CButten::PATTERN0);
			//�v���Z�b�g���[�h
			CButten::Create(D3DXVECTOR3(153.0f, 435.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PRESETLOAD, 0, CButten::CHANGE, CButten::PATTERN0);
			break;
		case(1):
			//�T�C�Y
			CButten::Create(D3DXVECTOR3(69.0f, 217.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SIZE, 1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(93.0f, 217.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SIZE, -1, CButten::CHANGE, CButten::PATTERN1);
			//�T�C�Y����
			CButten::Create(D3DXVECTOR3(102.0f, 237.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ADDSIZE, 0.1f, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(124.0f, 237.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ADDSIZE, -0.1f, CButten::CHANGE, CButten::PATTERN1);
			//���x
			CButten::Create(D3DXVECTOR3(54.0f, 254.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DENSITY, 1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(79.0f, 254.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DENSITY, -1, CButten::CHANGE, CButten::PATTERN1);
			//�e�N�X�`��
			CButten::Create(D3DXVECTOR3(104.0f, 274.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TEXTURE, -1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(138.0f, 274.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TEXTURE, 1, CButten::CHANGE, CButten::PATTERN1);
			//�ړ�X
			CButten::Create(D3DXVECTOR3(78.0f, 308.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVE3DX, 1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(104.0f, 308.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVE3DX, -1, CButten::CHANGE, CButten::PATTERN1);
			//�ړ�Y
			CButten::Create(D3DXVECTOR3(78.0f, 326.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVE3DY, 1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(104.0f, 326.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVE3DY, -1, CButten::CHANGE, CButten::PATTERN1);
			//�ړ�Z
			CButten::Create(D3DXVECTOR3(78.0f, 345.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVE3DZ, 1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(104.0f, 345.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVE3DZ, -1, CButten::CHANGE, CButten::PATTERN1);
			//�Z�[�u
			CButten::Create(D3DXVECTOR3(120.0f, 378.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SAVE, 0, CButten::CHANGE, CButten::PATTERN1);

			//����
			CButten::Create(D3DXVECTOR3(56.0f, 452.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, -1, CButten::CHANGE, CButten::PATTERN1);
			CButten::Create(D3DXVECTOR3(88.0f, 452.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, 1, CButten::CHANGE, CButten::PATTERN1);

			//���[�h
			CButten::Create(D3DXVECTOR3(106.0f, 398.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::LOAD, 0, CButten::CHANGE, CButten::PATTERN1);

			//�v���Z�b�g���[�h
			CButten::Create(D3DXVECTOR3(151.0f, 415.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PRESETLOAD, 0, CButten::CHANGE, CButten::PATTERN1);

			break;
		case(2):
			//�T�C�Y
			CButten::Create(D3DXVECTOR3(69.0f, 217.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SIZE, 1, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(93.0f, 217.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SIZE, -1, CButten::CHANGE, CButten::PATTERN2);
			//�T�C�Y����
			CButten::Create(D3DXVECTOR3(102.0f, 237.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ADDSIZE, 0.1f, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(124.0f, 237.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ADDSIZE, -0.1f, CButten::CHANGE, CButten::PATTERN2);
			//���x
			CButten::Create(D3DXVECTOR3(54.0f, 254.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DENSITY, 1, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(79.0f, 254.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DENSITY, -1, CButten::CHANGE, CButten::PATTERN2);
			//�e�N�X�`��
			CButten::Create(D3DXVECTOR3(104.0f, 274.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TEXTURE, -1, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(138.0f, 274.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TEXTURE, 1, CButten::CHANGE, CButten::PATTERN2);
			//�����l
			CButten::Create(D3DXVECTOR3(148.0f, 309.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::RANDMOVE3D, 1, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(174.0f, 309.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::RANDMOVE3D, -1, CButten::CHANGE, CButten::PATTERN2);
			//��[���f��
			CButten::Create(D3DXVECTOR3(108.0f, 326.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTCUR, 1, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(131.0f, 326.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTCUR, -1, CButten::CHANGE, CButten::PATTERN2);
			//�茳���f��
			CButten::Create(D3DXVECTOR3(108.0f, 344.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTTOP, 1, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(133.0f, 344.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TRAJECTTOP, -1, CButten::CHANGE, CButten::PATTERN2);
			//�Z�[�u
			CButten::Create(D3DXVECTOR3(120.0f, 378.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SAVE, 0, CButten::CHANGE, CButten::PATTERN2);
			//����
			CButten::Create(D3DXVECTOR3(56.0f, 452.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, -1, CButten::CHANGE, CButten::PATTERN2);
			CButten::Create(D3DXVECTOR3(88.0f, 452.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, 1, CButten::CHANGE, CButten::PATTERN2);

			//���[�h
			CButten::Create(D3DXVECTOR3(106.0f, 398.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::LOAD, 0, CButten::CHANGE, CButten::PATTERN2);

			//�v���Z�b�g���[�h
			CButten::Create(D3DXVECTOR3(151.0f, 415.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PRESETLOAD, 0, CButten::CHANGE, CButten::PATTERN2);

			break;
		case(3):
			//�T�C�Y
			CButten::Create(D3DXVECTOR3(69.0f, 217.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SIZE, 10, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(93.0f, 217.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SIZE, -10, CButten::CHANGE, CButten::PATTERN3);
			//�T�C�Y����
			CButten::Create(D3DXVECTOR3(102.0f, 237.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ADDSIZE, 1, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(124.0f, 237.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ADDSIZE, -1, CButten::CHANGE, CButten::PATTERN3);

			//���x
			CButten::Create(D3DXVECTOR3(54.0f, 254.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DENSITY, 1, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(79.0f, 254.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DENSITY, -1, CButten::CHANGE, CButten::PATTERN3);

			//�e�N�X�`��
			CButten::Create(D3DXVECTOR3(104.0f, 274.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TEXTURE, -1, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(138.0f, 274.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::TEXTURE, 1, CButten::CHANGE, CButten::PATTERN3);

			//��]
			CButten::Create(D3DXVECTOR3(53.0f, 308.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ROTATE, 0.01f, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(76.0f, 308.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ROTATE, -0.01f, CButten::CHANGE, CButten::PATTERN3);

			//�ړ�
			CButten::Create(D3DXVECTOR3(84.0f, 325.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVE3DX, 1, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(108.0f, 325.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MOVE3DX, -1, CButten::CHANGE, CButten::PATTERN3);

			//���T�C�Y
			CButten::Create(D3DXVECTOR3(84.0f, 344.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLESIZE, 1, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(108.0f, 344.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLESIZE, -1, CButten::CHANGE, CButten::PATTERN3);

			//����������
			CButten::Create(D3DXVECTOR3(134.0f, 363.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLETIME, 1, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(158.0f, 363.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLETIME, -1, CButten::CHANGE, CButten::PATTERN3);

			//�����n�_
			CButten::Create(D3DXVECTOR3(101.0f, 379.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DISTANCE, 5, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(122.0f, 379.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::DISTANCE, -5, CButten::CHANGE, CButten::PATTERN3);

			//�A�N�e�B�u����
			CButten::Create(D3DXVECTOR3(133.0f, 416.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ACTIVETIME, 10, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(156.0f, 416.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ACTIVETIME, -10, CButten::CHANGE, CButten::PATTERN3);

			//���傫���ϓ�
			CButten::Create(D3DXVECTOR3(117.0f, 434.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLEADDSIZE, 0.1f, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(143.0f, 434.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLEADDSIZE, -0.1f, CButten::CHANGE, CButten::PATTERN3);

			//�傫���ő�
			CButten::Create(D3DXVECTOR3(117.0f, 454.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MAXSIZE, 10, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(140.0f, 454.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::MAXSIZE, -10, CButten::CHANGE, CButten::PATTERN3);

			//�p�[�e�B�N���F
			CButten::Create(D3DXVECTOR3(54.0f, 487.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLECOLOR, 5, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(76.0f, 487.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLECOLOR, -5, CButten::CHANGE, CButten::PATTERN3);
			//�p�[�e�B�N���F����
			CButten::Create(D3DXVECTOR3(85.0f, 507.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLEADDCOLOR, 1, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(109.0f, 507.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLEADDCOLOR, -1, CButten::CHANGE, CButten::PATTERN3);
			//�p�[�e�B�N������
			CButten::Create(D3DXVECTOR3(70.0f, 525.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLESYNSETIC, -1, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(93.0f, 525.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PARTICLESYNSETIC, 1, CButten::CHANGE, CButten::PATTERN3);

			//�A�N�e�B�u���̑傫���ύX
			CButten::Create(D3DXVECTOR3(165.0f, 542.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ACTIVEADDSIZE, 1, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(190.0f, 542.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::ACTIVEADDSIZE, -1, CButten::CHANGE, CButten::PATTERN3);


			//�Z�[�u
			CButten::Create(D3DXVECTOR3(120.0f, 578.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SAVE, 0, CButten::CHANGE, CButten::PATTERN3);

			//���[�h
			CButten::Create(D3DXVECTOR3(106.0f, 595.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::LOAD, 0, CButten::CHANGE, CButten::PATTERN3);

			//����
			CButten::Create(D3DXVECTOR3(56.0f, 650.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, -1, CButten::CHANGE, CButten::PATTERN3);
			CButten::Create(D3DXVECTOR3(88.0f, 650.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::SYNTHETIC, 1, CButten::CHANGE, CButten::PATTERN3);

			//���[�h
			CButten::Create(D3DXVECTOR3(150.0f, 613.0f, 0.0f), BUTTEN_SIZE, BUTTEN_SIZE, -1,
				CButten::PRESETLOAD, 0, CButten::CHANGE, CButten::PATTERN3);


			break;

		default:
			break;
		}
	}
}

//*****************************************************************************
//�Z�[�u
//*****************************************************************************
void CControl::SaveEffect(CManager::MODE mode, int nPattern)
{
	FILE *pFile = fopen(SAVE_TEXT, "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "#========================================================================\n");
		fprintf(pFile, "#�G�t�F�N�g�̏������̃e�L�X�g�t�@�C���ɏ����o���܂�\n");
		fprintf(pFile, "#�ǂݍ��ރe�L�X�g�t�@�C���ɃR�s�y����Ȃ肵�Ă����R��\n");
		fprintf(pFile, "#========================================================================\n\n\n");

		fprintf(pFile, "#========================================================================\n");
		fprintf(pFile, "#�G�t�F�N�g�p�^�[�� ()�Ԗ�\n");
		fprintf(pFile, "#�����F(���̃G�t�F�N�g�̎g�������A�����Ă�������)\n");
		fprintf(pFile, "#========================================================================\n");


		if (mode == CManager::MODE_2D)
		{
			fprintf(pFile, "EFFECTSTATE2D\n");
			fprintf(pFile, "	PATTERN = %d				//�����̃p�^�[��\n", nPattern);


			fprintf(pFile, "	POS = %.1f %.1f				//���W\n", CSetEffect::GetSetPos().x, CSetEffect::GetSetPos().y);

			switch (nPattern)
			{
			case(0):
				fprintf(pFile, "	MOVE = %.1f %.1f					//����\n", m_move.x, m_move.y);
				fprintf(pFile, "	ADDMOVE = %.1f %.1f				//�������Z�l\n", m_Addmove.x, m_Addmove.y);
				break;
			case(1):
				fprintf(pFile, "	MOVE = %.1f					//�X�s�[�h\n", m_move.x);
				fprintf(pFile, "	DIFFUSION = %d					//�g�U��\n", m_Diffusion);
				fprintf(pFile, "	DESTROYVEC = %d					//������x�N�g��\n", m_nUninitVectl);
			case(2):
				fprintf(pFile, "	ROTATE = %.2f					//��]\n", m_fAddRotate);
				break;
				break;
			default:
				assert(false);
				break;
			}
			fprintf(pFile, "	SIZE = %.1f						//�傫��\n", m_ControlSize);
			fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", m_ControlChangeSize);
			fprintf(pFile, "	COLOR = %d %d %d %d			//�J���[\n", (int)m_ControlColor.r, (int)m_ControlColor.g, (int)m_ControlColor.b, (int)m_ControlColor.a);
			fprintf(pFile, "	CHANGECOLOR = %d %d %d %d			//�J���[�ϓ��l\n", (int)m_ControlChangeCol.r, (int)m_ControlChangeCol.g, (int)m_ControlChangeCol.b, (int)m_ControlChangeCol.a);
			fprintf(pFile, "	LIFE = %d						//���C�t\n", m_nLife);
			fprintf(pFile, "	DENSITY = %d						//���x\n", m_nDensity);

			fprintf(pFile, "	COLORRANDR = %d						//�J���[�����_���� 1���ƗL��\n", m_ColorR);
			fprintf(pFile, "	COLORRANDG = %d						//�J���[�����_���� 1���ƗL��\n", m_ColorG);
			fprintf(pFile, "	COLORRANDB = %d						//�J���[�����_���� 1���ƗL��\n", m_ColorB);

			fprintf(pFile, "	MOVERANDX = %d						//�ړ������_��X 1���ƗL��\n", m_RandMoveX);

			if (m_nPattern != 2)
			{
				fprintf(pFile, "	MOVERANDY = %d						//�ړ������_��Y 1���ƗL��\n", m_RandMoveY);
			}

			fprintf(pFile, "	MOUSEPOS = %d						//�}�E�X�Ǐ]ON 1���ƗL��\n", m_bMouseCursor);


			fprintf(pFile, "END_EFFECTSTATE2D\n\n");
		}
		else if (mode == CManager::MODE_3D)	//3D���[�h
		{
			fprintf(pFile, "EFFECTSTATE3D\n");
			fprintf(pFile, "	PATTERN = %d				//�����̃p�^�[��\n", nPattern);

			fprintf(pFile, "	LIFE = %d						//����\n", m_nLife);

			switch (nPattern)
			{
			case(0):
				fprintf(pFile, "	SECONDCOLOR = %d %d %d %d			//��[�J���[\n", (int)m_TrajectColor.r, (int)m_TrajectColor.g, (int)m_TrajectColor.b, (int)m_TrajectColor.a);
				fprintf(pFile, "	SECONDCHANGECOLOR = %d %d %d %d			//��[�J���[�ϓ��l\n", (int)m_TrajectChangeCol.r, (int)m_TrajectChangeCol.g, (int)m_TrajectChangeCol.b, (int)m_TrajectChangeCol.a);

				fprintf(pFile, "	MODEL = %d						//�O�Վ茳���f��\n", m_ModelNum);
				fprintf(pFile, "	TRAJECTMODEL = %d				//�O�Ր�[���f��\n", m_ModelTrajecNum);
				break;
			case(1):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
				fprintf(pFile, "	DENSITY = %d						//���x\n", CControl::GetDensity());

				fprintf(pFile, "	MOVE3D = %.1f %.1f %.1f					//�ړ�\n", CControl::Getmove3d().x, CControl::Getmove3d().y, CControl::Getmove3d().z);
				break;
			case(2):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
				fprintf(pFile, "	DENSITY = %d						//���x\n", CControl::GetDensity());

				fprintf(pFile, "	RANDMOVE = %d				//�ړ��l\n", CControl::GetRandMove1());
				fprintf(pFile, "	TRAJECTTOP = %d				//�������f���P\n", CControl::GetModelNum());
				fprintf(pFile, "	TRAJECTCUR = %d				//�������f���Q\n", CControl::GetTrajectModelNum());

				break;
			case(3):
				fprintf(pFile, "	ROTATE = %.2f						//��]\n", CControl::GetRotate());
				fprintf(pFile, "	MOVE = %.1f						//�ړ�\n", CControl::Getmove3d().x);
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
				fprintf(pFile, "	DENSITY = %d						//�����x\n", CControl::GetDensity());

				fprintf(pFile, "	PARTICLESIZE = %.1f						//���T�C�Y\n", CControl::GetParticleSize());
				fprintf(pFile, "	PARTICLETIME = %d						//�������Ԋu\n", CControl::GetParticleTime());
				fprintf(pFile, "	DISTANCE = %.1f						//���̔�������\n", CControl::GetDistance());

				fprintf(pFile, "	ACTIVE = %d						//�ғ�����\n", CControl::GetActiveTime());
				fprintf(pFile, "	PARTICLEADDSIZE = %.1f						//���T�C�Y�ύX\n", CControl::GetParticleAddSize());
				fprintf(pFile, "	MAXSIZE = %.1f						//�t�B�[���h�ő�T�C�Y\n", CControl::GetMaxSize());

				fprintf(pFile, "	SECONDCOLOR = %d %d %d %d			//�p�[�e�B�N���J���[\n", (int)CControl::GetParticleColor(1), (int)CControl::GetParticleColor(2), (int)CControl::GetParticleColor(3), (int)CControl::GetParticleColor(4));
				fprintf(pFile, "	SECONDADDCOLOR = %d %d %d %d			//�p�[�e�B�N���J���[����\n", (int)CControl::GetParticleAddCol(1), (int)CControl::GetParticleAddCol(2), (int)CControl::GetParticleAddCol(3), (int)CControl::GetParticleAddCol(4));
				fprintf(pFile, "	SECONDSYNTHETIC = %d			//�p�[�e�B�N������\n", (int)CControl::GetParticleSynthetic());
				fprintf(pFile, "	ACTIVEADDSIZE = %.1f					//�ғ����̉ғ�����\n", CControl::GetAvctiveAddSize());

				fprintf(pFile, "	FIELDTIME = 10			//�t�B�[���h�����Ԋu\n");
				fprintf(pFile, "	FIELDCREATE = 0			//�t�B�[���h�������邩\n");
				fprintf(pFile, "	CREATEPRESET = 0					//�����v���Z�b�g\n");

				break;
			default:
				assert(false);
				break;
			}
			fprintf(pFile, "	POS = 0.0 0.0 0.0			//�o���ʒu\n");

			fprintf(pFile, "	COLOR = %d %d %d %d			//�J���[\n", (int)CControl::GetControlCoror(1), (int)CControl::GetControlCoror(2), (int)CControl::GetControlCoror(3), (int)CControl::GetControlCoror(4));
			fprintf(pFile, "	CHANGECOLOR = %d %d %d %d			//�J���[�ϓ��l\n", (int)CControl::GetChangeCol(1), (int)CControl::GetChangeCol(2), (int)CControl::GetChangeCol(3), (int)CControl::GetChangeCol(4));
			fprintf(pFile, "	LIFE = %d						//���C�t\n", CControl::GetLife());
			fprintf(pFile, "	TEXTURE = %d						//�e�N�X�`��\n", CControl::GetTex());
			fprintf(pFile, "	SYNTHETIC = %d						//����\n", CControl::GetSynthetic());

			fprintf(pFile, "END_EFFECTSTATE3D\n\n");
		}
		fclose(pFile);
	}

}

//*****************************************************************************
//�I��F�̎擾
//*****************************************************************************
int CControl::GetControlCoror(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		return (int)m_ControlColor.r;
		break;
	case(2):
		return (int)m_ControlColor.g;
		break;
	case(3):
		return (int)m_ControlColor.b;
		break;
	case(4):
		return (int)m_ControlColor.a;
		break;
	default:
		return 0;		//��O����(�����s�\�j
		break;
	}
}

//*****************************************************************************
//�I��F�������_�����ǂ���
//*****************************************************************************
bool CControl::GetRandCol(int nSerectcolor)	//�F�����_�����擾
{
	switch (nSerectcolor)
	{
	case(1):
		return m_ColorR;
		break;
	case(2):
		return m_ColorG;
		break;
	case(3):
		return m_ColorB;
		break;
	case(4):
		return false;
		break;
	default:
		return false;		//��O����(�����s�\�j
		break;
	}
}

//*****************************************************************************
//�I��F�����_����
//*****************************************************************************
void CControl::SetColorRandom(int nSerect, bool bAdaptation)
{
	switch (nSerect)
	{
	case(1):
		m_ColorR = bAdaptation;
		break;
	case(2):
		m_ColorG = bAdaptation;
		break;
	case(3):
		m_ColorB = bAdaptation;
		break;
	case(4):
		return;
		break;
	default:
		assert(false);
		break;
	}
}

//*****************************************************************************
//�����l�擾
//*****************************************************************************
int CControl::GetChangeCol(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		return (int)m_ControlChangeCol.r;
		break;
	case(2):
		return (int)m_ControlChangeCol.g;
		break;
	case(3):
		return (int)m_ControlChangeCol.b;
		break;
	case(4):
		return (int)m_ControlChangeCol.a;
		break;
	default:
		return 0;		//��O����
		break;
	}
}

//*****************************************************************************
//�I��F�̕ύX
//*****************************************************************************
void CControl::AddColor(int nColor, int nSerect)
{
	switch (nSerect)
	{
	case(1):
		m_ControlColor.r += nColor;
		if (m_ControlColor.r > MAX_COLOR)
		{
			m_ControlColor.r = MAX_COLOR;
		}
		else if (m_ControlColor.r < 0)
		{
			m_ControlColor.r = 0;
		}
		break;
	case(2):
		m_ControlColor.g += nColor;
		if (m_ControlColor.g > MAX_COLOR)
		{
			m_ControlColor.g = MAX_COLOR;
		}
		else if (m_ControlColor.g < 0)
		{
			m_ControlColor.g = 0;
		}
		break;
	case(3):
		m_ControlColor.b += nColor;
		if (m_ControlColor.b > MAX_COLOR)
		{
			m_ControlColor.b = MAX_COLOR;
		}
		else if (m_ControlColor.b < 0)
		{
			m_ControlColor.b = 0;
		}
		break;
	case(4):
		m_ControlColor.a += nColor;
		if (m_ControlColor.a > MAX_COLOR)
		{
			m_ControlColor.a= MAX_COLOR;
		}
		else if (m_ControlColor.a < 0)
		{
			m_ControlColor.a = 0;
		}
		break;
	default:
		assert(false);		//��O����
		break;
	}
}

//*****************************************************************************
//�����l�̕ύX
//*****************************************************************************
void CControl::AddChangeCol(int nColor, int nSerect)
{
	switch (nSerect)
	{
	case(1):
		m_ControlChangeCol.r += nColor;
		if (m_ControlChangeCol.r > MAX_CHANGECOL)
		{
			m_ControlChangeCol.r = MAX_CHANGECOL;
		}
		else if (m_ControlChangeCol.r < -MAX_CHANGECOL)
		{
			m_ControlChangeCol.r = -MAX_CHANGECOL;
		}
		break;
	case(2):
		m_ControlChangeCol.g += nColor;
		if (m_ControlChangeCol.g > MAX_CHANGECOL)
		{
			m_ControlChangeCol.g = MAX_CHANGECOL;
		}
		else if (m_ControlChangeCol.g < -MAX_CHANGECOL)
		{
			m_ControlChangeCol.g = -MAX_CHANGECOL;
		}
		break;
	case(3):
		m_ControlChangeCol.b += nColor;
		if (m_ControlChangeCol.b > MAX_CHANGECOL)
		{
			m_ControlChangeCol.b = MAX_CHANGECOL;
		}
		else if (m_ControlChangeCol.b < -MAX_CHANGECOL)
		{
			m_ControlChangeCol.b = -MAX_CHANGECOL;
		}
		break;
	case(4):
		m_ControlChangeCol.a += nColor;
		if (m_ControlChangeCol.a > MAX_CHANGECOL)
		{
			m_ControlChangeCol.a = MAX_CHANGECOL;
		}
		else if (m_ControlChangeCol.a < -MAX_CHANGECOL)
		{
			m_ControlChangeCol.a = -MAX_CHANGECOL;
		}
		break;
	default:
		assert(false);		//��O����
		break;
	}
}

//*****************************************************************************
//�I��F�̃��Z�b�g
//*****************************************************************************
void CControl::SetControlCoror(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		m_ControlColor.r = 255;
		break;
	case(2):
		m_ControlColor.g = 255;
		break;
	case(3):
		m_ControlColor.b = 255;
		break;
	case(4):
		m_ControlColor.a;
		break;
	default:
		return ;
		break;
	}
}

//*****************************************************************************
//���b�V�������F�̕ύX
//*****************************************************************************
void CControl::TrajectColor(int nColor, int nSerect)
{
	switch (nSerect)
	{
	case(1):
		m_TrajectColor.r += nColor;
		if (m_TrajectColor.r > MAX_COLOR)
		{
			m_TrajectColor.r = MAX_COLOR;
		}
		else if (m_TrajectColor.r < 0)
		{
			m_TrajectColor.r = 0;
		}
		break;
	case(2):
		m_TrajectColor.g += nColor;
		if (m_TrajectColor.g > MAX_COLOR)
		{
			m_TrajectColor.g = MAX_COLOR;
		}
		else if (m_TrajectColor.g < 0)
		{
			m_TrajectColor.g = 0;
		}
		break;
	case(3):
		m_TrajectColor.b += nColor;
		if (m_TrajectColor.b > MAX_COLOR)
		{
			m_TrajectColor.b = MAX_COLOR;
		}
		else if (m_TrajectColor.b < 0)
		{
			m_TrajectColor.b = 0;
		}
		break;
	case(4):
		m_TrajectColor.a += nColor;
		if (m_TrajectColor.a > MAX_COLOR)
		{
			m_TrajectColor.a = MAX_COLOR;
		}
		else if (m_TrajectColor.a < 0)
		{
			m_TrajectColor.a = 0;
		}
		break;
	default:
		assert(false);		//��O����
		break;
	}
}

//*****************************************************************************
//���b�V�������F�̎擾
//*****************************************************************************
int CControl::GetTrajectColor(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		return (int)m_TrajectColor.r;
		break;
	case(2):
		return (int)m_TrajectColor.g;
		break;
	case(3):
		return (int)m_TrajectColor.b;
		break;
	case(4):
		return (int)m_TrajectColor.a;
		break;
	default:
		return 0;		//��O����(�����s�\�j
		break;
	}
}

//*****************************************************************************
//���b�V�������F�̕ύX
//*****************************************************************************
void CControl::AddTrajectCol(int nColor, int nSerect)
{
	switch (nSerect)
	{
	case(1):
		m_TrajectChangeCol.r += nColor;
		if (m_TrajectChangeCol.r > MAX_CHANGECOL)
		{
			m_TrajectChangeCol.r = MAX_CHANGECOL;
		}
		else if (m_TrajectChangeCol.r < -MAX_CHANGECOL)
		{
			m_TrajectChangeCol.r = -MAX_CHANGECOL;
		}
		break;
	case(2):
		m_TrajectChangeCol.g += nColor;
		if (m_TrajectChangeCol.g > MAX_CHANGECOL)
		{
			m_TrajectChangeCol.g = MAX_CHANGECOL;
		}
		else if (m_TrajectChangeCol.g < -MAX_CHANGECOL)
		{
			m_TrajectChangeCol.g = -MAX_CHANGECOL;
		}
		break;
	case(3):
		m_TrajectChangeCol.b += nColor;
		if (m_TrajectChangeCol.b > MAX_CHANGECOL)
		{
			m_TrajectChangeCol.b = MAX_CHANGECOL;
		}
		else if (m_TrajectChangeCol.b < -MAX_CHANGECOL)
		{
			m_TrajectChangeCol.b = -MAX_CHANGECOL;
		}
		break;
	case(4):
		m_TrajectChangeCol.a += nColor;
		if (m_TrajectChangeCol.a > MAX_CHANGECOL)
		{
			m_TrajectChangeCol.a = MAX_CHANGECOL;
		}
		else if (m_TrajectChangeCol.a < -MAX_CHANGECOL)
		{
			m_TrajectChangeCol.a = -MAX_CHANGECOL;
		}
		break;
	default:
		assert(false);		//��O����(�����s�\�j
		break;
	}
}

//*****************************************************************************
//���b�V�������F�̎擾
//*****************************************************************************
int CControl::GetTrajectCol(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(0):
		break;
	case(1):
		return (int)m_TrajectChangeCol.r;
		break;
	case(2):
		return (int)m_TrajectChangeCol.g;
		break;
	case(3):
		return (int)m_TrajectChangeCol.b;
		break;
	case(4):
		return (int)m_TrajectChangeCol.a;
		break;
	default:
		assert(false);
		break;
	}
	return 0;
}

//*****************************************************************************
//�RD�ړ��̕ω�
//*****************************************************************************
void CControl::Addmove3d(float Move, int nNum)
{
	switch (nNum)
	{
	case(0):
		m_move3d.x += Move;
		if (m_move3d.x <= 0)
		{
			m_move3d.x = 1;
		}
		break;
	case(1):
		m_move3d.y += Move;
		if (m_move3d.y <= 0)
		{
			m_move3d.y = 1;
		}
		break;
	case(2):
		m_move3d.z += Move;
		if (m_move3d.z<= 0)
		{
			m_move3d.z = 1;
		}

		break;
	default:
		assert(false);
		break;
	}
}

//*****************************************************************************
//�p�[�e�B�N���F�̎擾
//*****************************************************************************
int CControl::GetParticleColor(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		return (int)m_ParticleColor.r;
		break;
	case(2):
		return (int)m_ParticleColor.g;
		break;
	case(3):
		return (int)m_ParticleColor.b;
		break;
	case(4):
		return (int)m_ParticleColor.a;
		break;
	default:
		return 0;		//��O����(�����s�\�j
		break;
	}
}

//*****************************************************************************
//�p�[�e�B�N�������F�̎擾
//*****************************************************************************
int CControl::GetParticleAddCol(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		return (int)m_ParticleAddCol.r;
		break;
	case(2):
		return (int)m_ParticleAddCol.g;
		break;
	case(3):
		return (int)m_ParticleAddCol.b;
		break;
	case(4):
		return (int)m_ParticleAddCol.a;
		break;
	default:
		return 0;		//��O����(�����s�\�j
		break;
	}
}

//*****************************************************************************
//�p�[�e�B�N���F�̕ύX
//*****************************************************************************
void CControl::AddParticleColor(int nColor, int nSerect)
{
	switch (nSerect)
	{
	case(1):
		m_ParticleColor.r += nColor;
		if (m_ParticleColor.r > MAX_COLOR)
		{
			m_ParticleColor.r = MAX_COLOR;
		}
		else if (m_ParticleColor.r < 0)
		{
			m_ParticleColor.r = 0;
		}
		break;
	case(2):
		m_ParticleColor.g += nColor;
		if (m_ParticleColor.g > MAX_COLOR)
		{
			m_ParticleColor.g = MAX_COLOR;
		}
		else if (m_ParticleColor.g < 0)
		{
			m_ParticleColor.g = 0;
		}
		break;
	case(3):
		m_ParticleColor.b += nColor;
		if (m_ParticleColor.b > MAX_COLOR)
		{
			m_ParticleColor.b = MAX_COLOR;
		}
		else if (m_ParticleColor.b < 0)
		{
			m_ParticleColor.b = 0;
		}
		break;
	case(4):
		m_ParticleColor.a += nColor;
		if (m_ParticleColor.a > MAX_COLOR)
		{
			m_ParticleColor.a = MAX_COLOR;
		}
		else if (m_ParticleColor.a < 0)
		{
			m_ParticleColor.a = 0;
		}
		break;
	default:
		assert(false);		//��O����
		break;
	}
}

//*****************************************************************************
//�p�[�e�B�N�������F�̕ύX
//*****************************************************************************
void CControl::AddParticleAddCol(int nColor, int nSerect)
{
	switch (nSerect)
	{
	case(1):
		m_ParticleAddCol.r += nColor;
		if (m_ParticleAddCol.r > MAX_COLOR)
		{
			m_ParticleAddCol.r = MAX_COLOR;
		}
		else if (m_ParticleAddCol.r < 0)
		{
			m_ParticleAddCol.r = 0;
		}
		break;
	case(2):
		m_ParticleAddCol.g += nColor;
		if (m_ParticleAddCol.g > MAX_COLOR)
		{
			m_ParticleAddCol.g = MAX_COLOR;
		}
		else if (m_ParticleAddCol.g < 0)
		{
			m_ParticleAddCol.g = 0;
		}
		break;
	case(3):
		m_ParticleAddCol.b += nColor;
		if (m_ParticleAddCol.b > MAX_COLOR)
		{
			m_ParticleAddCol.b = MAX_COLOR;
		}
		else if (m_ParticleAddCol.b < 0)
		{
			m_ParticleAddCol.b = 0;
		}
		break;
	case(4):
		m_ParticleAddCol.a += nColor;
		if (m_ParticleAddCol.a > MAX_COLOR)
		{
			m_ParticleAddCol.a = MAX_COLOR;
		}
		else if (m_ParticleAddCol.a < 0)
		{
			m_ParticleAddCol.a = 0;
		}
		break;
	default:
		assert(false);		//��O����
		break;
	}
}
