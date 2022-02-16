//*****************************************************************************
// 3Dエフェクト設置処理(SetEffect3d.h)
// Author : 佐藤秀亮
//*****************************************************************************
#include "SetEffect3d.h"
#include "control.h"

#include "straight3d.h"

#include <assert.h>
//*****************************************************************************
//静的
//*****************************************************************************

//*****************************************************************************
//マクロ
//*****************************************************************************

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CSetEffect3D::CSetEffect3D(int nPriority) : CPlane(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CSetEffect3D::~CSetEffect3D()
{

}

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CSetEffect3D::Init(D3DXVECTOR3 Size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex)
{
	CPlane::Init(Size, pos, Tex);

	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CSetEffect3D::Uninit()
{
	CPlane::Uninit();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CSetEffect3D::Update()
{
	D3DXVECTOR3 pos = GetPos();
	switch (CControl::GetPattern())
	{
	case(1):
		break;
	case(2):
		CStraight3D::Create(pos,
			D3DXVECTOR3(CControl::GetSize(), CControl::GetSize(), 0.0f),
			D3DXVECTOR3(CControl::GetChangeSize(), CControl::GetChangeSize(), 0.0f),
			CControl::Getmove3d(),
			D3DXCOLOR((float)CControl::GetControlCoror(1), (float)CControl::GetControlCoror(2), (float)CControl::GetControlCoror(3), (float)CControl::GetControlCoror(4)),
			D3DXCOLOR((float)CControl::GetChangeCol(1), (float)CControl::GetChangeCol(2), (float)CControl::GetChangeCol(3), (float)CControl::GetChangeCol(4)),
			CControl::GetTex(), CControl::GetLife());
			break;
	case(3):
		break;
	case(4):

		break;
	default:
		assert(false);
		break;
	}
}

//*****************************************************************************
//作成
//*****************************************************************************
CSetEffect3D *CSetEffect3D::Create(D3DXVECTOR3 Size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex)
{
	CSetEffect3D * pSetEffect3D = NULL;
	pSetEffect3D = new CSetEffect3D(5);
	if (pSetEffect3D != NULL)
	{
		pSetEffect3D->Init(Size, pos, Tex);
	}
	return pSetEffect3D;
}
