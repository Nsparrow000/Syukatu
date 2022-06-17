//=============================================================================
// �e��(����)���� [BulletHoll.h]
// Author : �����G��
//=============================================================================
#ifndef _BULLETHOLL_H_
#define _BULLETHOLL_H_

#include "main.h"
#include "billEffect.h"

class CBulletHoll : public CBillEffect
{
public:

	CBulletHoll(int nPriority);
	~CBulletHoll();

	HRESULT Init(D3DXVECTOR3 size,
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
		ANIMPATTERN AnimPattern);

	void Uninit();
	void Update();
	void Draw();


	static CBulletHoll *Create(D3DXVECTOR3 size,
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
		ANIMPATTERN AnimPattern);

private:
	int nLife;	//����
	bool bUninit;
	D3DXVECTOR3 m_pos;
	float m_size;		//���݂̑傫��

	D3DXVECTOR3 m_pos1;	//�o���ʒu
	D3DXVECTOR3 m_pos2;	//�o���ʒu
	D3DXVECTOR3 m_pos3;	//�o���ʒu
	D3DXVECTOR3 m_pos4;	//�o���ʒu

	D3DXVECTOR3 m_Rot;	//��]
};

#endif