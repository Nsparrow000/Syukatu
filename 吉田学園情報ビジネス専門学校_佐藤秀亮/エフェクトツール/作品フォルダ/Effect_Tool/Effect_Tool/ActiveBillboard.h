//=============================================================================
// (�t�B�[���h�̃r���{�[�h��)3D�G�t�F�N�g���� [ActiveBillboard.h]
// Author : �����G��
//=============================================================================
#ifndef _ACTIVEBILLBORARD_H_
#define _ACTIVEBILLBORARD_H_

#include "main.h"
#include "billEffect.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************


class CActiveBillBoard : public CBillEffect
{
public:
	typedef enum
	{
		START,
		ACTIVE,
		END,
		MAX,
	} EFFECT_TIME;


	CActiveBillBoard(int nPriority);
	~CActiveBillBoard();


	HRESULT Init(D3DXVECTOR3 pos,
		D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		D3DXVECTOR3 move,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nType,
		int nLife,
		int Synsetic,
		int FieldTime,
		float MaxSize,
		float AddSize,
		bool PresetCreate,
		int nPattern,
		D3DXVECTOR2 TexMove,
		D3DXVECTOR2 TexNum,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		ANIMPATTERN AnimPattern);

		void Uninit();
	void Update();
	void Draw();

	static CActiveBillBoard *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 Size,
		D3DXVECTOR3 MinSize,
		D3DXVECTOR3 move,
		D3DCOLORVALUE color,
		D3DCOLORVALUE Mincolor,
		int nType,
		int nLife,
		int Synsetic,
		int FieldTime,
		float MaxSize,
		float AddSize,
		bool PresetCreate,
		int nPattern,
		D3DXVECTOR2 TexMove,
		D3DXVECTOR2 TexNum,
		int nAnimCounter,
		D3DXVECTOR2 nSplit,
		ANIMPATTERN AnimPattern);

private:
	EFFECT_TIME EffectTime;	//�G�t�F�N�g�̍��̏��

	D3DXVECTOR3 m_move;	//�ړ��l
	D3DXVECTOR3 m_rot;	//�ړ��l

	int m_ActiveTime;	//�ғ�����
	float m_MaxSize;	//�ő�T�C�Y
	float m_AddSize;	//���Z�T�C�Y
	float m_fSize;	//�T�C�Y

	bool m_PresetCreate;	//�v���Z�b�g�������邩
	int m_CreatePreset;	//�ǂ̃v���Z�b�g�𐶐����邩

};

#endif