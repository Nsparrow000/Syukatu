//*****************************************************************************
// �G�t�F�N�g���� [Effect.cpp]
// Author : �����G��
//*****************************************************************************

#include "Effect.h"
#include "manager.h"
#include "Renderer.h"
#include "control.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_MinColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CEffect::~CEffect()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DXVECTOR2 Size, D3DXVECTOR2 MinSize, int nLife, int nType,int Synthetic)
{
	CScene2D::Init(pos);

	m_Color = color;
	m_MinColor = Mincolor;

	m_Size = Size;
	m_MinSize = MinSize;

	m_nLife = nLife;
	m_bUninit = false;
	
	nSynthetic = Synthetic;
	ColorChange(m_Color);

	CScene2D::SetTexture(nType);	//�I�������ԍ��̃e�N�X�`����\��
	CScene2D::SetWhidth(m_Size.x);
	CScene2D::SetHight(m_Size.y);

	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CEffect::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CEffect::Update()
{
	D3DXVECTOR3 pos = GetPosition();

	m_Size += m_MinSize;

	//�T�C�Y�ύX
	SetWhidth(m_Size.x);
	SetHight(m_Size.y);

	m_nLife--;		//���C�t���Z

	//��ʊO����
	if (pos.y < 0)
	{
		m_bUninit = true;
	}
	else if (pos.y > SCREEN_HEIGHT)
	{
		m_bUninit = true;
	}
	if (pos.x < 0)
	{
		m_bUninit = true;
	}
	else if (pos.x > SCREEN_WIDTH)
	{
		m_bUninit = true;
	}


	//����������0�ɂȂ�����
	if (m_Size.x < 0 || m_Size.y < 0)
	{
		m_bUninit = true;
	}
	//������0�ɂȂ�����
	if (m_nLife < 0)
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
	ColorChange(m_Color);

	//�j��
	if (m_bUninit == true)
	{
		Uninit();
	}

}

//*****************************************************************************
// �`��
//*****************************************************************************
void CEffect::Draw()
{
	// ���_����ݒ�
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	if (nSynthetic == 0)
	{
		//���Z�����֌W
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (nSynthetic == 1)
	{
		//���Z�����̐ݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	//����ȊO�̐��l�͉��Z������
	else
	{
		//���Z�����֌W
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	CScene2D::Draw();

	//Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//�ʏ퍇���ɖ߂�(���Z����)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


