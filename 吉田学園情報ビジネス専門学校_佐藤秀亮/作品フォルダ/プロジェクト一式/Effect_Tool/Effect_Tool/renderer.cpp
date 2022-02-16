//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : 三上航世
//
//=============================================================================
#include "renderer.h"
#include "scene2d.h"
#include "manager.h"
#include "camera.h"

#include "control.h"
#include "seteffect.h"

#include <assert.h>

//静的メンバ変数
CCamera *CRenderer::m_pCamera = NULL;
HWND CRenderer::m_wnd = NULL;

CRenderer::CRenderer()
{

}

CRenderer::~CRenderer()
{

}

HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;							// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;						// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

																// デバイスの生成
																// ディスプレイアダプタを表すためのデバイスを作成
																// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	m_wnd = hWnd;

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングを行わない
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

																			// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

																			// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 200.0f, -300.0f), 400.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	

	return S_OK;
}

void CRenderer::Uninit()
{
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
	}

	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

}

void CRenderer::Update()
{
	m_pCamera->Update();

	GetMouse();
	CScene::UpdateAll();
}

void CRenderer::Draw()
{
	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0); //背景の色を変えれる

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// ポリゴンの描画処理
		CScene::DrawAll();

		// FPS表示
		DrawFPS();


		DrawText();

		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CRenderer::DrawFPS()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", GetFPS());

	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//*****************************************************************************
//画面テキスト表示
//*****************************************************************************
void CRenderer::DrawText()
{
	CManager::MODE mode = CManager::GetMode();

	RECT rect = { 0, 30, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[1024];

	bool bMouse = CControl::GetMouseCursor();
	bool bTap = CControl::GetTap();

	int nNum = sprintf(&str[0], "選択カラー [←][→]：%d\n", CControl::GetSerectColor());

	nNum += sprintf(&str[nNum], "カラー値 [Q][A] ランダム[1]：(%d %d %d %d)\n", CControl::GetControlCoror(1), CControl::GetControlCoror(2), CControl::GetControlCoror(3), CControl::GetControlCoror(4));

	nNum += sprintf(&str[nNum], "カラー増減値 [W][S]：(%d %d %d %d)\n", CControl::GetChangeCol(1), CControl::GetChangeCol(2), CControl::GetChangeCol(3), CControl::GetChangeCol(4));

	nNum += sprintf(&str[nNum], "寿命 [T][G]：(%d)\n", CControl::GetLife());
	nNum += sprintf(&str[nNum], "\n");
	nNum += sprintf(&str[nNum], "エフェクトパターン [↑][↓]：(%d)\n", CControl::GetPattern());



	nNum += sprintf(&str[nNum], "\n");

	switch (mode)
	{
		//*****************************************************************************
		//2Dモード
	case(CManager::MODE_2D):

		if (bMouse == true)
		{
			nNum += sprintf(&str[nNum], "マウス追従 [M]：(ON)\n");
		}
		else
		{
			nNum += sprintf(&str[nNum], "マウス追従 [M]：(OFF)\n");
		}

		nNum += sprintf(&str[nNum], "生成座標XY：(%.1f %.1f)\n", CSetEffect::GetSetPos().x, CSetEffect::GetSetPos().y);

		nNum += sprintf(&str[nNum], "\n");

		switch (CControl::GetPattern())
		{
		case(1):
			//ランダムONなら移動値の表示
			if (CControl::GetRandMoveX() == false && CControl::GetRandMoveY() == false)
			{
				nNum += sprintf(&str[nNum], "移動値 X:[Y][H]ランダムON[6] Y:[U][J]ランダムON[7]：(%.1f %.1f)\n", CControl::GetMove().x, CControl::GetMove().y);
			}
			else if (CControl::GetRandMoveX() == true && CControl::GetRandMoveY() == false)
			{
				nNum += sprintf(&str[nNum], "移動値 XランダムOFF[6] Y:[U][J]ランダムON[7]：(RANDOM %.1f)\n", CControl::GetMove().y);
			}
			else if (CControl::GetRandMoveY() == true && CControl::GetRandMoveX() == false)
			{
				nNum += sprintf(&str[nNum], "移動値 X:[Y][H]ランダムON[6] Y:ランダムOFF[7]：(%.1f RANDOM)\n", CControl::GetMove().x);
			}
			else
			{
				nNum += sprintf(&str[nNum], "移動値 XランダムOFF[6] Y:ランダムOFF[7]：(RANDOM RANDOM)\n");
			}

			nNum += sprintf(&str[nNum], "移動加算値 X[I][K] Y[O][L]：(%.1f %.1f)\n", CControl::GetAddMove().x, CControl::GetAddMove().y);
			break;
		case(2):
			if (CControl::GetRandMoveX() == false)
			{
				nNum += sprintf(&str[nNum], "移動値 [Y][H] ランダムON[6]：(%.1f)\n", CControl::GetMove().x);
			}
			else
			{
				nNum += sprintf(&str[nNum], "移動値 ランダムOFF[6]：(RANDOM)\n");
			}
			nNum += sprintf(&str[nNum], "拡散率 [I][K]：(%.2f)\n", (float)CControl::GetDiffusion() / 100);
			nNum += sprintf(&str[nNum], "消える直線距離 [U][J]：(%d)\n", CControl::GetUninitVectl());
			nNum += sprintf(&str[nNum], "\n");
			nNum += sprintf(&str[nNum], "※マウスに向かって飛んでいくやつ\n");
			nNum += sprintf(&str[nNum], "※マウス追従がONだと上に飛んで行きます\n");

			break;
		default:
			break;
		}
		nNum += sprintf(&str[nNum], "\n");

		nNum += sprintf(&str[nNum], "サイズ [E][D]：(%.1f)\n", CControl::GetSize());
		nNum += sprintf(&str[nNum], "サイズ増減 [R][F]：(%.1f)\n", CControl::GetChangeSize());
		nNum += sprintf(&str[nNum], "\n");
		nNum += sprintf(&str[nNum], "密度 [C][V]：(%d)\n", CControl::GetDensity());
		nNum += sprintf(&str[nNum], "テクスチャ [Z][X]：(%d)\n", CControl::GetTex());
		nNum += sprintf(&str[nNum], "\n");
		if (bTap == true)
		{
			nNum += sprintf(&str[nNum], "Tapモード [N]：(ON)\n");
		}
		else
		{
			nNum += sprintf(&str[nNum], "Tapモード [N]：(OFF)\n");
		}


		nNum += sprintf(&str[nNum], "\n");
		nNum += sprintf(&str[nNum], "テキスト出力 [F9]\n");

		nNum += sprintf(&str[nNum], "3Dモードへ [ENTER]\n");

		break;

		//*****************************************************************************
		//3Dモード
	case(CManager::MODE_3D):
		nNum += sprintf(&str[nNum], "操作モード [F5]：");



		if (CControl::GetPlayerMode() == true)
		{
			nNum += sprintf(&str[nNum], "プレイヤー操作\n");
			nNum += sprintf(&str[nNum], "移動 WASD\n");
			nNum += sprintf(&str[nNum], "SPACE ジャンプ\n");
			nNum += sprintf(&str[nNum], "左クリック 攻撃(軌跡確認)\n\n");

		}
		else
		{
			nNum += sprintf(&str[nNum], "エフェクト操作\n");
			nNum += sprintf(&str[nNum], "プレイヤー一部更新停止\n");

			nNum += sprintf(&str[nNum], "\n");
			if (CControl::GetPattern() != 1)
			{
				nNum += sprintf(&str[nNum], "サイズ [E][D]：(%.1f)\n", CControl::GetSize());
				nNum += sprintf(&str[nNum], "サイズ増減 [R][F]：(%.1f)\n", CControl::GetChangeSize());
				nNum += sprintf(&str[nNum], "密度 [C][V]：(%d)\n", CControl::GetDensity());
				nNum += sprintf(&str[nNum], "テクスチャ [Z][X]：(%d)\n", CControl::GetTex());

			}
			nNum += sprintf(&str[nNum], "\n");


			switch (CControl::GetPattern())
			{
			case(1)://軌跡パターン
				nNum += sprintf(&str[nNum], "左クリック 攻撃(軌跡確認) \n※この操作モードだと色ランダムがうまく機能しないかも)\n\n");

				nNum += sprintf(&str[nNum], "軌跡先端初期色 [C][V]：(%d %d %d %d)\n", CControl::GetTrajectColor(1), CControl::GetTrajectColor(2), CControl::GetTrajectColor(3), CControl::GetTrajectColor(4));
				nNum += sprintf(&str[nNum], "軌跡先端増減 [B][N]：(%d %d %d %d)\n", CControl::GetTrajectCol(1), CControl::GetTrajectCol(2), CControl::GetTrajectCol(3), CControl::GetTrajectCol(4));

				nNum += sprintf(&str[nNum], "軌跡手元モデル [Z] ：(%d / 14)\n", CControl::GetModelNum());
				nNum += sprintf(&str[nNum], "軌跡先端モデル [X] ：(%d / 14)\n", CControl::GetTrajectModelNum());

				nNum += sprintf(&str[nNum], "\n");
				nNum += sprintf(&str[nNum], "※このパターンはカラー値が手元の色の役割になります\n");
				nNum += sprintf(&str[nNum], "※あと選択カラーは先端、手元ともに同じです\n");
				nNum += sprintf(&str[nNum], "※軌跡の長さ変えたい時はプレイヤーのテキストいじってください\n  不便でごめんなさい\n");
				break;
			case(2)://ストレートパターン
				nNum += sprintf(&str[nNum], "移動値 X[U][J] Y[I][K] Z[O][L]：X：%.1f Y：%.1f Z：%.1f\n", CControl::Getmove3d().x, CControl::Getmove3d().y, CControl::Getmove3d().z);
				break;
			case(3)://纏わせるパーティクル
				nNum += sprintf(&str[nNum], "動く値の最大 最小[Y][H] ：(%d)\n", CControl::GetRandMove1());
				nNum += sprintf(&str[nNum], "発生モデル [Z] ：(%d / 14)\n", CControl::GetModelNum());
				nNum += sprintf(&str[nNum], "比較モデル [X] ：(%d / 14)\n", CControl::GetTrajectModelNum());
				break;
			default:
				assert(false);
				break;
			}
			nNum += sprintf(&str[nNum], "\n");

			nNum += sprintf(&str[nNum], "テキスト出力 [F9]\n");

		}
		nNum += sprintf(&str[nNum], "2Dモードへ [ENTER]\n");
		break;

	default:
		assert(false);
		break;
	}


	// テキストの描画
	m_pFont->DrawText(
		NULL,
		&str[0],
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));

}