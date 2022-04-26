//*****************************************************************************
// 3D�G�t�F�N�g�ݒu����(SetEffect3d.h)
// Author : �����G��
//*****************************************************************************

#ifndef _SETEFFECT3D_H_
#define _SETEFFECT3D_H_

#include "plane.h"

class CKeyboard;

class CSetEffect3D : public CPlane
{
public:
	CSetEffect3D(int nPriority);
	~CSetEffect3D();

	HRESULT Init(D3DXVECTOR3 Size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex);
	void Uninit();
	void Update();

	static CSetEffect3D *Create(D3DXVECTOR3 Size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex);

private:
	static bool bOne;
	CKeyboard *m_pKeyboard;

};

#endif