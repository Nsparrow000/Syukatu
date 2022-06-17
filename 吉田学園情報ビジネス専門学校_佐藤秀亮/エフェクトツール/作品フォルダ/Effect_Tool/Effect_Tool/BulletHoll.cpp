//=============================================================================
// �e��(����)���� [BulletHoll.cpp]
// Author : �����G��
//=============================================================================
#include "BulletHoll.h"
#include "renderer.h"
#include "manager.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBulletHoll::CBulletHoll(int nPriority) : CBillEffect(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBulletHoll::~CBulletHoll()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CBulletHoll::Init(D3DXVECTOR3 size,
	D3DXVECTOR3 Addsize,
	D3DXVECTOR3 pos,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nLife,
	int nTex,
	D3DXVECTOR2 TexMove,
	D3DXVECTOR2 TexNum,
	int nAnimCounter,
	D3DXVECTOR2 nSplit,
	D3DXVECTOR3 rot,
	int Synthetic,
	ANIMPATTERN AnimPattern)
{
	CBillEffect::Init(size, Addsize, color, Mincolor, nTex, nLife, TexNum, TexMove, nAnimCounter, nSplit, AnimPattern);
	m_nSynthenic = Synthetic;
	m_Size = size;
	m_Rot = rot;

	//m_pos1 = D3DXVECTOR3(
	//	pos.x + size.x * (cosf(m_Rot.y)),
	//	pos.y /*+ size.x / 2*/,
	//	pos.z + size.x * (sinf(-m_Rot.y)));
	//m_pos2 = D3DXVECTOR3(
	//	pos.x + (sinf(-m_Rot.y))  * size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z - (cosf(m_Rot.y))* size.x);
	//m_pos3 = D3DXVECTOR3(
	//	pos.x - (sinf(-m_Rot.y))  * size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z + (cosf(m_Rot.y))* size.x);
	//m_pos4 = D3DXVECTOR3(
	//	pos.x - (cosf(m_Rot.y)) * size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z - (sinf(-m_Rot.y))* size.x);

	m_pos1 = D3DXVECTOR3(
		pos.x - (cosf(-m_Rot.y) * size.x / 2),
		pos.y + size.x / 2,
		pos.z - (sinf(-m_Rot.y) * size.x / 2));
	m_pos2 = D3DXVECTOR3(
		pos.x + (cosf(-m_Rot.y)) * size.x / 2,
		pos.y + size.x / 2,
		pos.z + (sinf(-m_Rot.y)) * size.x / 2);
	m_pos3 = D3DXVECTOR3(
		pos.x - (cosf(-m_Rot.y) * size.x / 2),
		pos.y - size.x / 2,
		pos.z - (sinf(-m_Rot.y) * size.x / 2));
	m_pos4 = D3DXVECTOR3(
		pos.x + (cosf(-m_Rot.y)) * size.x / 2,
		pos.y - size.x / 2,
		pos.z + (sinf(-m_Rot.y)) * size.x / 2);

	//m_pos1 = D3DXVECTOR3(
	//	pos.x + size.x,
	//	pos.y /*+ size.x / 2*/,
	//	pos.z + size.x);
	//m_pos2 = D3DXVECTOR3(
	//	pos.x + size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z - size.x);
	//m_pos3 = D3DXVECTOR3(
	//	pos.x - size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z + size.x);
	//m_pos4 = D3DXVECTOR3(
	//	pos.x - size.x,
	//	pos.y /*- size.x / 2*/,
	//	pos.z - size.x);
	//CScene3d::SetRot(m_Rot);


	CPlane::SetPosBill(m_pos1, m_pos2, m_pos3, m_pos4);
	m_nSynthenic = Synthetic;
	return S_OK;

}

//=============================================================================
// �I��
//=============================================================================
void CBulletHoll::Uninit()
{
	CBillEffect::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CBulletHoll::Update()
{
	CPlane::SetPosBill(m_pos1, m_pos2, m_pos3, m_pos4);
	CBillEffect::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CBulletHoll::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

														//Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	if (m_nSynthenic == 0)
	{
		//���Z�����֌W
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (m_nSynthenic == 1)
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
	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�J�����O�I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CPlane::Draw();
	//�J�����O�I��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//�ʏ퍇���ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//=============================================================================
// �쐬
//=============================================================================
CBulletHoll *CBulletHoll::Create(D3DXVECTOR3 size,
	D3DXVECTOR3 Addsize,
	D3DXVECTOR3 pos,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nLife,
	int nTex,
	D3DXVECTOR2 TexMove,
	D3DXVECTOR2 TexNum,
	int nAnimCounter,
	D3DXVECTOR2 nSplit,
	D3DXVECTOR3 rot,
	int Synthetic,
	ANIMPATTERN AnimPattern)
{
	CBulletHoll *pBulletHoll = new CBulletHoll(CManager::PRIORITY_EFFECT);

	if (pBulletHoll != NULL)
	{
		pBulletHoll->Init(size, Addsize, pos, color, Mincolor, nLife, nTex, TexMove, TexNum, nAnimCounter, nSplit,
			rot, Synthetic, AnimPattern);
	}

	return pBulletHoll;

}