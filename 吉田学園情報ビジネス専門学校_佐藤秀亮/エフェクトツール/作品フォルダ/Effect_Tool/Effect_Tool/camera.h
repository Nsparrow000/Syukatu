//=============================================================================
//
// �V�[������ [camera.h]
// Author : �����G��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

class CKeyboard;
class CMouse;

class CCamera
{
public:
	//�J�����̍\����
	typedef struct
	{
		D3DXVECTOR3 posV;     //���݂̎��_
		D3DXVECTOR3 posR;     //���݂̒����_
		D3DXVECTOR3 vecU;     //������x�N�g��
		D3DXVECTOR3 rot;     //�J�����̌���
		float fLength;
		D3DXMATRIX mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView; //�r���[�}�g���b�N�X
	} Camera;
	CCamera();
	~CCamera();
	HRESULT Init(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);
	void Uninit();
	void Update();

	float GetRotY() const { return m_camera.rot.y; }
	float GetRotX() const { return m_camera.rot.x; }
	

	void SetPosV(D3DXVECTOR3 pos) { m_camera.posV = pos; }
	void SetPosR(D3DXVECTOR3 pos) { m_camera.posR = pos; }
	void SetRot() { m_camera.rot.y = atan2f(m_camera.posR.x - m_camera.posV.x, m_camera.posR.z - m_camera.posV.z); }
	D3DXVECTOR3 GetPosR() const { return m_camera.posR; }
	D3DXVECTOR3 GetPosV() const { return m_camera.posV; }
	void AddRotY(float fRotY) { m_camera.rot.y += fRotY; }
	void AddRotX(float fRotX) { m_camera.rot.x += fRotX; }
	void ResetRot() { m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void AddLength(float Length) { m_camera.fLength += Length; }

	static CCamera *Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);

private:
	Camera m_camera;
	CKeyboard *m_pKeyboard;
	CMouse *m_pMouse;
};

#endif