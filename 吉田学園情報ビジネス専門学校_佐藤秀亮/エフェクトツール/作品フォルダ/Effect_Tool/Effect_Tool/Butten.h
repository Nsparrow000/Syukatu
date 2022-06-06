//*****************************************************************************
// �{�^��(Butten.h)
// Author : �����G��
//*****************************************************************************
#ifndef _BUTTEN_H_
#define _BUTTEN_H_

#include "Scene2D.h"
class CKeyboard;
class CMouse;

//*****************************************************************************
//�}�N��
//*****************************************************************************
#define MAX_BUTTENPATTERN 16
#define MAX_BUTTEN 64

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
		PATTERN4,
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
		SCONDTIME,
		VTX,
		TYPE,	//������������
		TEXU,	//�e�N�X�`��U
		TEXV,	//�e�N�X�`��V
		TEXNUM,	//�e�N�X�`������
		SECONDTYPE,
		TEXSPLITU,
		TEXSPLITV,
		ANIMCONT,
		TEXNUMV,
		HIGTH,
		CONTROLBEZIERX,	//�x�W�F����_
		CONTROLBEZIERY,	//�x�W�F����_
		CONTROLBEZIERZ,	//�x�W�F����_
		SECONDTEX,
		MAX,
	} OPERATION;

	//�{�^���̏��
	typedef struct
	{
		D3DXVECTOR3 m_pos;	//���W
		float m_SizeX;	//�T�C�Yx
		float m_SizeY;	//�T�C�Y�x
		int m_nType;	//�e�N�X�`��
		OPERATION m_Operation;	//�ύX�^�C�v
		float m_nIndeNum;	//���Z��
		DISPLAY_PATTERN Pattrn;	//�\���p�^�[��
	} BUTTEN_STATE;

	CButten(int nPriority);
	~CButten();

	HRESULT Init(D3DXVECTOR3 pos,
		float SizeX, float SizeY,
		int nType,
		OPERATION Operation,
		float nIndeNum,
		DISPLAY Display,
		DISPLAY_PATTERN Pattern);

	void Uninit();
	void Update();
	void Draw();

	void Set(OPERATION Operation, float nIndeNum);

	static CButten *Create(D3DXVECTOR3 pos,
		float SizeX, float SizeY,
		int nType,
		OPERATION Operation,
		float nIndeNum,
		DISPLAY Display,
		DISPLAY_PATTERN Pattern);

	//�{�^���X�e�[�^�X�̊i�[
	static void SetButtenState(D3DXVECTOR3 pos,
		float SizeX, float SizeY,
		int nType,
		OPERATION Operation,
		float nIndeNum,
		DISPLAY_PATTERN Pattern);

	static void SetButten(int nPatten);	//�{�^���z�u


	static void AddTotal(int nTotal) { m_nButtenTotal = nTotal;}	//�p�^�[���̕ύX
	static void SetTotal(int nPatten) { m_nTotal[nPatten] = m_nButtenTotal; }	//�����̊i�[
	static void ResetTotal() {m_nButtenTotal = 0;}
	static void SetPatten() { m_nPatten++; }
	static void ResetPatten() { m_nPatten = 0; }

private:
	static BUTTEN_STATE ButtenState[MAX_BUTTENPATTERN][MAX_BUTTEN];	//�{�^���̃X�e�[�^�X
	static int m_nPatten;	//�X�̃X�e�[�^�X
	static int m_nButtenTotal;	//���̃p�^�[���̃{�^������
	static int m_nTotal[MAX_BUTTENPATTERN];	//���[�v�p

	static bool m_MouseButtenPush;	//�{�^�������Ă邩
	static int m_MousePushTime;	//�����Ă鎞��

	static bool m_PushDeley;	//�{�^�������Ă邩
	static int m_DeleyTime;	//�����Ă鎞��


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