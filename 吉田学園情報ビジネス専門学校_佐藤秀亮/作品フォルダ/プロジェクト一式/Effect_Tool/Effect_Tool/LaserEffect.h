//*****************************************************************************
// (レーザー)エフェクト処理 [LaserEffect.h]
// Author : 佐藤秀亮
//*****************************************************************************
#ifndef _LASEREFFECT_H_
#define _LASEREFFECT_H_

#include "effect.h"

class CLaserEffect : public CEffect
{
public:
	CLaserEffect(int Priority);
	~CLaserEffect();

	HRESULT Init(
		D3DXVECTOR3 Vector1,
		D3DXVECTOR3 Vector2,
		D3DXVECTOR3 OldVector1,
		D3DXVECTOR3 OldVector2,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nLife, int nType);

	void Uninit();
	void Update();
	void Draw();

	static CLaserEffect *Create(
		D3DXVECTOR3 Vector1,
		D3DXVECTOR3 Vector2,
		D3DXVECTOR3 OldVector1,
		D3DXVECTOR3 OldVector2,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nLife, int nType);
private:
	D3DXVECTOR3 m_Vector1;
	D3DXVECTOR3 m_Vector2;
	D3DXVECTOR3 m_OldVector1;
	D3DXVECTOR3 m_OldVector2;
};

#endif // !_LASEREFFECT_H_
