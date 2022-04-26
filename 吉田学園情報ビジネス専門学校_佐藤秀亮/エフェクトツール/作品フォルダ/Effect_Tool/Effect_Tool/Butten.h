//*****************************************************************************
// �{�^��(Butten.h)
// Author : �����G��
//*****************************************************************************
#ifndef _BUTTEN_H_
#define _BUTTEN_H_

#include "Scene2D.h"
class CKeyboard;
class CMouse;

class CButten :public CScene2D
{
public:

	//�\������{�^��
	typedef enum
	{
		ALL,
		CHANGE,
		DISPLAY_MAX,
	} DISPLAY;

	//�\������{�^��
	typedef enum
	{
		NONE,
		PATTERN0,
		PATTERN1,
		PATTERN2,
		PATTERN3,
		PATTEN_MAX,
	} DISPLAY_PATTERN;


	//�ύX���镨�̎w��
	typedef enum
	{
		PATTERN,
		COLSELECT,
		COL,
		ADDCOL,
		SIZE,
		ADDSIZE,
		MOVEX,
		MOVEY,
		ADDMOVEX,
		ADDMOVEY,
		LIFE,
		DENSITY,
		DIFFUSION,
		TEXTURE,
		ROTATE,
		SAVE,
		LOAD,
		DESTROY,
		TRAJECTTOP,
		TRAJECTTOPCOL,
		TRAJECTTOPADDCOL,
		TRAJECTCUR,
		MOVE3DX,
		MOVE3DY,
		MOVE3DZ,
		RANDMOVE3D,
		SYNTHETIC,
		PARTICLESIZE,
		PARTICLETIME,
		DISTANCE,
		ACTIVETIME,
		MAXSIZE,
		PARTICLEADDSIZE,
		PARTICLECOLOR,
		PARTICLEADDCOLOR,
		PARTICLESYNSETIC,
		ACTIVEADDSIZE,
		PRESETLOAD,
		MAX,
	} OPERATION;

	CButten(int nPriority);
	~CButten();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, OPERATION Operation, float nIndeNum, DISPLAY Display, DISPLAY_PATTERN Pattern);
	void Uninit();
	void Update();
	void Draw();

	void Set(OPERATION Operation, int nCol, float nIndeNum);

	static CButten *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, OPERATION Operation,float nIndeNum, DISPLAY Display, DISPLAY_PATTERN Pattern);
private:
	CMouse *m_pMouse;
	CKeyboard *m_pKeyboard;

	static POINT m_po;					//�}�E�X���W

	D3DXVECTOR2 m_Size;		//�T�C�Y
	static D3DXVECTOR2 m_Mousepos;		//�}�E�X���W

	bool m_bUninit;		//����

	float m_fAlpha;	//�A���t�@�l

	OPERATION m_aOperation;		//�ύX���鍀��
	DISPLAY aDisplay;	//�\������{�^��
	DISPLAY_PATTERN aDisplayPattern;	//�ׂ���
	int m_nNum;		//�F
	float m_nIndeNum;		//����
};
#endif