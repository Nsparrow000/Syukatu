//=============================================================================
// �V�[������ [player.h]
// Author : �����G��
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene3d.h"

class CKeyboard;
class CMouse;
class CModel;
class CCamera;

class CPlayer : public CScene3D
{
	//���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,	//�ҋ@
		MOTIONTYPE_RUN,	//����
		MOTIONTYPE_ACTION,	//�U���i�A�N�V�����j
		MOTIONTYPE_JUMP,	//�W�����v
		MOTIONTYPE_LANDING,	//���n
		MOTIONTYPE_RETURN, //�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
		MAX_MOTION
	} MOTIONTYPE;

	//�L�[�̍\����
	typedef struct
	{
		float fPosX; //�ʒuX
		float fPosY; //�ʒuY
		float fPosZ; //�ʒuZ
		float fRotX; //����X
		float fRotY; //����Y
		float fRotZ; //����Z
	} KEY;

	//�L�[���̍\����
	typedef struct
	{
		int nFrame; //�t���[��
		KEY aKey[32]; //�e���f���̃L�[�v�f []���̓p�[�c�̍ő吔
	} KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop; //���[�v���邩�ǂ���
		int nNumKey; //�L�[�̑���
		int nNonOpe;
		KEY_INFO aKeyInfo[16]; //�L�[��� []���̓L�[�̍ő吔
	} MOTION_INFO;

	//�o�������G�t�F�N�g�̎��
	typedef enum
	{
		TYPE_TRAJECT,
		TYPE_MAX,
	}EFFECT_TYPE;

	typedef struct
	{
		int CreateModel;
		float Size;
		float AddSize;
		D3DCOLORVALUE Color;
		D3DCOLORVALUE ChangeColor;
		int Life;
	} TRAJECT_STATE;

public:
	CPlayer(int nPriority);
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);
	void Uninit();
	void Update();
	void Draw();

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);

	void CreateEffect(int Pattern);
private:
	void Load(const char *aFileName);
	void Move(float fRotY);
	void SlackMove(float fRotY);
	void Stop();
	void UnderSearch(D3DXVECTOR3 pos);
	bool Land(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);

	void Motion();
	void MotionChange(MOTIONTYPE motionType);

	D3DXVECTOR3 m_PosOld;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rotDesh;
	D3DXVECTOR3 m_RestartPos;
	float m_fRot;
	float m_fMove;
	float m_fGravity;
	float m_fJump;
	float m_fHeight;
	bool m_bJump;
	bool m_bSlack;
	bool m_bSlackMove;
	bool m_bLandObject;
	int m_nNumModel;
	MOTIONTYPE m_motionType;
	int m_nCntMotion;
	MOTION_INFO m_aMotionInfo[MAX_MOTION];
	MOTION_INFO m_MotionInfo;
	int m_nNeutralTime;
	KEY m_aKeyDiff[32];
	int m_nKey;
	CModel *m_pModel[32]; //���f���i�p�[�c�j
	CKeyboard *m_pKeyboard;
	CMouse *m_pMouse;
	CCamera *m_pCamera;

	TRAJECT_STATE m_Traject;	//�G�t�F�N�g�̏��

	bool m_bLanding;		//���n

	//�O�Տ����ŕK�v
	D3DXVECTOR3 m_SwordTrajectPos;	//���ݐ�[�̏ꏊ
	D3DXVECTOR3 m_SwordTrajectPos2;	//���ݎ茳�̏ꏊ
	D3DXVECTOR3 m_SwordTrajectOldPos;	//1�t���[���O�̐�[�̏ꏊ
	D3DXVECTOR3 m_SwordTrajectOldPos2;	//1�t���[���O�̎茳�̏ꏊ

	static bool m_MouseButtenPush;	//�{�^�������Ă邩
	static int m_MousePushTime;	//�����Ă鎞��

	static bool m_PushDeley;	//�{�^�������Ă邩
	static int m_DeleyTime;	//�����Ă鎞��

};
#endif