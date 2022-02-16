//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : �O��q��
//
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
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 200.0f, -300.0f), 400.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	

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
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0); //�w�i�̐F��ς����

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �|���S���̕`�揈��
		CScene::DrawAll();

		// FPS�\��
		DrawFPS();


		DrawText();

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

	nNum += sprintf(&str[nNum], "�J���[�l [Q][A] �����_��[1]�F(%d %d %d %d)\n", CControl::GetControlCoror(1), CControl::GetControlCoror(2), CControl::GetControlCoror(3), CControl::GetControlCoror(4));

	nNum += sprintf(&str[nNum], "�J���[�����l [W][S]�F(%d %d %d %d)\n", CControl::GetChangeCol(1), CControl::GetChangeCol(2), CControl::GetChangeCol(3), CControl::GetChangeCol(4));

	nNum += sprintf(&str[nNum], "���� [T][G]�F(%d)\n", CControl::GetLife());
	nNum += sprintf(&str[nNum], "\n");
	nNum += sprintf(&str[nNum], "�G�t�F�N�g�p�^�[�� [��][��]�F(%d)\n", CControl::GetPattern());



	nNum += sprintf(&str[nNum], "\n");

	switch (mode)
	{
		//*****************************************************************************
		//2D���[�h
	case(CManager::MODE_2D):

		if (bMouse == true)
		{
			nNum += sprintf(&str[nNum], "�}�E�X�Ǐ] [M]�F(ON)\n");
		}
		else
		{
			nNum += sprintf(&str[nNum], "�}�E�X�Ǐ] [M]�F(OFF)\n");
		}

		nNum += sprintf(&str[nNum], "�������WXY�F(%.1f %.1f)\n", CSetEffect::GetSetPos().x, CSetEffect::GetSetPos().y);

		nNum += sprintf(&str[nNum], "\n");

		switch (CControl::GetPattern())
		{
		case(1):
			//�����_��ON�Ȃ�ړ��l�̕\��
			if (CControl::GetRandMoveX() == false && CControl::GetRandMoveY() == false)
			{
				nNum += sprintf(&str[nNum], "�ړ��l X:[Y][H]�����_��ON[6] Y:[U][J]�����_��ON[7]�F(%.1f %.1f)\n", CControl::GetMove().x, CControl::GetMove().y);
			}
			else if (CControl::GetRandMoveX() == true && CControl::GetRandMoveY() == false)
			{
				nNum += sprintf(&str[nNum], "�ړ��l X�����_��OFF[6] Y:[U][J]�����_��ON[7]�F(RANDOM %.1f)\n", CControl::GetMove().y);
			}
			else if (CControl::GetRandMoveY() == true && CControl::GetRandMoveX() == false)
			{
				nNum += sprintf(&str[nNum], "�ړ��l X:[Y][H]�����_��ON[6] Y:�����_��OFF[7]�F(%.1f RANDOM)\n", CControl::GetMove().x);
			}
			else
			{
				nNum += sprintf(&str[nNum], "�ړ��l X�����_��OFF[6] Y:�����_��OFF[7]�F(RANDOM RANDOM)\n");
			}

			nNum += sprintf(&str[nNum], "�ړ����Z�l X[I][K] Y[O][L]�F(%.1f %.1f)\n", CControl::GetAddMove().x, CControl::GetAddMove().y);
			break;
		case(2):
			if (CControl::GetRandMoveX() == false)
			{
				nNum += sprintf(&str[nNum], "�ړ��l [Y][H] �����_��ON[6]�F(%.1f)\n", CControl::GetMove().x);
			}
			else
			{
				nNum += sprintf(&str[nNum], "�ړ��l �����_��OFF[6]�F(RANDOM)\n");
			}
			nNum += sprintf(&str[nNum], "�g�U�� [I][K]�F(%.2f)\n", (float)CControl::GetDiffusion() / 100);
			nNum += sprintf(&str[nNum], "�����钼������ [U][J]�F(%d)\n", CControl::GetUninitVectl());
			nNum += sprintf(&str[nNum], "\n");
			nNum += sprintf(&str[nNum], "���}�E�X�Ɍ������Ĕ��ł������\n");
			nNum += sprintf(&str[nNum], "���}�E�X�Ǐ]��ON���Ə�ɔ��ōs���܂�\n");

			break;
		default:
			break;
		}
		nNum += sprintf(&str[nNum], "\n");

		nNum += sprintf(&str[nNum], "�T�C�Y [E][D]�F(%.1f)\n", CControl::GetSize());
		nNum += sprintf(&str[nNum], "�T�C�Y���� [R][F]�F(%.1f)\n", CControl::GetChangeSize());
		nNum += sprintf(&str[nNum], "\n");
		nNum += sprintf(&str[nNum], "���x [C][V]�F(%d)\n", CControl::GetDensity());
		nNum += sprintf(&str[nNum], "�e�N�X�`�� [Z][X]�F(%d)\n", CControl::GetTex());
		nNum += sprintf(&str[nNum], "\n");
		if (bTap == true)
		{
			nNum += sprintf(&str[nNum], "Tap���[�h [N]�F(ON)\n");
		}
		else
		{
			nNum += sprintf(&str[nNum], "Tap���[�h [N]�F(OFF)\n");
		}


		nNum += sprintf(&str[nNum], "\n");
		nNum += sprintf(&str[nNum], "�e�L�X�g�o�� [F9]\n");

		nNum += sprintf(&str[nNum], "3D���[�h�� [ENTER]\n");

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
			if (CControl::GetPattern() != 1)
			{
				nNum += sprintf(&str[nNum], "�T�C�Y [E][D]�F(%.1f)\n", CControl::GetSize());
				nNum += sprintf(&str[nNum], "�T�C�Y���� [R][F]�F(%.1f)\n", CControl::GetChangeSize());
				nNum += sprintf(&str[nNum], "���x [C][V]�F(%d)\n", CControl::GetDensity());
				nNum += sprintf(&str[nNum], "�e�N�X�`�� [Z][X]�F(%d)\n", CControl::GetTex());

			}
			nNum += sprintf(&str[nNum], "\n");


			switch (CControl::GetPattern())
			{
			case(1)://�O�Ճp�^�[��
				nNum += sprintf(&str[nNum], "���N���b�N �U��(�O�Պm�F) \n�����̑��샂�[�h���ƐF�����_�������܂��@�\���Ȃ�����)\n\n");

				nNum += sprintf(&str[nNum], "�O�Ր�[�����F [C][V]�F(%d %d %d %d)\n", CControl::GetTrajectColor(1), CControl::GetTrajectColor(2), CControl::GetTrajectColor(3), CControl::GetTrajectColor(4));
				nNum += sprintf(&str[nNum], "�O�Ր�[���� [B][N]�F(%d %d %d %d)\n", CControl::GetTrajectCol(1), CControl::GetTrajectCol(2), CControl::GetTrajectCol(3), CControl::GetTrajectCol(4));

				nNum += sprintf(&str[nNum], "�O�Վ茳���f�� [Z] �F(%d / 14)\n", CControl::GetModelNum());
				nNum += sprintf(&str[nNum], "�O�Ր�[���f�� [X] �F(%d / 14)\n", CControl::GetTrajectModelNum());

				nNum += sprintf(&str[nNum], "\n");
				nNum += sprintf(&str[nNum], "�����̃p�^�[���̓J���[�l���茳�̐F�̖����ɂȂ�܂�\n");
				nNum += sprintf(&str[nNum], "�����ƑI���J���[�͐�[�A�茳�Ƃ��ɓ����ł�\n");
				nNum += sprintf(&str[nNum], "���O�Ղ̒����ς��������̓v���C���[�̃e�L�X�g�������Ă�������\n  �s�ւł��߂�Ȃ���\n");
				break;
			case(2)://�X�g���[�g�p�^�[��
				nNum += sprintf(&str[nNum], "�ړ��l X[U][J] Y[I][K] Z[O][L]�FX�F%.1f Y�F%.1f Z�F%.1f\n", CControl::Getmove3d().x, CControl::Getmove3d().y, CControl::Getmove3d().z);
				break;
			case(3)://�Z�킹��p�[�e�B�N��
				nNum += sprintf(&str[nNum], "�����l�̍ő� �ŏ�[Y][H] �F(%d)\n", CControl::GetRandMove1());
				nNum += sprintf(&str[nNum], "�������f�� [Z] �F(%d / 14)\n", CControl::GetModelNum());
				nNum += sprintf(&str[nNum], "��r���f�� [X] �F(%d / 14)\n", CControl::GetTrajectModelNum());
				break;
			default:
				assert(false);
				break;
			}
			nNum += sprintf(&str[nNum], "\n");

			nNum += sprintf(&str[nNum], "�e�L�X�g�o�� [F9]\n");

		}
		nNum += sprintf(&str[nNum], "2D���[�h�� [ENTER]\n");
		break;

	default:
		assert(false);
		break;
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