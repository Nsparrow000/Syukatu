//*****************************************************************************
// �G�t�F�N�g�ݒu����(SetEffect.h)
// Author : �����G��
//*****************************************************************************

#ifndef _SETEFFECT_H_
#define _SETEFFECT_H_

#include "Scene2D.h"
class CKeyboard;
class CMouse;

class CSetEffect :public CScene2D
{
public:

	CSetEffect(int nPriority);
	~CSetEffect();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType);
	void Uninit();
	void Update();
	void Draw();

	static void SetEffect(int nPatern);

	static D3DXVECTOR3 GetSetPos() { return m_pos; }

	static CSetEffect *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType);
private:
	CMouse *m_pMouse;
	CKeyboard *m_pKeyboard;

	static POINT m_po;					//�}�E�X���W

	static D3DXVECTOR3 m_pos;			//���݈ʒu

	D3DCOLORVALUE m_Color;		//�J���[
	bool m_bUninit;				//������

	//�傫�����
	float m_fSizeX;
	float m_fSizeY;

	static float m_fSizeX2;
	static float m_fSizeY2;

	static bool m_bOnce;

	static int m_nSerectEffect;	//�ݒu�G�t�F�N�g�v���r���[�ԍ�
};
#endif