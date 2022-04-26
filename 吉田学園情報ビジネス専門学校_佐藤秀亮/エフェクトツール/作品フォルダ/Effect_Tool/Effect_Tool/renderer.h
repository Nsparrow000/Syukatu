//=============================================================================
// �����_�����O���� [renderer.h]
// Author : �����G��
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

class CInputKeyboard;
class CCamera;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }
	CCamera *GetCamera() { return m_pCamera; }

	void DrawFPS();
	void DrawText();
	void DrawTextLeft();


	static HWND GetWnd() { return m_wnd; }

	D3DXVECTOR3 GetMousePos() { return GetMouse(); }

private:
	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
	static CCamera *m_pCamera;

	static HWND m_wnd;
};

#endif