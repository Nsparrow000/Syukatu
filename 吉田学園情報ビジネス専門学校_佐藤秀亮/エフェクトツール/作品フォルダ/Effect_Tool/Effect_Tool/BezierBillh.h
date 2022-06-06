//=============================================================================
// �x�W�F�Ȑ��ړ��r���{�[�h���� [BezierBill.h]
// Author : �����G��
//=============================================================================
#ifndef _BEZIERBILL_H_
#define _BEZIERBILL_H_

#include "plane.h"
#include "billEffect.h"

class CBezierBill : public CBillEffect
{
public:
	CBezierBill(int nPriority);	//�R���X�g���N�^
	~CBezierBill();	//�f�X�g���N�^

	typedef struct
	{
		double x;//�z�[�~���O���W
		double y;
		double z;

		double u;
		int Counter;
		int Counter2;
		int DivNum;

		double P0[3];
		double P1[3];
		double P2[3];
		double P3[3];// ����_

		bool f;
	} HOMING_BEZIER;

	HRESULT Init(D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nTex, int nLife,
		D3DXVECTOR2 TexNum,
		D3DXVECTOR2 TexMove,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 Target,
		int Speed,
		D3DXVECTOR3 ControlBezier,
		D3DXVECTOR3 rot,
		float TrajectSize,
		D3DCOLORVALUE FastTrajecttcolor,
		D3DCOLORVALUE FastTrajectMincolor,
		D3DCOLORVALUE SecondTrajecttcolor,
		D3DCOLORVALUE SecondTrajectMincolor,
		float TrajectMinSize,
		int TrajectTex,
		int TrajectLife,
		float DistanceTarget,
		int Synthetic,
		int TrajectSynthetic);

	void Uninit();
	void Update();
	void Draw();

	static CBezierBill *Create(D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nTex, int nLife,
		D3DXVECTOR2 TexNum,
		D3DXVECTOR2 TexMove,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		D3DXVECTOR3 pos,
		D3DXVECTOR3 Target,
		int Speed,
		D3DXVECTOR3 ControlBezier,
		D3DXVECTOR3 rot,
		float TrajectSize,
		D3DCOLORVALUE FastTrajecttcolor,
		D3DCOLORVALUE FastTrajectMincolor,
		D3DCOLORVALUE SecondTrajecttcolor,
		D3DCOLORVALUE SecondTrajectMincolor,
		float TrajectMinSize,
		int TrajectTex,
		int TrajectLife,
		float DistanceTarget,
		int Synthetic,
		int TrajectSynthetic);

	void PredictTraject();

private:
	HOMING_BEZIER m_Bezier;

	D3DCOLORVALUE m_TrajectColor;
	D3DCOLORVALUE m_AddTrajectColor;
	D3DCOLORVALUE m_TrajectColor1;
	D3DCOLORVALUE m_AddTrajectColor1;

	float m_TrajectSize;
	float m_TrajectAddSize;

	int m_TjajectTex;
	int m_TrajectLife;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Size;
	D3DXVECTOR3 m_Oldpos;

	D3DXVECTOR3 m_Target;	//�ڕW�n�_
	D3DXVECTOR3 m_ControlBezier;	//����_
	int m_Speed;	//�X�s�[�h(�x�W�F�̒ʉߓ_��)

	float m_fRandAngle;
	float m_fRandAngle2;
	float m_nDistanse;
	float m_XZr;	//�p�xxz

	int m_TrajectSynthetic;
};

#endif // !_BEZIERBILL_H_
