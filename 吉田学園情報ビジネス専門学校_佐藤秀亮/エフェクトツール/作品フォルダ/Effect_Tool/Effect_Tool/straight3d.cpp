//=============================================================================
// (����)3D�G�t�F�N�g���� [Straight3D.cpp]
// Author : �����G��
// 10/24 ����������(����
//=============================================================================
#include "Straight3D.h"

#include "renderer.h"
#include "Camera.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStraight3D::CStraight3D(int nPriority) : CBillEffect(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStraight3D::~CStraight3D()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CStraight3D::Init(D3DXVECTOR3 pos,
	D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	D3DXVECTOR3 move,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nType,
	int nLife,
	CStraight3D::MOVE_PATTERN Pattrn,
	D3DXVECTOR3 Target,
	int Synsetic)
{
	m_move = move;

	CBillEffect::Init(Size, MinSize, color, Mincolor, nType, nLife);
	m_nSynthenic = Synsetic;
	m_pCamera = CManager::GetRenderer()->GetCamera();
	m_Pattern = Pattrn;
	m_Target = Target;

	SetPos(pos);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CStraight3D::Uninit()
{
	CBillEffect::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CStraight3D::Update()
{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 v;	//�v�Z
		float r;	//��������

		if (m_Pattern == STRAIGHT)
		{
			pos += m_move;
		}
		else if(m_Pattern == TARGET)
		{
			v = pos - m_Target;
			r = sqrtf(v.x * v.x + v.z * v.z);
			m_XZr = (float)atan2(v.x, v.z);		//�p�x����
			m_Yr = (float)atan2(v.x, v.y);		//�p�x��

			pos += D3DXVECTOR3(sinf(m_XZr) * -m_move.x, cosf(m_Yr) * -m_move.x, cosf(m_XZr) * -m_move.x);

			if (r < 30)
			{
				m_bUninit == true;
			}
		}

		SetPos(pos);

		CBillEffect::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CStraight3D::Draw()
{
	CBillEffect::Draw();
}

//=============================================================================
// �쐬
//=============================================================================
CStraight3D *CStraight3D::Create(D3DXVECTOR3 pos,
	D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	D3DXVECTOR3 move,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nType,
	int nLife,
	CStraight3D::MOVE_PATTERN Pattrn,
	D3DXVECTOR3 Target,
	int Synsetic)
{
	CStraight3D *pStraight3D = new CStraight3D(CManager::PRIORITY_EFFECT);

	if (pStraight3D != NULL)
	{
		pStraight3D->Init(pos, Size, MinSize, move, color, Mincolor, nType, nLife, Pattrn, Target,Synsetic);
	}

	return pStraight3D;
}
