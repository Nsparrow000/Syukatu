//*****************************************************************************
// (�}�E�X�Ɍ������Ĕ��ł�)�G�t�F�N�g���� [MouseTracking.cpp]
// Author : �����G��
//*****************************************************************************
#include "MouseTracking.h"
#include "manager.h"
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CMouseTracking::CMouseTracking(int nPriority) : CEffect(nPriority)
{
	m_move = {};
	m_Vec = {};
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CMouseTracking::~CMouseTracking()
{

}

//*****************************************************************************
//	������
//*****************************************************************************
HRESULT CMouseTracking::Init(D3DXVECTOR3 pos,
	D3DXVECTOR2 move,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	D3DXVECTOR2 Size,
	D3DXVECTOR2 MinSize,
	int nLife, int nType,
	D3DXVECTOR3 Endpos,
	int Diffusion,
	int UninitVectl,
	int Synthetic,
	int Distance,
	D3DXVECTOR3 Playerpos,
	D3DXVECTOR3 rot)
{

	CEffect::Init(pos, color, Mincolor, Size, MinSize, nLife, nType, Synthetic);
	m_Endpos = pos;
	m_Vec = Playerpos - Endpos;
	m_move = move;
	m_PlayerPos = Playerpos;

	m_UninitVectl = UninitVectl;
	m_SerectRot = rot;
	//�Œ�ۏ�
	int Lowest = Diffusion;
	if (Lowest <= 0)
	{
		Lowest = 1;
	}

	float randAngle = float(rand() % Lowest) - float(rand() % Lowest);
	randAngle /= 100.0f;

	m_fAngle = (float)atan2(m_Vec.x, m_Vec.y);		//�p�x

	m_fAngle += randAngle;
	m_pos += D3DXVECTOR3(pos.x + sinf(-m_fAngle + m_SerectRot.y) * Distance, pos.y + cosf(-m_fAngle + m_SerectRot.y) * Distance, 0.0f);
	SetPosition(m_pos);
	CScene2D::SetRotate(m_pos, -m_fAngle + D3DX_PI / 4 + m_SerectRot.y, -m_fAngle  + D3DX_PI / 4 + m_SerectRot.y, m_Size.x);

	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CMouseTracking::Uninit()
{
	CEffect::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CMouseTracking::Update()
{

	m_Vec = m_PlayerPos - m_Endpos;

	m_Vectl = sqrtf(m_Vec.x * m_Vec.x + m_Vec.y *  m_Vec.y);

	if (m_Vectl >= m_UninitVectl)
	{
		m_bUninit = true;
	}

	//m_pos += D3DXVECTOR3(sinf(-m_fAngle + m_SerectRot.y) * - m_move.x, cosf(-m_fAngle + m_SerectRot.y) * m_move.x, 0.0f);
	

	SetPosition(m_pos);
	CScene2D::SetRotate(m_pos, -m_fAngle + D3DX_PI / 4 + m_SerectRot.y, -m_fAngle + D3DX_PI / 4 + m_SerectRot.y, m_Size.x);

	CEffect::Update();

}

//*****************************************************************************
//�`��
//*****************************************************************************
void CMouseTracking::Draw()
{
	CEffect::Draw();
}

//*****************************************************************************
//�쐬
//*****************************************************************************
CMouseTracking *CMouseTracking::Create(D3DXVECTOR3 pos,
	D3DXVECTOR2 move,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	D3DXVECTOR2 Size,
	D3DXVECTOR2 MinSize,
	int nLife, int nType,
	D3DXVECTOR3 Endpos,
	int Diffusion,
	int UninitVectl,
	int Synthetic,
	int Distance,
	D3DXVECTOR3 Playerpos,
	D3DXVECTOR3 rot)
{
	CMouseTracking *pMouseTracking = NULL;
	pMouseTracking = new CMouseTracking(CManager::PRIORITY_EFFECT);		//�������m��
										//NULL�`�F�b�N
	if (pMouseTracking != NULL)
	{
		pMouseTracking->Init(pos,
			move,
			color,
			Mincolor,
			Size,
			MinSize,
			nLife, nType,
			Endpos, Diffusion,
			UninitVectl, Synthetic,
			Distance, Playerpos, rot);
	}

	return pMouseTracking;
}
