//=============================================================================
// (���i���́j)�G�t�F�N�g���� [ThunderBill.h]
// Author : �����G��
//=============================================================================
#include "main.h"
#include "billEffect.h"

class CThunderBill : public CBillEffect
{
public:
	CThunderBill(int nPriority);
	~CThunderBill();

	HRESULT Init(D3DXVECTOR3 pos,
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
		int Synthetic);

	void Uninit();
	void Update();
	void Draw();

	static CThunderBill *Create(D3DXVECTOR3 pos,
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
		int Synthetic
		);
private:

	D3DXVECTOR3 m_posorizin1;	//�o���ʒu
	D3DXVECTOR3 m_posorizin2;	//�o���ʒu

	D3DXVECTOR3 m_posHigth1;	//�o���ʒu��
	D3DXVECTOR3 m_posHigth2;	//�o���ʒu��

	D3DXVECTOR3 m_orizinSize;	//�T�C�Y�i�������j

	float m_Rot;	//�o���ʒu��

	float m_fHigth;

};