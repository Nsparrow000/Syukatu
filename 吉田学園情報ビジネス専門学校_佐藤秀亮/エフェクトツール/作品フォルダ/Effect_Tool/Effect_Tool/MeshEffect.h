//=============================================================================
// �G�t�F�N�g�p�|���S������ [MeshEffect.h]
// Author : �����G��
//=============================================================================
#ifndef _MESHEFFECT_H_
#define _MESHEFFECT_H_

#include "main.h"
#include "plane.h"
#define MAX_TEX (32)

class CMeshEffect : public CScene3D
{
public:
	typedef enum
	{
		TYPE_TRAJECTORY,	//�O��
		TYPE_TRAJECTPLAYER,
		TYPE_MAX,
	} EFFECT_TYPE;

	CMeshEffect(int nPriority);	//�R���X�g���N�^
	~CMeshEffect();	//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 Vtxpos1, D3DXVECTOR3 Vtxpos2, D3DXVECTOR3 VtxOldpos1, D3DXVECTOR3 VtxOldpos2, D3DXVECTOR3 Size, int nTex, int nLife, EFFECT_TYPE nType);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��

	void SetTexture(int nTex);		//�w�肳�ꂽ�ԍ��̃e�N�X�`����\���悤��

	void ColorChange(D3DCOLORVALUE color, D3DCOLORVALUE color2);
	void SetSize();

	static void CreateTextureMesh();
	static void UninitTextureMesh();
protected:
	bool m_bUninit;	//�����t���O
	int m_Synthetic;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX];
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//�C���f�b�N�X�o�b�t�@
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_Max;
	D3DXVECTOR3 m_Max2;

	D3DXVECTOR3 m_PosOld;
	D3DXVECTOR3 m_PosOld2;

	int m_nLife;	//����

	int m_nVtx;		//���_��
	int m_nIndx;	//�C���f�b�N�X�̐�

	EFFECT_TYPE m_atype;	//�G�t�F�N�g�̃^�C�v
	int m_nTexType;	//�e�N�X�`���^�C�v

	static int m_nMaxTex;
};
#endif // !_MESHEFFECT_H_
