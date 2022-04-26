//=============================================================================
// �V�[������ [scene.h]
// Author : �����G��
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//�}�N����`
#define POLYGON_SIZE (70.0f)
#define PRIORITY (7)
#define CIRCLE (float(rand() % 324) / 100.0f - float(rand() % 324) / 100.0f) //�~

class CCameraPanel;

class CScene
{
public:

	//�I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJECTTYPE_NONE = 0,
		OBJECTTYPE_PLAYER,
		OBJECTTYPE_UI,
		OBJECTTYPE_EFFECT,
		OBJECTTYPE_FIELD,
		OBJECTTYPE_MAX
	} OBJTYPE;

	//�����蔻��
	typedef enum
	{
		COLLISION_SPHERE = 0,
		COLLISION_PALL,
		COLLISION_SQUARE,
		COLLISION_MAX
	} COLLISION;

	CScene(int nPriority = 3);
	virtual ~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	CScene *GetNext() { return m_pNext[m_nPriority]; }

	static CScene *GetScene(int nPriority) { return m_pTop[nPriority]; }
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	//�I�u�W�F�N�g�^�C�v
	void SetObjType(OBJTYPE obj) { m_objType = obj; }
	OBJTYPE GetObjType() const { return m_objType; }

	D3DXVECTOR3 GetPos() const { return m_pos; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

	void SetRadius(float fRadius) { m_fRadius = fRadius; }
	float GetRadius() { return m_fRadius; }	//�����̔���

	COLLISION GetCollision() const { return m_Collision; }	//���̔���̎��
	void SetCollision(COLLISION collision) { m_Collision = collision; }

	//�I�u�W�F�N�g�̍ŏ��ő�
	D3DXVECTOR3 GetVtxMax() const { return m_vtxMaxModel; }
	void SetVtxMax(D3DXVECTOR3 VtxMax) { m_vtxMaxModel = VtxMax; }

	D3DXVECTOR3 GetVtxMin() const { return m_vtxMinModel; }
	void SetVtxMin(D3DXVECTOR3 VtxMin) { m_vtxMinModel = VtxMin; }

	//�J����
	D3DXVECTOR3 GetCameraPosV() const { return m_CameraPosV; }
	void SetCameraPosV(D3DXVECTOR3 posV) { m_CameraPosV = posV; }
	D3DXVECTOR3 GetCameraPosR() const { return m_CameraPosR; }
	void SetCameraPosR(D3DXVECTOR3 posR){ m_CameraPosR = posR; }

	void SetDeath(bool bDeath) { m_bDeath = bDeath; }


	void SetRot(D3DXVECTOR3 Rot) { m_CameraPosR = Rot; }
	D3DXVECTOR3 GetRot() { return m_Rot; }

private:
	static CScene *m_pTop[PRIORITY]; //�擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene *m_pCur[PRIORITY]; //����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev[PRIORITY];       //�O�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pNext[PRIORITY];       //���̃I�u�W�F�N�g�̃|�C���^

	static int m_nNumAll;
	static bool m_bKey;
	D3DXVECTOR3 m_pos;
	bool m_bDeath;
	float m_fRadius;
	COLLISION m_Collision;
	D3DXVECTOR3 m_vtxMinModel; //���f���̍ŏ��l
	D3DXVECTOR3 m_vtxMaxModel; //���f���̍ő�l
	int m_nSlack;
	D3DXVECTOR3 m_CameraPosV;
	D3DXVECTOR3 m_CameraPosR;

	int m_nPriority;//�D�揇��

	OBJTYPE m_objType;							//�I�u�W�F�N�g�^�C�v
	D3DXVECTOR3 m_Rot;

protected:
	void Release();
};
#endif