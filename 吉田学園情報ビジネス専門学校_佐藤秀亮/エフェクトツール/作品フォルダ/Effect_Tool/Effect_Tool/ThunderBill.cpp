//=============================================================================
// (���i���́j)�G�t�F�N�g���� [ThunderBill.cpp]
// Author : �����G��
//=============================================================================
#include "ThunderBill.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CThunderBill::CThunderBill(int nPriority) : CBillEffect(nPriority)
{
	m_orizinSize = {};
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CThunderBill::~CThunderBill()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CThunderBill::Init(D3DXVECTOR3 pos,
	D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nTex,
	int nLife,
	float Destance,
	D3DXVECTOR2 TexMove,
	D3DXVECTOR2 TexNum,
	int nAnimCounter,
	D3DXVECTOR2 nSplit,
	float fHigth,
	D3DXVECTOR3 orizinSize,
	int Synthetic)
{
	CBillEffect::Init(Size, MinSize, color, Mincolor, nTex, nLife, TexNum, TexMove, nAnimCounter, nSplit);
	int fDistance = (int)Destance;
	float fRandAngle = CIRCLE2;
	float fRandAngle2 = CIRCLE2;
	float fRandDistance = float(rand() % fDistance) - float(rand() % fDistance);
	m_orizinSize = orizinSize;

	m_nSynthenic = Synthetic;
	m_Size = Size;
	m_posorizin1 = D3DXVECTOR3(
		pos.x * sinf(fRandAngle)  * cosf(fRandAngle2) + m_orizinSize.x,
		0.0f,
		{});
	m_posorizin2 = D3DXVECTOR3(
		pos.x * sinf(fRandAngle) * cosf(fRandAngle2) - m_orizinSize.x,
		0.0f,
		{});
	m_posHigth1 = D3DXVECTOR3(
		pos.x + fRandDistance * sinf(fRandAngle) * cosf(fRandAngle2) + m_Size.x,
		fHigth,
		{});
	m_posHigth2 = D3DXVECTOR3(
		pos.x + fRandDistance * sinf(fRandAngle) * cosf(fRandAngle2) - m_Size.x,
		fHigth,
		{});

	CPlane::SetPosBill(m_posHigth1, m_posHigth2, m_posorizin1, m_posorizin2);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CThunderBill::Uninit()
{
	CBillEffect::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CThunderBill::Update()
{
	CPlane::SetPosBill(m_posHigth1, m_posHigth2, m_posorizin1, m_posorizin2);
	CBillEffect::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CThunderBill::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans, mtxWorld; //�v�Z�p�}�g���b�N�X
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	D3DXMatrixIdentity(&mtxWorld);

	//Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//�J�����O�I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	////�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	//D3DXMatrixInverse(&mtxWorld, NULL, &mtxView); //�t�s������߂�

	//x���ȊO�̃r���{�[�h��
	mtxWorld._11 = mtxView._11;
	mtxWorld._12 = mtxView._21;
	mtxWorld._13 = mtxView._31;
	//mtxWorld._21 = mtxView._12;
	mtxWorld._22 = mtxView._22;
	//mtxWorld._23 = mtxView._32;
	mtxWorld._31 = mtxView._13;
	mtxWorld._32 = mtxView._23;
	mtxWorld._33 = mtxView._33;

	//���W
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	D3DXVECTOR3 pos = GetPos();

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	SetMatrix(mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtx(), 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture[m_nTexType]);    //�e�N�X�`���̐ݒ�

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
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
CThunderBill *CThunderBill::Create(D3DXVECTOR3 pos,
	D3DXVECTOR3 Size,
	D3DXVECTOR3 MinSize,
	D3DCOLORVALUE color,
	D3DCOLORVALUE Mincolor,
	int nTex,
	int nLife,
	float Destance,
	D3DXVECTOR2 TexMove,
	D3DXVECTOR2 TexNum,
	int nAnimCounter,
	D3DXVECTOR2 nSplit,
	float fHigth,
	D3DXVECTOR3 orizinSize,
	int Synthetic)
{
	CThunderBill *pThunderBill = new CThunderBill(CManager::PRIORITY_EFFECT);

	if (pThunderBill != NULL)
	{
		pThunderBill->Init(pos, Size, MinSize, color, Mincolor, nTex, nLife, Destance, TexMove,
			TexNum, nAnimCounter, nSplit, fHigth,
			orizinSize,
			Synthetic);
	}

	return pThunderBill;
}
