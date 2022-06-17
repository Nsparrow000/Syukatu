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

#define MAX_CHANGECOL (30)		//�ő呝���F�l

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
int CControl::m_nSecondTime = 0;

int CControl::m_nVtx = 4;
int CControl::m_nType = 0;
D3DXVECTOR2 CControl::m_TexMove = D3DXVECTOR2(0.0f, 0.0f);
D3DXVECTOR2 CControl::m_TexNum = D3DXVECTOR2(1.0f, 1.0f);
int CControl::m_SecndType = 0;

D3DXVECTOR2 CControl::m_TexPattern = D3DXVECTOR2(1.0f, 1.0f);
int CControl::m_nAnimCont = -1;
D3DXVECTOR2 CControl::m_nSplit = D3DXVECTOR2(1.0f, 1.0f);
float CControl::m_fHigth = 30.0f;
D3DXVECTOR3 CControl::m_ContorolBezier = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
int CControl::m_SecondTex = 1;
int CControl::m_AnimPatternType = 0;


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
	m_AnimPatternType = 0;
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
		//�{�^���z�u
		CButten::SetButten(nPattern);
	}
	else if (CManager::GetMode() == CManager::MODE_3D)
	{
			//�{�^���z�u
			CButten::SetButten(nPattern);
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
				fprintf(pFile, "	DISTANCE = %.1f					//����\n", CControl::GetDistance());
				break;

			case(2):
				fprintf(pFile, "	ROTATE = %.2f					//��]\n", m_fAddRotate);
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
			fprintf(pFile, "	TEXTURE = %d						//�e�N�X�`��\n", CControl::GetTex());
			fprintf(pFile, "	SYNTHETIC = %d						//����\n", CControl::GetSynthetic());


			fprintf(pFile, "END_EFFECTSTATE2D\n\n");
		}
		else if (mode == CManager::MODE_3D)	//3D���[�h
		{
			fprintf(pFile, "EFFECTSTATE3D\n");
			fprintf(pFile, "	PATTERN = %d				//�����̃p�^�[��\n", nPattern);

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

				fprintf(pFile, "	DISTANCE = %.1f						//��������\n", CControl::GetDistance());
				fprintf(pFile, "	TYPE = %d					//�o���ʒu�̃p�^�[��\n", CControl::GetType());
				fprintf(pFile, "	SECONDTYPE = %d					//�����_���ړ��̃p�^�[��\n", CControl::GetSecondType());
				fprintf(pFile, "	PARTICLETIME = %d						//�������Ԋu\n", CControl::GetParticleTime());

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
			case(4):

				fprintf(pFile, "	MOVE3D = %.1f %.1f %.1f					//�ړ�\n", CControl::Getmove3d().x, CControl::Getmove3d().y, CControl::Getmove3d().z);
				fprintf(pFile, "	ACTIVE = %d						//�ғ�����\n", CControl::GetActiveTime());
				fprintf(pFile, "	MAXSIZE = %.1f						//�t�B�[���h�ő�T�C�Y\n", CControl::GetMaxSize());
				fprintf(pFile, "	DENSITY = %d						//�����x\n", CControl::GetDensity());

				break;
			case(5):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
				fprintf(pFile, "	DENSITY = %d						//�����x\n", CControl::GetDensity());
				fprintf(pFile, "	ROTATE = %.2f						//��]\n", CControl::GetRotate());
				fprintf(pFile, "	DISTANCE = %.1f						//���̔�������\n", CControl::GetDistance());
				fprintf(pFile, "	PARTICLETIME = %d						//�������Ԋu\n", CControl::GetParticleTime());
				fprintf(pFile, "	SECONDTIME = %d						//�߂Â��܂ł̎���\n", CControl::GetSecondTime());
				fprintf(pFile, "	MAXSIZE = %.1f						//�A�N�e�B�u�T�C�Y\n", CControl::GetMaxSize());
				fprintf(pFile, "	MOVE = %.1f						//�������Z\n", CControl::Getmove3d().x);
				fprintf(pFile, "	TYPE = %d					//�p�[�e�B�N��(0)or�O��(1)\n", CControl::GetType());
				fprintf(pFile, "	SECONDTYPE = %d					//�ړ������_��\n", CControl::GetSecondType());

				break;
			case(6):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());

				fprintf(pFile, "	ROTATE = %.2f						//��]\n", CControl::GetRotate());
				fprintf(pFile, "	VTX = %d						//���_��\n", CControl::GetVtx());
				fprintf(pFile, "	TYPE = %d					//��(0)or����(1)\n", CControl::GetType());


				break;
			case(7):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());

				fprintf(pFile, "	DISTANCE = %.1f						//�㔭������\n", CControl::GetDistance());
				fprintf(pFile, "	HIGTH = %.1f						//�㋗��\n", CControl::GetHigth());
				fprintf(pFile, "	PARTICLESIZE = %.1f						//�������̕�\n", CControl::GetParticleSize());
				break;
			case(8):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
				fprintf(pFile, "	DENSITY = %d						//���x\n", CControl::GetDensity());

				fprintf(pFile, "	CONTROLBEZIER = %.1f %.1f %.1f						//�x�W�F����_\n", CControl::GetContorolBezierX(), CControl::GetContorolBezierY(), CControl::GetContorolBezierZ());
				fprintf(pFile, "	MOVE = %.1f						//�ړ��i����_�̐��j\n", CControl::Getmove3d().x);

				fprintf(pFile, "	SECONDCOLOR = %d %d %d %d			//�O�Ղ̐F�P\n", (int)CControl::GetParticleColor(1), (int)CControl::GetParticleColor(2), (int)CControl::GetParticleColor(3), (int)CControl::GetParticleColor(4));
				fprintf(pFile, "	SECONDADDCOLOR = %d %d %d %d			//�O�Ղ̐F�P����\n", (int)CControl::GetParticleAddCol(1), (int)CControl::GetParticleAddCol(2), (int)CControl::GetParticleAddCol(3), (int)CControl::GetParticleAddCol(4));

				fprintf(pFile, "	THERDCOLOR = %d %d %d %d				//�O�Ղ̐F�Q\n", (int)CControl::GetTrajectColor(1), (int)CControl::GetTrajectColor(2), (int)CControl::GetTrajectColor(3), (int)CControl::GetTrajectColor(4));
				fprintf(pFile, "	THERDADDCOLOR = %d %d %d %d				//�O�Ղ̐F�Q����\n", (int)CControl::GetTrajectCol(1), (int)CControl::GetTrajectCol(2), (int)CControl::GetTrajectCol(3), (int)CControl::GetTrajectCol(4));

				fprintf(pFile, "	MAXSIZE = %.1f						//�O�ՃT�C�Y\n", CControl::GetMaxSize());
				fprintf(pFile, "	SECONDTEX = %d						//�O�Ճe�N�X�`��\n", CControl::GetSecondTex());
				fprintf(pFile, "	PARTICLETIME = %d						//�O�Վ���\n", CControl::GetParticleTime());

				fprintf(pFile, "	DISTANCE = %.1f						//�^�[�Q�b�g����̃����_������\n", CControl::GetDistance());
				fprintf(pFile, "	SECONDSYNTHETIC = %d			//�O�Ս���\n", (int)CControl::GetParticleSynthetic());
				break;
			case(9):
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
			fprintf(pFile, "	TEXMOVE = %.3f %.3f					//�e�N�X�`���ړ�\n", CControl::GetTexMoveU(), CControl::GetTexMoveV());
			fprintf(pFile, "	TEXNUM = %.1f %.1f					//�e�N�X�`������\n", CControl::GetTexNum().x, CControl::GetTexNum().y);

			fprintf(pFile, "	TEXANIMCOUNT = %d					//�e�N�X�`���A�j���[�V�����J�E���g\n", CControl::GetAnimCont());
			fprintf(pFile, "	TEXSPLIT = %.0f %.0f					//�e�N�X�`��������\n", CControl::GetSplitU(), CControl::GetSplitV());
			fprintf(pFile, "	ANIMPATTERNTYPE = %d					//�A�j���[�V�����p�^�[���^�C�v\n", CControl::GetAnimPatternType());

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
		break;
	case(1):
		m_move3d.y += Move;
		break;
	case(2):
		m_move3d.z += Move;

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
		else if (m_ParticleColor.r < -MAX_COLOR)
		{
			m_ParticleColor.r = -MAX_COLOR;
		}
		break;
	case(2):
		m_ParticleColor.g += nColor;
		if (m_ParticleColor.g > MAX_COLOR)
		{
			m_ParticleColor.g = MAX_COLOR;
		}
		else if (m_ParticleColor.g < -MAX_COLOR)
		{
			m_ParticleColor.g = -MAX_COLOR;
		}
		break;
	case(3):
		m_ParticleColor.b += nColor;
		if (m_ParticleColor.b > MAX_COLOR)
		{
			m_ParticleColor.b = MAX_COLOR;
		}
		else if (m_ParticleColor.b < -MAX_COLOR)
		{
			m_ParticleColor.b = -MAX_COLOR;
		}
		break;
	case(4):
		m_ParticleColor.a += nColor;
		if (m_ParticleColor.a > MAX_COLOR)
		{
			m_ParticleColor.a = MAX_COLOR;
		}
		else if (m_ParticleColor.a < -MAX_COLOR)
		{
			m_ParticleColor.a = -MAX_COLOR;
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
		else if (m_ParticleAddCol.r < -MAX_COLOR)
		{
			m_ParticleAddCol.r = -MAX_COLOR;
		}
		break;
	case(2):
		m_ParticleAddCol.g += nColor;
		if (m_ParticleAddCol.g > MAX_COLOR)
		{
			m_ParticleAddCol.g = MAX_COLOR;
		}
		else if (m_ParticleAddCol.g < -MAX_COLOR)
		{
			m_ParticleAddCol.g = -MAX_COLOR;
		}
		break;
	case(3):
		m_ParticleAddCol.b += nColor;
		if (m_ParticleAddCol.b > MAX_COLOR)
		{
			m_ParticleAddCol.b = MAX_COLOR;
		}
		else if (m_ParticleAddCol.b < -MAX_COLOR)
		{
			m_ParticleAddCol.b = -MAX_COLOR;
		}
		break;
	case(4):
		m_ParticleAddCol.a += nColor;
		if (m_ParticleAddCol.a > MAX_COLOR)
		{
			m_ParticleAddCol.a = MAX_COLOR;
		}
		else if (m_ParticleAddCol.a < -MAX_COLOR)
		{
			m_ParticleAddCol.a = -MAX_COLOR;
		}
		break;
	default:
		assert(false);		//��O����
		break;
	}
}
