//=============================================================================
// �}�l�[�W�� [Manager.h]
// Author : �����G��
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
//=============================================================================
//�}�N��
//=============================================================================

//�O���錾
class CRenderer;
class CKeyboard;
class CMouse;
class CGamePad;

class C2DScene;
class C3DScene;

class CManager
{
public:

	typedef enum
	{
		MODE_2D,
		MODE_3D,
		MODE_MAX,
	}MODE;

	typedef enum
	{
		PRIORITY_SET = 0,
		PRIORITY_EFFECT,
		PRIORITY_BUTTEN,
		PRIORITY_FADE,
		PRIORITY_MAX
	}PRIORITY_TYPE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	static CRenderer *GetRenderer();
	static CKeyboard *GetKeyboard();
	static CMouse *GetMouse();

	//���[�h�i�[�E�擾
	static void SetMode(MODE mode);
	static MODE GetMode();

	//���ꂼ��̃��[�h�n�����
	static C2DScene *Get2DScene() { return m_p2DScene; }
	static C3DScene *Get3DScene() { return m_p3DScene; }


private:
	static CRenderer *m_pRenderer;
	static CKeyboard *m_pKeyboard;
	static CMouse *m_pMouse;

	static MODE m_aMode;		//���݂̃��[�h

	//�n�����
	static C2DScene *m_p2DScene;
	static C3DScene *m_p3DScene;

};

#endif