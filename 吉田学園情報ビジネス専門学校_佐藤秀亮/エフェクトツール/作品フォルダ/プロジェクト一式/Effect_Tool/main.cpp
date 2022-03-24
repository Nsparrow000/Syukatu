//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 三上航世
//
//=============================================================================
#include "main.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"WindowsClass"	// ウインドウのクラス名
#define WINDOW_NAME		"Effect"	// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
int						g_nCountFPS;			// FPSカウンタ
D3DXVECTOR3 g_MousePos = {};			// マウスポジション

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	//マネージャクラスの生成
	CManager *pManager;
	pManager = new CManager;
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		WINDOW_POS,
		WINDOW_POS,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);
	// 初期化処理
	if (pManager == NULL || FAILED(pManager->Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwCurrentTime =
		dwFrameCount = 0;
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// 現在の時間を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒ごとに実行

			 // FPSを算出
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;	// 現在の時間を保存
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;	// 現在の時間を保存

												// 更新処理
				pManager->Update();

				// 描画処理
				pManager->Draw();

				dwFrameCount++;
			}
		}
	}
	//レンダリングクラスの破棄
	if (pManager != NULL)
	{
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	
	// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{


	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				// [ESC]キーが押された
			DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
			break;
		case VK_F7:					// [F7]キーが押された
			SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, NULL);			
			break;
		case VK_F8:					// [F9]キーが押された
			SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, NULL);
			break;
		}
		break;
	case WM_MOUSEMOVE:
		g_MousePos.x = (float)GET_X_LPARAM(lParam);
		g_MousePos.y = (float)GET_Y_LPARAM(lParam);
		break;
	default:
		break;
	}

	IsIconic(hWnd);
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int GetFPS()
{
	return g_nCountFPS;
}

D3DXVECTOR3 GetMouse()
{
	return g_MousePos;
}