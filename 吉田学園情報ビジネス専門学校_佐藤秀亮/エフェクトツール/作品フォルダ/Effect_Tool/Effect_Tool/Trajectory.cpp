 //=============================================================================
// �O�Տ��� [Trajectory.cpp]
// Author : �����G��
//=============================================================================
#include "Trajectory.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTrajectory::CTrajectory(int nPriority) : CSetMesh::CSetMesh(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTrajectory::~CTrajectory(void)
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CTrajectory::Init(D3DXVECTOR3 Vtxpos1, D3DXVECTOR3 Vtxpos2, D3DXVECTOR3 VtxOldpos1, D3DXVECTOR3 VtxOldpos2, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DCOLORVALUE Trajectcolor,D3DCOLORVALUE TrajectMincolor,D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, int nTex, int nLife,
	int Synthetic)
{
	CSetMesh::Init(Vtxpos1, Vtxpos2, VtxOldpos1, VtxOldpos2, color, Mincolor, Trajectcolor, TrajectMincolor, Size, MinSize, nTex, nLife, CMeshEffect::TYPE_TRAJECTORY, Synthetic);
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CTrajectory::Uninit(void)
{
	CSetMesh::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CTrajectory::Update(void)
{
	CSetMesh::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CTrajectory::Draw(void)
{
	CSetMesh::Draw();
}

//=============================================================================
// �쐬
//=============================================================================
CTrajectory *CTrajectory::Create(D3DXVECTOR3 Vtxpos1, D3DXVECTOR3 Vtxpos2, D3DXVECTOR3 VtxOldpos1, D3DXVECTOR3 VtxOldpos2, D3DCOLORVALUE color, D3DCOLORVALUE Mincolor, D3DCOLORVALUE Trajectcolor, D3DCOLORVALUE TrajectMincolor, D3DXVECTOR3 Size, D3DXVECTOR3 MinSize, int nTex, int nLife,
	int Synthetic)
{
	CTrajectory *pTrajectory = NULL;
	pTrajectory = new CTrajectory(CManager::PRIORITY_EFFECT);	//�������m��

	//NULL�`�F�b�N
	if (pTrajectory != NULL)
	{
		pTrajectory->Init(Vtxpos1, Vtxpos2, VtxOldpos1, VtxOldpos2, color, Mincolor, Trajectcolor, TrajectMincolor, Size, MinSize, nTex, nLife, Synthetic);
	}

	return pTrajectory;
}
