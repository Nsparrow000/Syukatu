//=============================================================================
// �����_�����O���� [renderer.h]
// Author : �����G��
//=============================================================================
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "camera.h"

#include "control.h"
#include "seteffect.h"

#include <assert.h>

//�ÓI�����o�ϐ�
CCamera *CRenderer::m_pCamera = NULL;
HWND CRenderer::m_wnd = NULL;

CRenderer::CRenderer()
{

}

CRenderer::~CRenderer()
{

}

HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

																// �f�o�C�X�̐���
																// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
																// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	m_wnd = hWnd;

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O���s��Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

																			// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

																			// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);		//�����̑傫��

	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 200.0f, -300.0f), 700.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	

	return S_OK;
}

void CRenderer::Uninit()
{
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
	}

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

}

void CRenderer::Update()
{
	m_pCamera->Update();

	GetMouse();
	CScene::UpdateAll();
}

void CRenderer::Draw()
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(100, 100, 100, 0), 1.0f, 0); //�w�i�̐F��ς����

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �|���S���̕`�揈��
		CScene::DrawAll();

		// FPS�\��
		DrawFPS();


		DrawText();
		DrawTextLeft();

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CRenderer::DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", GetFPS());

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//*****************************************************************************
//��ʃe�L�X�g�\��
//*****************************************************************************
void CRenderer::DrawText()
{
	CManager::MODE mode = CManager::GetMode();

	RECT rect = { 0, 30, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[1024];

	bool bMouse = CControl::GetMouseCursor();
	bool bTap = CControl::GetTap();

	int nNum = sprintf(&str[0], "�I���J���[ [��][��]�F%d\n", CControl::GetSerectColor());

	nNum += sprintf(&str[nNum], "�J���[�l [+][-]�F(%d %d %d %d)\n", CControl::GetControlCoror(1), CControl::GetControlCoror(2), CControl::GetControlCoror(3), CControl::GetControlCoror(4));

	nNum += sprintf(&str[nNum], "�J���[�����l [+][-]�F(%d %d %d %d)\n", CControl::GetChangeCol(1), CControl::GetChangeCol(2), CControl::GetChangeCol(3), CControl::GetChangeCol(4));

	nNum += sprintf(&str[nNum], "���� [+][-]�F(%d)\n", CControl::GetLife());
	nNum += sprintf(&str[nNum], "\n");
	nNum += sprintf(&str[nNum], "�G�t�F�N�g�p�^�[�� [��][��]�F(%d)\n", CControl::GetPattern());

	nNum += sprintf(&str[nNum], "\n");

	switch (mode)
	{
		//*****************************************************************************
		//2D���[�h
	case(CManager::MODE_2D):

		nNum += sprintf(&str[nNum], "�T�C�Y [+][-]�F(%.1f)\n", CControl::GetSize());
		nNum += sprintf(&str[nNum], "�T�C�Y���� [+][-]�F(%.1f)\n", CControl::GetChangeSize());
		nNum += sprintf(&str[nNum], "\n");
		nNum += sprintf(&str[nNum], "���x [+][-]�F(%d)\n", CControl::GetDensity());
		nNum += sprintf(&str[nNum], "�e�N�X�`�� [��][��]�F(%d)\n", CControl::GetTex());
		nNum += sprintf(&str[nNum], "\n");
		if (bMouse == true)
		{
			nNum += sprintf(&str[nNum], "�}�E�X�Ǐ] [M]�F(ON)\n");
		}
		else
		{
			nNum += sprintf(&str[nNum], "�}�E�X�Ǐ] [M]�F(OFF)\n");
		}
		if (bTap == true)
		{
			nNum += sprintf(&str[nNum], "Tap���[�h [N]�F(ON)\n");
		}
		else
		{
			nNum += sprintf(&str[nNum], "Tap���[�h [N]�F(OFF)\n");
		}
		nNum += sprintf(&str[nNum], "\n");
		nNum += sprintf(&str[nNum], "�e�L�X�g�o�� [�@]\n");
		nNum += sprintf(&str[nNum], "���ԃZ�[�u�̃��[�h [�@]\n");
		nNum += sprintf(&str[nNum], "\n");


		nNum += sprintf(&str[nNum], "�������WXY�F(%.1f %.1f)\n", CSetEffect::GetSetPos().x, CSetEffect::GetSetPos().y);

		nNum += sprintf(&str[nNum], "\n");

		switch (CControl::GetPattern())
		{
		case(0):
			nNum += sprintf(&str[nNum], "�ړ��lX [+][-] : (%.1f) \n", CControl::GetMove().x);
			nNum += sprintf(&str[nNum], "�ړ��lY [+][-] : (%.1f) \n", CControl::GetMove().y);
			nNum += sprintf(&str[nNum], "�ړ����Z�l X[+][-]�F(%.1f)\n", CControl::GetAddMove().x);
			nNum += sprintf(&str[nNum], "�ړ����Z�l Y[+][-]�F(%.1f)\n", CControl::GetAddMove().y);
			break;
		case(1):
			nNum += sprintf(&str[nNum], "�ړ��l [+][-]�F(%.1f)\n", CControl::GetMove().x);
			nNum += sprintf(&str[nNum], "�g�U�� [+][-]�F(%.2f)\n", (float)CControl::GetDiffusion() / 100);
			nNum += sprintf(&str[nNum], "�����鋗�� [+][-]�F(%d)\n", CControl::GetUninitVectl());
			nNum += sprintf(&str[nNum], "�o������ [+][-]�F(%.1f)\n", CControl::GetDistance());

			nNum += sprintf(&str[nNum], "\n");
			break;
		case(2):
			nNum += sprintf(&str[nNum], "�ړ��lX [+][-] : (%.1f)\n", CControl::GetMove().x);
			nNum += sprintf(&str[nNum], "�ړ��lY [+][-] : (%.1f)\n", CControl::GetMove().y);

			nNum += sprintf(&str[nNum], "��] [+][-] �F(%.2f)\n", CControl::GetRotate());
			break;
		default:
			break;
		}
		nNum += sprintf(&str[nNum], "\n");

		nNum += sprintf(&str[nNum], "\n");

		nNum += sprintf(&str[nNum], "3D���[�h�� [ENTER]\n");
		nNum += sprintf(&str[nNum], "\n");

		break;

		//*****************************************************************************
		//3D���[�h
	case(CManager::MODE_3D):
		nNum += sprintf(&str[nNum], "���샂�[�h [F5]�F");

		if (CControl::GetPlayerMode() == true)
		{
			nNum += sprintf(&str[nNum], "�v���C���[����\n");
			nNum += sprintf(&str[nNum], "�ړ� WASD\n");
			nNum += sprintf(&str[nNum], "SPACE �W�����v\n");
			nNum += sprintf(&str[nNum], "���N���b�N �U��(�O�Պm�F)\n\n");
		}
		else
		{
			nNum += sprintf(&str[nNum], "�G�t�F�N�g����\n");
			nNum += sprintf(&str[nNum], "�v���C���[�ꕔ�X�V��~\n");

			nNum += sprintf(&str[nNum], "\n");
			if (CControl::GetPattern() != 0)
			{
				nNum += sprintf(&str[nNum], "�T�C�Y [+][-]�F(%.1f)\n", CControl::GetSize());
				nNum += sprintf(&str[nNum], "�T�C�Y���� [+][-]�F(%.1f)\n", CControl::GetChangeSize());
				nNum += sprintf(&str[nNum], "���x [+][-]�F(%d)\n", CControl::GetDensity());

			}
			nNum += sprintf(&str[nNum], "�e�N�X�`�� [��][��]�F(%d)\n", CControl::GetTex());
			nNum += sprintf(&str[nNum], "\n");


			switch (CControl::GetPattern())
			{
			case(0)://�O�Ճp�^�[��
				nNum += sprintf(&str[nNum], "���N���b�N �U��(�O�Պm�F) \n\n");

				nNum += sprintf(&str[nNum], "�O�Ր�[�����F [+][-]�F(%d %d %d %d)\n", CControl::GetTrajectColor(1), CControl::GetTrajectColor(2), CControl::GetTrajectColor(3), CControl::GetTrajectColor(4));
				nNum += sprintf(&str[nNum], "�O�Ր�[���� [+][-]�F(%d %d %d %d)\n", CControl::GetTrajectCol(1), CControl::GetTrajectCol(2), CControl::GetTrajectCol(3), CControl::GetTrajectCol(4));

				nNum += sprintf(&str[nNum], "�O�Վ茳���f�� [+][-] �F(%d / 14)\n", CControl::GetModelNum());
				nNum += sprintf(&str[nNum], "�O�Ր�[���f�� [+][-] �F(%d / 14)\n", CControl::GetTrajectModelNum());

				nNum += sprintf(&str[nNum], "\n");
				break;
			case(1)://�X�g���[�g�p�^�[��
				nNum += sprintf(&str[nNum], "�ړ��l X[+][-]�F%.1f\n", CControl::Getmove3d().x);
				nNum += sprintf(&str[nNum], "�ړ��l Y[+][-]�F%.1f\n", CControl::Getmove3d().y);
				nNum += sprintf(&str[nNum], "�ړ��l Z[+][-]�F%.1f\n", CControl::Getmove3d().z);

				nNum += sprintf(&str[nNum], "�o���ʒu�̋��� [+][-]�F%.1f\n", CControl::GetDistance());
				nNum += sprintf(&str[nNum], "�o���ʒu�p�^�[�� [+][-]�F%d\n", CControl::GetSecondType());
				nNum += sprintf(&str[nNum], "�����_���ړ��p�^�[�� [+][-]�F%d\n", CControl::GetType());
				nNum += sprintf(&str[nNum], "�������Ԋu [+][-]�F%d\n", CControl::GetParticleTime());

				break;
			case(2)://�Z�킹
				nNum += sprintf(&str[nNum], "�����l�̍ő� �ŏ�[+][-] �F(%d)\n", CControl::GetRandMove1());
				nNum += sprintf(&str[nNum], "�������f��1 [+][-] �F(%d / 14)\n", CControl::GetModelNum());
				nNum += sprintf(&str[nNum], "�������f��2 [+][-] �F(%d / 14)\n", CControl::GetTrajectModelNum());
				break;
			case(3):
				nNum += sprintf(&str[nNum], "��] [+][-]�F%.2f\n", CControl::GetRotate());

				nNum += sprintf(&str[nNum], "���ړ��l [+][-]�F%.1f\n", CControl::Getmove3d().x);
				nNum += sprintf(&str[nNum], "���T�C�Y [+][-]�F%.1f\n", CControl::GetParticleSize());
				nNum += sprintf(&str[nNum], "�������ő厞�� [+][-]�F%d\n", CControl::GetParticleTime());
				nNum += sprintf(&str[nNum], "�������n�_ [+][-]�F%.1f\n", CControl::GetDistance());
				nNum += sprintf(&str[nNum], "\n");
				nNum += sprintf(&str[nNum], "�A�N�e�B�u���� [+][-]�F%d\n", CControl::GetActiveTime());
				nNum += sprintf(&str[nNum], "���傫���ύX [+][-]�F%.1f\n", CControl::GetParticleAddSize());
				nNum += sprintf(&str[nNum], "�ő�̑傫�� [+][-]�F%.1f\n", CControl::GetMaxSize());
				nNum += sprintf(&str[nNum], "\n");
				nNum += sprintf(&str[nNum], "���F [+][-]�F(%d %d %d %d)\n", CControl::GetParticleColor(1), CControl::GetParticleColor(2), CControl::GetParticleColor(3), CControl::GetParticleColor(4));
				nNum += sprintf(&str[nNum], "���F���� [+][-]�F(%d %d %d %d)\n", CControl::GetParticleAddCol(1), CControl::GetParticleAddCol(2), CControl::GetParticleAddCol(3), CControl::GetParticleAddCol(4));
				nNum += sprintf(&str[nNum], "������ [+][-]�F(%d)\n", CControl::GetParticleSynthetic());
				nNum += sprintf(&str[nNum], "�ғ����̑傫���ύX [+][-]�F(%.1f)\n", CControl::GetAvctiveAddSize());

				break;
			case(4):
				nNum += sprintf(&str[nNum], "�ړ��l X[+][-]�F%.1f\n", CControl::Getmove3d().x);
				nNum += sprintf(&str[nNum], "�ړ��l Y[+][-]�F%.1f\n", CControl::Getmove3d().y);
				nNum += sprintf(&str[nNum], "�ړ��l Z[+][-]�F%.1f\n", CControl::Getmove3d().z);

				nNum += sprintf(&str[nNum], "�A�N�e�B�u���� [+][-]�F%d\n", CControl::GetActiveTime());
				nNum += sprintf(&str[nNum], "�ő�̑傫�� [+][-]�F%.1f\n", CControl::GetMaxSize());

				break;
			case(5):
				nNum += sprintf(&str[nNum], "��] [+][-]�F%.2f\n", CControl::GetRotate());
				nNum += sprintf(&str[nNum], "�������n�_ [+][-]�F%.1f\n", CControl::GetDistance());
				nNum += sprintf(&str[nNum], "������ [+][-]�F%d\n", CControl::GetParticleTime());
				nNum += sprintf(&str[nNum], "�߂Â��܂ł̎��� [+][-]�F%d\n", CControl::GetSecondTime());
				nNum += sprintf(&str[nNum], "�A�N�e�B�u�ɂȂ�܂ł̑傫�� [+][-]�F%.1f\n", CControl::GetMaxSize());
				nNum += sprintf(&str[nNum], "�ړ��l[+][-]�F%.1f\n", CControl::Getmove3d().x);
				nNum += sprintf(&str[nNum], "�G�t�F�N�g�^�C�v[+][-]�F%d\n", CControl::GetType());
				nNum += sprintf(&str[nNum], "�ړ��^�C�v[+][-]�F%d\n", CControl::GetSecondType());

				break;
			case(6):
				nNum += sprintf(&str[nNum], "��] [+][-]�F%.2f\n", CControl::GetRotate());
				nNum += sprintf(&str[nNum], "���_�� [+][-]�F%d\n", CControl::GetVtx());
				nNum += sprintf(&str[nNum], "�����^�C�v [+][-]�F%d\n", CControl::GetType());
				break;
			case(7):
				nNum += sprintf(&str[nNum], "���� [+][-]�F%.1f\n", CControl::GetDistance());
				nNum += sprintf(&str[nNum], "���� [+][-]�F%.1f\n", CControl::GetHigth());
				nNum += sprintf(&str[nNum], "�������� [+][-]�F%.1f\n", CControl::GetParticleSize());
				break;
			case(8):
				nNum += sprintf(&str[nNum], "����_ X[+][-]�F%.1f\n", CControl::GetContorolBezierX());
				nNum += sprintf(&str[nNum], "����_ Y[+][-]�F%.1f\n", CControl::GetContorolBezierY());
				nNum += sprintf(&str[nNum], "����_ Z[+][-]�F%.1f\n", CControl::GetContorolBezierZ());
				nNum += sprintf(&str[nNum], "�ړ�(�ʉߓ_�̐�) [+][-]�F%.0f\n", CControl::Getmove3d().x);

				nNum += sprintf(&str[nNum], "�O�ՂP�F [+][-]�F(%d %d %d %d)\n", CControl::GetParticleColor(1), CControl::GetParticleColor(2), CControl::GetParticleColor(3), CControl::GetParticleColor(4));
				nNum += sprintf(&str[nNum], "�O�ՂP���� [+][-]�F(%d %d %d %d)\n", CControl::GetParticleAddCol(1), CControl::GetParticleAddCol(2), CControl::GetParticleAddCol(3), CControl::GetParticleAddCol(4));

				nNum += sprintf(&str[nNum], "�O�ՂQ�F [+][-]�F(%d %d %d %d)\n", CControl::GetTrajectColor(1), CControl::GetTrajectColor(2), CControl::GetTrajectColor(3), CControl::GetTrajectColor(4));
				nNum += sprintf(&str[nNum], "�O�ՂQ���� [+][-]�F(%d %d %d %d)\n", CControl::GetTrajectCol(1), CControl::GetTrajectCol(2), CControl::GetTrajectCol(3), CControl::GetTrajectCol(4));
				nNum += sprintf(&str[nNum], "�O�ՃT�C�Y [+][-]�F%.1f\n", CControl::GetMaxSize());
				nNum += sprintf(&str[nNum], "�O�Ճe�N�X�`�� [+][-]�F%d\n", CControl::GetSecondTex());
				nNum += sprintf(&str[nNum], "�O�Վ��� [+][-]�F%d\n", CControl::GetParticleTime());
				nNum += sprintf(&str[nNum], "�^�[�Q�b�g�����_������ [+][-]�F%.1f\n", CControl::GetDistance());
				nNum += sprintf(&str[nNum], "�O�Ս��� [+][-]�F%d\n", CControl::GetParticleSynthetic());
				break;
			case(9):
				break;
			default:
				break;
			}
			nNum += sprintf(&str[nNum], "\n");

			nNum += sprintf(&str[nNum], "�e�L�X�g�o�� [�@]\n");
			nNum += sprintf(&str[nNum], "���ԃ��[�h [�@]\n");
			nNum += sprintf(&str[nNum], "�v���Z�b�g���[�h [�@]\n");

		}
		nNum += sprintf(&str[nNum], "2D���[�h�� [ENTER]\n");
		break;

	default:
		assert(false);
		break;
	}
	nNum += sprintf(&str[nNum], "���� [��][��]�F(%d)\n", CControl::GetSynthetic());

	nNum += sprintf(&str[nNum], "%.0f %.0f\n", GetMousePos().x, GetMousePos().y);

	// �e�L�X�g�̕`��
	m_pFont->DrawText(
		NULL,
		&str[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));

}

//*****************************************************************************
//��ʃe�L�X�g�\������
//*****************************************************************************
void CRenderer::DrawTextLeft()
{

	RECT rect = { 900, 30, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[1024];

	int nNum = sprintf(&str[0], "\n");

	if (CManager::MODE mode = CManager::GetMode())
	{
		nNum += sprintf(&str[nNum], "�e�N�X�`���ړ� U [+][-]�F%.3f\n", CControl::GetTexMoveU());
		nNum += sprintf(&str[nNum], "�e�N�X�`���ړ� V [+][-]�F%.3f\n", CControl::GetTexMoveV());
		nNum += sprintf(&str[nNum], "�e�N�X�`������ U [+][-]�F%.1f\n", CControl::GetTexNum().x);
		nNum += sprintf(&str[nNum], "�e�N�X�`������ V [+][-]�F%.1f\n", CControl::GetTexNum().y);

		nNum += sprintf(&str[nNum], "�e�N�X�`�������� U [+][-]�F%.0f\n", CControl::GetSplitU());
		nNum += sprintf(&str[nNum], "�e�N�X�`�������� V [+][-]�F%.0f\n", CControl::GetSplitV());
		nNum += sprintf(&str[nNum], "�p�^�[���J�E���g  [+][-]�F%d\n", CControl::GetAnimCont());
		nNum += sprintf(&str[nNum], "�����_����  [+][-]�F%d\n", CControl::GetAnimPatternType());


		nNum += sprintf(&str[nNum], "�v���Z�b�g�Đ�[F1]\n");
		nNum += sprintf(&str[nNum], "�S�Ẵv���Z�b�g�Đ�[F2]\n");
		nNum += sprintf(&str[nNum], "���ԍ��t���Ńv���Z�b�g�Đ�[F3]\n");

		switch (CControl::GetPattern())
		{

		case(1):
			break;
		case(2):
			break;
		case(3):
		case(4):
			nNum += sprintf(&str[nNum], "�Đ�[SPACE]\n");

			break;
		default:
			break;
		}
	}

	// �e�L�X�g�̕`��
	m_pFont->DrawText(
		NULL,
		&str[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));

}
