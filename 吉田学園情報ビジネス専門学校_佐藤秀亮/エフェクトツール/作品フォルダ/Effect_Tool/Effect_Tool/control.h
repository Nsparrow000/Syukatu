//*****************************************************************************
// �G�t�F�N�g�̏��X�ݒ�(control.h)
// Author : �����G��
//*****************************************************************************
#ifndef _CONTROL_H_
#define _CONTROL_H_
#include "main.h"
#include "manager.h"

//=============================================================================
//�}�N��
//=============================================================================
#define MAX_PATTERN (10)	//�ő�p�^�[��
#define MAX_DENSITY (30)		//�ő喧�x
#define MAX_LIFE (1000)			//�ő����

//�O���錾
class CKeyboard;

class CControl
{
public:
	CControl();		//�R���X�g���N�^
	~CControl();	//�f�X�g���N�^

	static HRESULT Init();
	static void Update();

	static void Control();
	static void Control2D();
	static void Control3D();
	static int GetControlCoror(int nSerectcolor);	//�F�擾
	static int GetChangeCol(int nSerectcolor);	//�����l�擾
	static void SetControlCoror(int nSerectcolor);	//�F�Z�b�g
	static bool GetRandCol(int nSerectcolor);	//�F�����_�����擾
	static void AddColor(int Color, int nSerect);		//�F����
	static void AddChangeCol(int Color, int nSerect);	//�F�����l�̑���
	static int GetSerectColor() { return m_SerectColor; }	//�F�I��ԍ�
	static const float GetSize() { return m_ControlSize; }	//�T�C�Y
	static const float GetChangeSize() { return m_ControlChangeSize; }	//�T�C�Y����
	static const int GetLife() { return m_nLife; }			//����
	static const int GetTex() { return m_nTex; }				//�e�N�X�`��
	static const int GetDensity() { return m_nDensity; }		//���x
	static const bool GetTap() { return m_bTap; }	//�^�b�vON or OFF
	static const int GetPattern() { return m_nPattern; }		//�p�^�[��
	static const float GetRotate() { return m_fAddRotate; }	//��]
	static const bool GetRandMoveX() { return m_RandMoveX; }	//�����_��XON or OFF
	static const bool GetRandMoveY() { return m_RandMoveY; }	//�����_��YON or OFF
	static void SetColorRandom(int nSerectcol , bool bAdaptation);	//�J���[�����_��ON or OFF
	static const int GetSynthetic() { return nSynthetic; }	//����
	static const D3DXVECTOR2 GetMove() { return m_move; }		//�����̓����l
	static const bool GetMouseCursor() { return m_bMouseCursor; }	//�J�[�\���Ǐ]ON or OFF
	static const D3DXVECTOR2 GetAddMove() { return m_Addmove; }		//�ړ����Z
	static const int GetDiffusion() { return m_Diffusion; }			//���x
	static const int GetUninitVectl() { return m_nUninitVectl; }		//������x�N�g��
	static const bool GetPlayerFollow() { return m_bPlayerFollow; }	//�v���C���[�Ǐ]ON or OFF
	static const bool GetPlayerMode()  { return m_bPlayerMode; }
	static const void SetPlayerMode(bool bMode) {m_bPlayerMode = bMode; }
	static const int GetModelNum() { return m_ModelNum; }
	static const D3DXVECTOR3 Getmove3d() { return m_move3d; }		//�ړ�
	static const int GetTrajectModelNum() { return m_ModelTrajecNum; }
	static const int GetRandMove1() { return m_nRandMove1; }
	static const D3DCOLORVALUE GetColor(){ return m_ControlColor; }
	static const D3DCOLORVALUE GetChangeColor() { return m_ControlChangeCol; }
	static const float GetParticleSize() { return ParticleSize; }
	static const int GetParticleTime() { return ParticleTime; }
	static const float GetDistance() { return fDistance; }
	static const int GetActiveTime() { return nActiveTime; }
	static const float GetMaxSize() { return fMaxSize; }
	static const float GetParticleAddSize() {return fParticleAddSize ; }
	static int GetParticleColor(int nSerect);		//�F����
	static int GetParticleAddCol(int nSerect);	//�F�����l�̑���
	static const int GetParticleSynthetic() { return nParticleSynthetic; }	//����
	static const float GetAvctiveAddSize() { return ActiveAddSize; }	//�A�N�e�B�u���̑傫���ύX
	static int GetSecondTime() { return m_nSecondTime; }
	static int GetVtx() { return m_nVtx; }	//���̒��_��
	static int GetType() { return m_nType; }	//���^�C�v
	static void TrajectColor(int Color, int nSerect);
	static int GetTrajectColor(int nSerectcolor);	//�F�擾
	static void AddTrajectCol(int Color, int nSerect);
	static int GetTrajectCol(int nSerectcolor);	//�F�擾
	static float GetTexMoveU() { return m_TexMove.x; }	
	static float GetTexMoveV() { return m_TexMove.y; }
	static D3DXVECTOR2 GetTexNum() { return m_TexNum; }	//�e�N�X�`������
	static int GetSecondType() { return m_nSecondTime; }
	static float GetTexPatternU() { return m_TexPattern.x; }
	static float GetTexPatternV() { return m_TexPattern.y; }
	static int GetAnimCont() { return m_nAnimCont; }
	static float GetSplitU() { return m_nSplit.x; }
	static float GetSplitV() { return m_nSplit.y; }
	static float GetHigth() { return m_fHigth; }

	static float GetContorolBezierX() {return m_ContorolBezier.x; }	//����_
	static float GetContorolBezierY() {return m_ContorolBezier.y; }	//����_
	static float GetContorolBezierZ() {return m_ContorolBezier.z; }	//����_
	static int GetSecondTex() { return m_SecondTex; }
	static int GetAnimPatternType() { return m_AnimPatternType; }


	//�e�L�X�g�Z�[�u
	static void SaveEffect(CManager::MODE mode, int nPattern);
	static void SetButten(int nPattern);

	//���ԃZ�[�u�֌W
	static void SetPattern(int nPattern) { m_nPattern = nPattern; }
	static void SetColor(D3DCOLORVALUE Color) { m_ControlColor = Color; }
	static void SetChangeColor(D3DCOLORVALUE ChangeColor) { m_ControlChangeCol = ChangeColor; }
	static void SetSize(float Size) { m_ControlSize = Size; }
	static void SetChangeSize(float ChangeSize) { m_ControlChangeSize = ChangeSize; }
	static void SetLife(int nLife) { m_nLife = nLife; }
	static void SetTexture(int nTex) { m_nTex = nTex; }
	static void SetDensity(int nDensity) { m_nDensity = nDensity; }
	static void SetAddRotate(float fAddRotate) { m_fAddRotate = fAddRotate; }
	static void SetDiffusion(int Diffusion) { m_Diffusion = Diffusion; }
	static void SetMove(D3DXVECTOR2 move) {m_move = move; }
	static void SetAddmove(D3DXVECTOR2 Addmove) { m_Addmove = Addmove; }
	static void SetUninitVectl(int nUninitVectl) { m_nUninitVectl = nUninitVectl; }
	static void SetSynthetic(int Synthetic) { nSynthetic = Synthetic; }
	static void SetTrajectColor(D3DCOLORVALUE Color) { m_TrajectColor = Color; }
	static void SetTrajectChangeColor(D3DCOLORVALUE ChangeColor) { m_TrajectChangeCol = ChangeColor; }
	static void SetTrajectTop(int Top) { m_ModelTrajecNum = Top; }
	static void SetTrajectCur(int Cur) { m_ModelNum = Cur; }
	static void SetMove3D(D3DXVECTOR3 move) { m_move3d = move; }
	static void SetRandMove(int Randmove) { m_nRandMove1 = Randmove; }
	static void SetParticleSize(float Size) { ParticleSize = Size; }
	static void SetParticleTime(int Time) { ParticleTime = Time; }
	static void SetDistance(float Distance) { fDistance = Distance; }
	static void SetActive(int Active) { nActiveTime = Active; }
	static void SetParticleAddSize(float AddSize) { fParticleAddSize = AddSize; }
	static void SetMaxSize(float MaxSize) { fMaxSize = MaxSize; }
	static void SetParticleColor(D3DCOLORVALUE Color) { m_ParticleColor = Color; }		//�F����
	static void SetParticleAddCol(D3DCOLORVALUE ChangeColor) { m_ParticleAddCol = ChangeColor; }	//�F�����l�̑���
	static void SetParticleSynthetic(int Synthetic) { nParticleSynthetic = Synthetic; }
	static void SetAvctiveAddSize(float ActiveSize) { ActiveAddSize = ActiveSize; }
	static void SetSecondTime(int SecondTime) { m_nSecondTime = SecondTime; }
	static void SetVtx(int Vtx) { m_nVtx = Vtx; }
	static void SetType(int nType) { m_nType = nType;}	//���^�C�v
	static void SetTexMoveUV(D3DXVECTOR2 TexMove) { m_TexMove = TexMove; }	//�e�N�X�`��
	static void SetTexNum(D3DXVECTOR2 Num) { m_TexNum = Num; }	//�e�N�X�`��
	static void SetSecondType(int SecondType) { m_nSecondTime = SecondType; }
	static void SetTexPattern(D3DXVECTOR2 TexPattern) { m_TexPattern = TexPattern; }	//�e�N�X�`��
	static void SetnAnimCont(int nAnimCont) { m_nAnimCont = nAnimCont; }	//�e�N�X�`��
	static void SetnSplit(D3DXVECTOR2 nSplit) { m_nSplit = nSplit; }	//�e�N�X�`��
	static void SetHigth(float Higth) { m_fHigth = Higth; }	//����
	static void SetControlBezier(D3DXVECTOR3 ControlBezier) { m_ContorolBezier = ControlBezier; }	//�x�W�F����_
	static void SetSecondTex(int SecondTex) { m_SecondTex = SecondTex; }
	static void SetAnimPatternType(int AnimPatternType) { m_AnimPatternType = AnimPatternType; }

	//�����֌W
	static void AddPattern(int nPattern) {
		m_nPattern += nPattern;
		if (m_nPattern >= MAX_PATTERN)
		{
			m_nPattern = MAX_PATTERN - 1;
		}
		else if (m_nPattern <= -1)
		{
			m_nPattern = 0;
		}
		else
		{
			CControl::SetButten(m_nPattern);
		}
		; }

	static void AddSelectCol(int nPattern) { m_SerectColor += nPattern; }
	static void AddSize(float Size) {
		m_ControlSize += Size;
	if (m_ControlSize <= 0)
	{
		m_ControlSize = 0;
	}

	}
	static void AddChangeSize(float ChangeSize) {
		m_ControlChangeSize += ChangeSize;
	}
	static void AddLife(int nLife) {
		m_nLife += nLife;
		if (m_nLife >= MAX_LIFE)
		{
			m_nLife = MAX_LIFE;
		}
		else if (m_nLife <= 0)
		{
			m_nLife = 0;
		}
	}
	static void AddTexture(int nTex) { m_nTex += nTex; }
	static void AddDensity(int nDensity) { m_nDensity += nDensity;}
	static void AddRotateAdd(float fAddRotate) { m_fAddRotate += fAddRotate; }
	static void AddDiffusion(int Diffusion) { m_Diffusion += Diffusion; }
	static void AddUninitVectl(int nUninitVectl) { m_nUninitVectl += nUninitVectl; }
	static void AddMoveX(float MoveX) { m_move.x += MoveX;}
	static void AddMoveY(float MoveY) {m_move.y += MoveY;}
	static void AddMoveXAdd(float AddMoveX) { m_Addmove.x += AddMoveX; }
	static void AddMoveYAdd(float AddMoveY) { m_Addmove.y += AddMoveY; }

	static void AddTrajectTop(int nTraject) { m_ModelTrajecNum += nTraject;
	if (m_ModelTrajecNum > 14)
	{
		m_ModelTrajecNum = 0;
	}
	else if (m_ModelTrajecNum <= 0)
	{
		m_ModelTrajecNum = 14;
	}
	}
	static void AddTrajectCur(int nTraject) { m_ModelNum += nTraject;
	if (m_ModelNum > 14)
	{
		m_ModelNum = 0;
	}
	else if (m_ModelNum <= 0)
	{
		m_ModelNum = 14;
	}
	}
	static void Addmove3d(float Move, int nNum);		//�ړ�
	static void AddRandMove(int nMove) { 
		m_nRandMove1 += nMove;
		if (m_nRandMove1 <= 0)
		{
			m_nRandMove1 = 1;
		}
	}

	static void AddSynthetic(int Synthetic) {
		nSynthetic += Synthetic;
		if (nSynthetic < 0)
		{
			nSynthetic = 0;
		}
	}	//����

	static void AddParticleSize(float Size) { ParticleSize += Size;}	//�p�[�e�B�N���T�C�Y
	static void AddParticleTime(int Time) { ParticleTime += Time;
	if (ParticleTime <= 0)
	{
		ParticleTime = 1;
	}
	}	//�p�[�e�B�N����������
	static void AddDistance(float Distance) { fDistance += Distance;
	if (fDistance <= 0)
	{
		fDistance = 1.0f;
	}
	}	//�����̒���

	static void AddActiveTime(int nActive) { nActiveTime += nActive; }
	static void AddMaxSize(float MaxSize) { fMaxSize += MaxSize; }
	static void AddParticleAddSize(float ParticleAddSize) { fParticleAddSize += ParticleAddSize; }
	static void AddAvctiveAddSize(float ActiveSize) { ActiveAddSize += ActiveSize; }

	static void AddSecondTime(int nScondTime) {m_nSecondTime += nScondTime;}

	static void AddParticleColor(int Color, int nSerect);		//�F����
	static void AddParticleAddCol(int Color, int nSerect);	//�F�����l�̑���

	static void AddParticleSynthetic(int Synthetic) {
		nParticleSynthetic += Synthetic;
		if (nParticleSynthetic < 0)
		{
			nParticleSynthetic = 0;
		}
	}	//����

	static void AddVtx(int Vtx) { m_nVtx += Vtx; }
	static void AddType(int nType) { m_nType += nType; }	//���^�C�v

	static void AddTexMoveU(float MoveU) { m_TexMove.x += MoveU; }	//�e�N�X�`��U
	static void AddTexMoveV(float MoveV) { m_TexMove.y += MoveV; }	//�e�N�X�`��V
	static void AddTexNumU(float NumU) { m_TexNum.x += NumU; }	//�e�N�X�`������
	static void AddTexNumV(float NumV) { m_TexNum.y += NumV; }	//�e�N�X�`������

	static void AddSecondType(int SecondType) { m_nSecondTime += SecondType; }

	static void AddTexPatternU(float PatternU) {m_TexPattern.x += PatternU;}	//�e�N�X�`��U
	static void AddTexPatternV(float PatternV) { m_TexPattern.y += PatternV; }	//�e�N�X�`��V
	static void AddAnimCont(int AnimCont) { m_nAnimCont += AnimCont; }	//�e�N�X�`��V
	static void AddSplitU(float SplitU) { m_nSplit.x += SplitU; }	//�e�N�X�`��V
	static void AddSplitV(float SplitU) { m_nSplit.y += SplitU; }	//�e�N�X�`��V
	static void AddHigth(float Higth) { m_fHigth += Higth; }	//����
	
	static void AddContorolBezierX(float NumX) { m_ContorolBezier.x += NumX;}	//����_
	static void AddContorolBezierY(float NumY) { m_ContorolBezier.y += NumY;}	//����_
	static void AddContorolBezierZ(float NumZ) { m_ContorolBezier.z += NumZ;}	//����_

	static void AddSecondTex(int SecondTex) { m_SecondTex += SecondTex; }	//����_

	static void AddAnimPatternType(int AnimPatternType) { m_AnimPatternType += AnimPatternType; }	//����_

private:
	static CKeyboard *m_pKeyboard;
	static int m_SerectColor;		//�F�I��
	static bool m_bTap;	//�^�b�v�ŏo�����ǂ���
	static D3DCOLORVALUE m_ControlColor;		//�F�ύX
	static D3DCOLORVALUE m_ControlChangeCol;	//�����l
	static float m_ControlSize;			//�T�C�Y
	static float m_ControlChangeSize;		//�T�C�Y����
	static int m_nLife;	//����
	static int m_nTex;	//�e�N�X�`���I��
	static int m_nDensity;	//���x
	static int m_nPattern;	//�p�^�[��

	static bool m_RandMoveX;	//�����_��X ON OFF
	static bool m_RandMoveY;	//�����_��Y ON OFF

	static bool m_ColorR;	//�J���[�����_�� ON OFF
	static bool m_ColorG;	//�J���[�����_�� ON OFF
	static bool m_ColorB;	//�J���[�����_�� ON OFF

	static float m_fAddRotate;	//��]

	static int nSynthetic;	//�����֌W

	static D3DXVECTOR2 m_TexMove;	//�e�N�X�`�����W

	//�QD
	static bool m_bMouseCursor;			//�J�[�\���Ǐ]
	static D3DXVECTOR2 m_move;	//�����̈ړ��l
	//�ŗL
	static D3DXVECTOR2 m_Addmove;	//�ړ����Z
	static int m_Diffusion;		//�����_���g�U��
	static int m_nUninitVectl;	//�����钼������
	//3D
	static bool m_bPlayerFollow;			//�v���C���[�ɂ��邩�Ǐ]
	static bool m_bPlayerMode;	//�v���C���[���삩�ǂ���
	static int m_ModelNum;	//�O�Վ茳
	static D3DXVECTOR3 m_move3d;	//�ړ����Z
	static int m_nRandMove1;	//�����_���̍ő�E�ŏ��ړ���

	static float ParticleSize;	//�p�[�e�B�N���̃T�C�Y
	static int ParticleTime;	//�p�[�e�B�N����������
	static float fDistance;		//�o���n�_
	static int nActiveTime;		//���ʎ���
	static float fMaxSize;		//�ő�̑傫��
	static float fParticleAddSize;	//�p�[�e�B�N���傫�������ύX
	static D3DCOLORVALUE m_ParticleColor;		//�p�[�e�B�N���F
	static D3DCOLORVALUE m_ParticleAddCol;	//�p�[�e�B�N���F���Z
	static int nParticleSynthetic;	//�p�[�e�B�N�������֌W
	static float ActiveAddSize;	//�A�N�e�B�u���̑傫���ύX
	static int m_nSecondTime;	//�Q�Ԗڂ̎���
	static int m_SecndType;	//2�ڂ̃p�^�[���I��

	//��
	static int m_nVtx;	//�����_��
	static int m_nType;	//�^�C�v

	static D3DXVECTOR2 m_TexNum;	//�e�N�X�`������

	//�O��
	static int m_ModelTrajecNum;	//�O�Ր�[
	static D3DCOLORVALUE m_TrajectColor;		//�F�ύX
	static D3DCOLORVALUE m_TrajectChangeCol;	//�F�ύX

	static D3DXVECTOR2 m_TexPattern;
	static int m_nAnimCont;	//�A�j���[�V�����J�E���g
	static D3DXVECTOR2 m_nSplit;	//������
	static float m_fHigth;	//����
	static D3DXVECTOR3 m_ContorolBezier;	//�x�W�F����_
	static int m_SecondTex;

	static int m_AnimPatternType;

};

#endif