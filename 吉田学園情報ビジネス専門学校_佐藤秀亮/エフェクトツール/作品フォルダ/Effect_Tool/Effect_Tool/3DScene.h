//=============================================================================
// 3D���G�t�F�N�g�Ǘ�[3DScene.h]
// Author : �����G��
//=============================================================================
#ifndef _3DSCENE_H_
#define _3DSCENE_H_

#include "manager.h"
#include "Scene.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;

class C3DScene : public CScene
{
public:
	C3DScene();
	~C3DScene();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();

	static C3DScene *Create();

private:
	static int m_SerectNam;
	static bool m_bFade;
	static int m_nDirey;	//�����̃f�B���C
	static bool m_bPresetStart;	//�v���Z�b�g�̍Đ���
	static int m_nPattarn;	//�����G�t�F�N�g


	CKeyboard *m_pKeyboard;
	CGamePad *m_pGamePad;

};

#endif // _3DSCENE_H_
