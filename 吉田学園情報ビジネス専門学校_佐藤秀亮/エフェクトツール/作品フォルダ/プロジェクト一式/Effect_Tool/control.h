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

	static void AddColor(int Color, int nSerect);
	static void AddChangeCol(int Color, int nSerect);

	static int GetSerectColor() { return m_SerectColor; }	//�F�I��ԍ�
	
	static const float GetSize() { return m_ControlSize; }	//�T�C�Y
	static const float GetChangeSize() { return m_ControlChangeSize; }	//�T�C�Y����


	static const int GetLife() { return m_nLife; }			//����
	static const int GetTex() { return m_nTex; }				//�e�N�X�`��
	static const int GetDensity() { return m_nDensity; }		//���x
	static const bool GetTap() { return m_bTap; }	//�^�b�vON or OFF
	static const int GetPattern() { return m_nPattern; }		//�p�^�[��

	static const bool GetRandMoveX() { return m_RandMoveX; }	//�����_��XON or OFF
	static const bool GetRandMoveY() { return m_RandMoveY; }	//�����_��YON or OFF

	static void SetColorRandom(int nSerectcol , bool bAdaptation);	//�J���[�����_��ON or OFF

	//2D
	static const D3DXVECTOR2 GetMove() { return m_move; }		//�����̓����l
	static const bool GetMouseCursor() { return m_bMouseCursor; }	//�J�[�\���Ǐ]ON or OFF
	//�ŗL
	static const D3DXVECTOR2 GetAddMove() { return m_Addmove; }		//�ړ����Z
	static const int GetDiffusion() { return m_Diffusion; }
	static const int GetUninitVectl() { return m_nUninitVectl; }		//������x�N�g��

	//3D
	static const bool GetPlayerMode()  { return m_bPlayerMode; }
	static const void SetPlayerMode(bool bMode) {m_bPlayerMode = bMode; }
	static const int GetModelNum() { return m_ModelNum; }
	static const D3DXVECTOR3 Getmove3d() { return m_move3d; }		//�ړ�
	static const int GetTrajectModelNum() { return m_ModelTrajecNum; }
	static const int GetRandMove1() { return m_nRandMove1; }

	//�ŗL
	static void TrajectColor(int Color, int nSerect);
	static int GetTrajectColor(int nSerectcolor);	//�F�擾

	static void AddTrajectCol(int Color, int nSerect);
	static int GetTrajectCol(int nSerectcolor);	//�F�擾

	//�e�L�X�g�Z�[�u
	static void SaveEffect(CManager::MODE mode, int nPattern);

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

	//�QD
	static bool m_bMouseCursor;			//�J�[�\���Ǐ]
	static D3DXVECTOR2 m_move;	//�����̈ړ��l
	//�ŗL
	static D3DXVECTOR2 m_Addmove;	//�ړ����Z
	static int m_Diffusion;		//�����_���g�U��
	static int m_nUninitVectl;	//�����钼������
	//3D
	static bool m_bPlayerMode;	//�v���C���[���삩�ǂ���
	static int m_ModelNum;	//�O�Վ茳
	static D3DXVECTOR3 m_move3d;	//�ړ����Z
	static int m_nRandMove1;	//�����_���̍ő�E�ŏ��ړ���

	//���b�V������
	static int m_ModelTrajecNum;	//�O�Ր�[
	static D3DCOLORVALUE m_TrajectColor;		//�F�ύX
	static D3DCOLORVALUE m_TrajectChangeCol;	//�F�ύX

};

#endif