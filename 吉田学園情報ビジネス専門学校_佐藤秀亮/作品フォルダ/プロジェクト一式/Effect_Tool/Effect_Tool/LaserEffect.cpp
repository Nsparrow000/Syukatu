//*****************************************************************************
// (���[�U�[)�G�t�F�N�g���� [LaserEffect.cpp]
// Author : �����G��
//*****************************************************************************

#include "LaserEffect.h"
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CLaserEffect::CLaserEffect(int nPriority) : CEffect(nPriority)
{
	m_Vector1 = {};
	m_Vector2 = {};
	m_OldVector1 = {};
	m_OldVector2 = {};
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CLaserEffect::~CLaserEffect()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CLaserEffect::Init(
	D3DXVECTOR3 Vector1,
	D3DXVECTOR3 Vector2,
	D3DXVECTOR3 OldVector1,
	D3DXVECTOR3 OldVector2,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nLife, int nType)
{
	CEffect::Init(D3DXVECTOR3(0.0f,0.0f,0.0f), color, Mincolor, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 (0.0f,0.0f), nLife, nType);
	
	m_Vector1 = Vector1;
	m_Vector2 = Vector2;
	m_OldVector1 = OldVector1;
	m_OldVector2 = OldVector2;

	CEffect::UpdateLaser(m_Vector1, m_Vector2, m_OldVector1, m_OldVector2);

	return S_OK;

}

//*****************************************************************************
//�I��
//*****************************************************************************
void CLaserEffect::Uninit()
{
	CEffect::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CLaserEffect::Update()
{
	D3DXVECTOR3 pos = GetPosition();

	CEffect::UpdateLaser(m_Vector1, m_Vector2, m_OldVector1, m_OldVector2);

	CEffect::Update();
}

//*****************************************************************************
//�`��
//*****************************************************************************
void CLaserEffect::Draw()
{
	CEffect::Draw();
}

//*****************************************************************************
//�쐬
//*****************************************************************************
CLaserEffect *CLaserEffect::Create(
	D3DXVECTOR3 Vector1,
	D3DXVECTOR3 Vector2,
	D3DXVECTOR3 OldVector1,
	D3DXVECTOR3 OldVector2,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nLife, int nType)
{
	CLaserEffect *pLaserEffect = NULL;
	pLaserEffect = new CLaserEffect(3);		//�������m��
												//NULL�`�F�b�N
	if (pLaserEffect != NULL)
	{
		pLaserEffect->Init(Vector1, Vector2, OldVector1, OldVector2, color, Mincolor, nLife, nType);
	}

	return pLaserEffect;
}