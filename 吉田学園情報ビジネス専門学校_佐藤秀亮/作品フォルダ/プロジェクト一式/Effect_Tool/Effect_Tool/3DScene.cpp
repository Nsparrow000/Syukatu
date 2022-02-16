//=============================================================================
// 3D側エフェクト管理[3DScene.h]
// Author : 佐藤秀亮
//=============================================================================
//*****************************************************************************
//インクルード
//*****************************************************************************
#if 1
#include "3DScene.h"
#include "Fade.h"
#include "load.h"
#include "control.h"

#include "keyboard.h"

#include "SetEffect3d.h"
#endif

//*****************************************************************************
//静的
//*****************************************************************************

//*****************************************************************************
//マクロ
//*****************************************************************************
#define FILE3D "data/3DMode.txt"

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
C3DScene::C3DScene()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
C3DScene::~C3DScene()
{
}
#endif

//*****************************************************************************
// 初期化
//***************************************************************************** 
HRESULT C3DScene::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();

	CLoad::Load(FILE3D);

	CControl::SetPlayerMode(true);
	//フェード
	CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	//エフェクト出すやつ
	CSetEffect3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, +15.0f, 0.0f),
		D3DXVECTOR2(0.0f, 0.0f));

	return S_OK;
}

//*****************************************************************************
// 終了
//***************************************************************************** 
void C3DScene::Uninit()
{
	CScene::Release();
}

//*****************************************************************************
// kousinn
//***************************************************************************** 
void C3DScene::Update()
{

}

#if 1
//*****************************************************************************
//描画
//***************************************************************************** 
void C3DScene::Draw()
{
	if (m_pKeyboard != NULL)
	{
		if (m_pKeyboard->GetKey(DIK_RETURN) == true)
		{
			CFade::SetFade(CManager::MODE_2D);
		}
	}
}

//*****************************************************************************
//描画
//***************************************************************************** 
C3DScene *C3DScene::Create()
{
	C3DScene *p2DScene = NULL;
	p2DScene = new C3DScene;		//メモリ確保
									//NULLチェック
	if (p2DScene != NULL)
	{
		p2DScene->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return p2DScene;
}
#endif

#if 1
#endif
