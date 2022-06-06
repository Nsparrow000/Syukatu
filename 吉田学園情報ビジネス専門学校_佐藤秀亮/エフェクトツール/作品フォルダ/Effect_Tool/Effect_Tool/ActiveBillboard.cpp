//=============================================================================
// (�t�B�[���h�̃r���{�[�h��)3D�G�t�F�N�g���� [ActiveBillboard.h]
// Author : �����G��
//=============================================================================
#include "ActiveBillboard.h"
#include "manager.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CActiveBillBoard::CActiveBillBoard(int nPriority) : CBillEffect(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CActiveBillBoard::~CActiveBillBoard()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CActiveBillBoard::Init(D3DXVECTOR3 pos,
	D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	D3DXVECTOR3 move,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nType,
	int nLife,
	int Synsetic,
	int FieldTime,
	float MaxSize,
	float AddSize,
	bool PresetCreate,
	int nPattern,
	D3DXVECTOR2 TexMove,
	D3DXVECTOR2 TexNum,
	int nAnimCounter,
	D3DXVECTOR2 nSplit)
{
	CBillEffect::Init(Size, MinSize, color, Mincolor, nType, nLife, TexNum, TexMove, nAnimCounter, nSplit);
	m_nSynthenic = Synsetic;
	m_CreatePreset = nPattern;
	m_MinSize = MinSize;
	m_fSize = sqrtf(Size.x * Size.x + Size.y * Size.y);

	m_MaxSize = MaxSize;
	m_AddSize = AddSize;
	m_move = move;
	m_PresetCreate = PresetCreate;
	m_ActiveTime = FieldTime;
	EffectTime = START;

	SetPos(pos);
	BillboardSize(m_fSize);

	return S_OK;
}


//=============================================================================
// �I��
//=============================================================================
void CActiveBillBoard::Uninit()
{
	CBillEffect::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CActiveBillBoard::Update()
{
	D3DXVECTOR3 pos = GetPos();


	switch (EffectTime)
	{
	case(START):
		pos += m_move;

		m_fSize += m_AddSize;
		if (m_fSize > m_MaxSize)
		{
			EffectTime = ACTIVE;
		}
		break;
	case(ACTIVE):
		if (m_fSize < 0)
		{
			m_fSize = 0;
		}
		m_ActiveTime--;
		if (m_ActiveTime < 0)
		{
			EffectTime = END;
		}
		break;
	case(END):
		m_fSize -= m_AddSize;
		if (m_fSize < 10)
		{
			m_bUninit = true;
		}
		break;
	default:
		break;
	}


	SetPos(pos);
	BillboardSize(m_fSize);

	CBillEffect::Update();
}


//=============================================================================
// �`��
//=============================================================================
void CActiveBillBoard::Draw()
{
	CBillEffect::Draw();
}

//=============================================================================
// �쐬
//=============================================================================
CActiveBillBoard *CActiveBillBoard::Create(D3DXVECTOR3 pos,
	D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	D3DXVECTOR3 move,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nType,
	int nLife,
	int Synsetic,
	int FieldTime,
	float MaxSize,
	float AddSize,
	bool PresetCreate,
	int nPattern,
	D3DXVECTOR2 TexMove,
	D3DXVECTOR2 TexNum,
	int nAnimCounter,
	D3DXVECTOR2 nSplit)
{
	CActiveBillBoard *pStraight3D = new CActiveBillBoard(CManager::PRIORITY_EFFECT);

	if (pStraight3D != NULL)
	{
		pStraight3D->Init(pos, Size, MinSize, move, color, Mincolor, nType, nLife, Synsetic, FieldTime, MaxSize, AddSize, PresetCreate, nPattern, TexMove, TexNum, nAnimCounter, nSplit);
	}

	return pStraight3D;

}
