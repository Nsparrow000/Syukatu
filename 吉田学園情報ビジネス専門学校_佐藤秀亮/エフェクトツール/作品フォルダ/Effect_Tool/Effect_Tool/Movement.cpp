//*****************************************************************************
// (�ړ�����)�G�t�F�N�g���� [Movement.cpp]
// Author : �����G��
//*****************************************************************************
#include "Movement.h"
#include "manager.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CMovement::CMovement(int nPriority) : CEffect(nPriority)
{
	m_move = {};
	m_Addpos = {};
}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CMovement::~CMovement()
{

}

//*****************************************************************************
//	������
//*****************************************************************************
HRESULT CMovement::Init(D3DXVECTOR3 pos,
	D3DXVECTOR2 move,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	D3DXVECTOR2 Size,
	D3DXVECTOR2 MinSize,
	int nLife,
	int nType,
	D3DXVECTOR2 AddMovement,
	int nSynthetic)
{
	CEffect::Init(pos, color, Mincolor, Size, MinSize, nLife, nType,nSynthetic);

	m_Addpos = AddMovement;
	m_move = move;
	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CMovement::Uninit()
{
	CEffect::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CMovement::Update()
{

	D3DXVECTOR3 pos = GetPosition();

	m_move += m_Addpos;	//�ړ��l�Ɋ��������Z

	pos += D3DXVECTOR3(m_move.x, m_move.y, 0.0f);

	SetPosition(pos);

	CEffect::Update();
}

//*****************************************************************************
//�`��
//*****************************************************************************
void CMovement::Draw()
{
	CEffect::Draw();
}

//*****************************************************************************
//�쐬
//*****************************************************************************
CMovement *CMovement::Create(D3DXVECTOR3 pos,
	D3DXVECTOR2 move,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	D3DXVECTOR2 Size,
	D3DXVECTOR2 MinSize,
	int nLife,
	int nType,
	D3DXVECTOR2 AddMovement,
	int nSynthetic)
{
	CMovement *pMovement = NULL;
	pMovement = new CMovement(CManager::PRIORITY_EFFECT);		//�������m��
	//NULL�`�F�b�N
	if (pMovement != NULL)
	{
		pMovement->Init(pos, move, color, Mincolor, Size, MinSize, nLife, nType, AddMovement, nSynthetic);
	}

	return pMovement;
}
