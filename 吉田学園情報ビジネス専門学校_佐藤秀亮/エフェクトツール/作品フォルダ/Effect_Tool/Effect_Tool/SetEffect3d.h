//*****************************************************************************
// 3D�G�t�F�N�g�ݒu����(SetEffect3d.h)
// Author : �����G��
//*****************************************************************************

#ifndef _SETEFFECT3D_H_
#define _SETEFFECT3D_H_

#include "plane.h"

class CKeyboard;
class CMouse;
class CCamera;

class CSetEffect3D : public CPlane
{
public:
	CSetEffect3D(int nPriority);
	~CSetEffect3D();

	HRESULT Init(D3DXVECTOR3 Size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex);
	void Uninit();
	void Update();

	static CSetEffect3D *Create(D3DXVECTOR3 Size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex);

	void SetEffect();

private:
	CMouse *m_pMouse;
	CCamera *m_pCamera;

	static bool bOne;
	CKeyboard *m_pKeyboard;
	bool m_bOne;
	int m_ParticleTime;

	static bool m_MouseButtenPush;	//�{�^�������Ă邩
	static int m_MousePushTime;	//�����Ă鎞��

	static bool m_PushDeley;	//�{�^�������Ă邩
	static int m_DeleyTime;	//�����Ă鎞��

};

#endif