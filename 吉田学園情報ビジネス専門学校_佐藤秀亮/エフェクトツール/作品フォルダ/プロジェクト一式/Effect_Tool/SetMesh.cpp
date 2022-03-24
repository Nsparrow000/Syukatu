//=============================================================================
// ���b�V���̐ݒ� [SetMesh.cpp]
// Author : �����G��
//=============================================================================
#include "SetMesh.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CSetMesh::CSetMesh(int nPriority) : CMeshEffect(nPriority)
{
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_MinColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CSetMesh::~CSetMesh()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CSetMesh::Init(D3DXVECTOR3 Vtxpos1, D3DXVECTOR3 Vtxpos2, D3DXVECTOR3 VtxOldpos1, D3DXVECTOR3 VtxOldpos2, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DCOLORVALUE Trajectcolor, D3DCOLORVALUE TrajectMincolor, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, int nTex, int nLife, EFFECT_TYPE nType)
{
	CMeshEffect::Init(Vtxpos1, Vtxpos2, VtxOldpos1, VtxOldpos2, Size, nTex, nLife, nType);

	m_Color = color;
	m_MinColor = Mincolor;

	m_TrajectColor = Trajectcolor;
	m_TrajectMinColor = TrajectMincolor;

	m_Size = Size;
	m_MinSize = MinSize;
	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CSetMesh::Uninit()
{
	CMeshEffect::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CSetMesh::Update()
{
	//�T�C�Y�ύX
	m_Size += m_MinSize;

	if (m_Size.x < 0)
	{
		m_bUninit = true;
	}
	if (m_Size.y < 0)
	{
		m_bUninit = true;
	}

	//�J���[�ύX
	m_Color.r += m_MinColor.r;
	m_Color.g += m_MinColor.g;
	m_Color.b += m_MinColor.b;
	m_Color.a += m_MinColor.a;

	//�J���[��0�ȉ��̎�
	if (m_Color.r < 0)
	{
		m_Color.r = 0;
	}
	if (m_Color.g < 0)
	{
		m_Color.g = 0;
	}
	if (m_Color.b < 0)
	{
		m_Color.b = 0;
	}
	if (m_Color.a < 0)
	{
		m_Color.a = 0;
	}

	//�J���[��255�ȏ�̎�
	if (m_Color.r > 255)
	{
		m_Color.r = 255;
	}
	if (m_Color.g > 255)
	{
		m_Color.g = 255;
	}
	if (m_Color.b > 255)
	{
		m_Color.b = 255;
	}
	if (m_Color.a > 255)
	{
		m_Color.a = 255;
	}

	//�J���[�ύX
	m_TrajectColor.r += m_TrajectMinColor.r;
	m_TrajectColor.g += m_TrajectMinColor.g;
	m_TrajectColor.b += m_TrajectMinColor.b;
	m_TrajectColor.a += m_TrajectMinColor.a;

	//�J���[��0�ȉ��̎�
	if (m_TrajectColor.r < 0)
	{
		m_TrajectColor.r = 0;
	}
	if (m_TrajectColor.g < 0)
	{
		m_TrajectColor.g = 0;
	}
	if (m_TrajectColor.b < 0)
	{
		m_TrajectColor.b = 0;
	}
	if (m_TrajectColor.a < 0)
	{
		m_TrajectColor.a = 0;
	}

	//�J���[��255�ȏ�̎�
	if (m_TrajectColor.r > 255)
	{
		m_TrajectColor.r = 255;
	}
	if (m_TrajectColor.g > 255)
	{
		m_TrajectColor.g = 255;
	}
	if (m_TrajectColor.b > 255)
	{
		m_TrajectColor.b = 255;
	}
	if (m_TrajectColor.a > 255)
	{
		m_TrajectColor.a = 255;
	}


	ColorChange(m_Color, m_TrajectColor);
	SetSize();
	CMeshEffect::Update();
}
//*****************************************************************************
// �`��
//*****************************************************************************
void CSetMesh::Draw()
{
	CMeshEffect::Draw();
}