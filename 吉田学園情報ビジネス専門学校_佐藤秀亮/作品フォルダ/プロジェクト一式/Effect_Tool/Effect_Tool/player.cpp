//---------------------------
//Author:�O��q��
//���f��(player.cpp)
//---------------------------
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "keyboard.h"
#include "camera.h"
#include "fade.h"
#include "model.h"

#include "Trajectory.h"
#include "straight3d.h"

#include "control.h"

#include <assert.h>

//=============================================================================
//�ÓI
//=============================================================================

//=============================================================================
//�}�N��
//=============================================================================
//#define MOVE_1 (rand()% 25) + 1 - (rand()% 25)

CPlayer::CPlayer(int nPriority) : CScene3D::CScene3D(nPriority)
{

}

CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName)
{
	Load(aFileName);
	SetPos(pos);
	SetRot(rot);
	m_rotDesh = rot;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosOld = pos;
	m_RestartPos = pos;
	m_pKeyboard = CManager::GetKeyboard();
	m_pMouse = CManager::GetMouse();
	m_pCamera = CManager::GetRenderer()->GetCamera();
	m_pCamera->ResetRot();
	m_bJump = true;
	m_bLandObject = false;
	D3DXVECTOR3 size;
	size.x = GetRadius();
	size.y = 0.0f;
	size.z = GetRadius();
	MotionChange(MOTIONTYPE_RETURN);
	m_bLanding = true;

	m_bSavePos = false;
	m_nSaveFrame = 0;

	m_bSavePosPlayer = true;

	//m_TrajecMaxPos = GetPos();
	//m_TrajecMinPos = GetPos();
	m_nSaveTrajecPlayerFrame = 0;

	return S_OK;
}

//�I������
void CPlayer::Uninit()
{
	CScene3D::Uninit();
}

//�X�V����
void CPlayer::Update()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	pos = GetPos();
	posOld = pos;
	bool bRun = false;
	bool bJump;

	if (m_bJump == false && m_bLandObject == false)
	{
		bJump = false;
	}
	else
	{
		bJump = true;
		m_bJump = true;
	}

	if (CControl::GetPlayerMode() == true)
	{

		if (m_pKeyboard != NULL)
		{
			if (m_pKeyboard->GetPress(DIK_A) == true)
			{
				if (m_pKeyboard->GetPress(DIK_S) == true)
				{
					Move(-0.75f);
				}
				else if (m_pKeyboard->GetPress(DIK_W) == true)
				{
					Move(-0.25f);
				}
				else
				{
					Move(-0.5f);
				}
				bRun = true;
			}
			else if (m_pKeyboard->GetPress(DIK_D) == true)
			{
				if (m_pKeyboard->GetPress(DIK_S) == true)
				{
					Move(0.75f);
				}
				else if (m_pKeyboard->GetPress(DIK_W) == true)
				{
					Move(0.25f);
				}
				else
				{
					Move(0.5f);
				}
				bRun = true;
			}

			else if (m_pKeyboard->GetPress(DIK_W) == true)
			{
				Move(0.0f);
				bRun = true;
			}
			else if (m_pKeyboard->GetPress(DIK_S) == true)
			{
				Move(1.0f);
				bRun = true;
			}
			else
			{
				Stop();
				bRun = false;
			}
			if (bRun == true && m_bJump == true && m_motionType != MOTIONTYPE_RUN)
			{
				MotionChange(MOTIONTYPE_RUN);
			}
			if (bRun == false && m_motionType == MOTIONTYPE_RUN)
			{
				MotionChange(MOTIONTYPE_RETURN);
			}
			if (m_pKeyboard->GetKey(DIK_SPACE) == true && m_bJump == true)
			{
				if (m_bSlack == true)
				{
					m_move.y = m_fJump;
					m_bJump = false;
					m_bLanding = false;
					MotionChange(MOTIONTYPE_JUMP);
				}
				else
				{
					m_move.y = m_fJump;
					m_bJump = false;
					m_bLanding = false;

					MotionChange(MOTIONTYPE_JUMP);
				}
			}
			if (m_pKeyboard->GetKey(DIK_P) == true)
			{
				MotionChange(CPlayer::MOTIONTYPE_ACTION);
			}

			if (m_bJump == false)
			{
				m_move.y -= m_fGravity;
			}
			if (m_bLandObject == true)
			{
				m_bJump = true;
			}
		}
		pos += m_move;

	}
	else
	{
		if (m_motionType != CPlayer::MOTIONTYPE_NEUTRAL && m_motionType != CPlayer::MOTIONTYPE_ACTION)
		{
			MotionChange(CPlayer::MOTIONTYPE_NEUTRAL);
		}
	}


	if (m_pMouse != NULL)
	{
		m_pCamera->AddRotY(m_pMouse->MouseX() * 0.003f);
		m_pCamera->AddRotX(m_pMouse->MouseY() * 0.003f);

		if (m_pMouse->GetMouseButton(CMouse::DIM_L) == true)
		{
			MotionChange(CPlayer::MOTIONTYPE_ACTION);
		}
	}

	m_bJump = Land(&pos, posOld);

	if (m_bJump == false)
	{
		UnderSearch(pos);
	}
	m_pCamera->SetPosV(D3DXVECTOR3(pos.x, pos.y + 140.0f, pos.z - 300.0f));
	m_pCamera->SetPosR(D3DXVECTOR3(pos.x, pos.y + m_fHeight, pos.z));
	SetPos(pos);
	
	D3DXVECTOR3 rot = GetRot();
	if (m_rotDesh.y >= D3DX_PI)
	{
		m_rotDesh.y -= D3DX_PI * 2;
	}
	if (m_rotDesh.y < -D3DX_PI)
	{
		m_rotDesh.y += D3DX_PI * 2;
	}
	if (rot.y >= D3DX_PI)
	{
		rot.y -= D3DX_PI * 2;
	}
	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}
	if (rot.y != m_rotDesh.y)
	{
		if (m_rotDesh.y - rot.y < -D3DX_PI)
		{
			rot.y += (m_rotDesh.y - rot.y + D3DX_PI * 2) * 0.14f;
		}
		else if (m_rotDesh.y - rot.y > D3DX_PI)
		{
			rot.y += (m_rotDesh.y - rot.y - D3DX_PI * 2) * 0.14f;
		}
		else
		{
			rot.y += (m_rotDesh.y - rot.y) * 0.14f;
		}
	}

	//�����p�̃��X�|�[��
	if (pos.y < -300.0f)
	{
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetPos(m_RestartPos);
		MotionChange(MOTIONTYPE_RETURN);
	}

	m_SwordTrajectPos = m_pModel[CControl::GetTrajectModelNum()]->GetMtxWorldPos();	//�O�Ր�[
	m_SwordTrajectPos2 = m_pModel[CControl::GetModelNum()]->GetMtxWorldPos();	//�O�Վ茳


	//�O��
	if (m_motionType == CPlayer::MOTIONTYPE_ACTION)
	{
		if (m_nKey >= 2)
		{
			CreateEffect(1);
		}
	}

	//���������̋O��
	if (m_motionType == CPlayer::MOTIONTYPE_RUN || m_motionType == CPlayer::MOTIONTYPE_JUMP)
	{
	}
	if (CControl::GetPattern() == 3)
	{
		CreateEffect(CControl::GetPattern());
	}
	Motion();
	SetRot(rot);
}

//�G�t�F�N�g�쐬
void CPlayer::CreateEffect(int nPattern)
{
	D3DXVECTOR3 Vectl;
	int Vectlx;
	int Vectly;
	int Vectlz;
	float Rx;
	float Ry;
	float Rz;

	bool bRx = false;
	bool bRy = false;
	bool bRz = false;

	float y;
	float z;
	float x;

	float fA;

	switch (nPattern)
	{
	case(1):
		CTrajectory::Create(
			m_SwordTrajectPos,
			D3DXVECTOR3(m_SwordTrajectPos2.x, m_SwordTrajectPos2.y, m_SwordTrajectPos2.z),
			m_SwordTrajectOldPos,
			D3DXVECTOR3(m_SwordTrajectOldPos2.x, m_SwordTrajectOldPos2.y, m_SwordTrajectOldPos2.z),
			D3DXCOLOR((float)CControl::GetControlCoror(1), (float)CControl::GetControlCoror(2), (float)CControl::GetControlCoror(3), (float)CControl::GetControlCoror(4)),
			D3DXCOLOR((float)CControl::GetChangeCol(1), (float)CControl::GetChangeCol(2), (float)CControl::GetChangeCol(3), (float)CControl::GetChangeCol(4)),
		
			D3DXCOLOR((float)CControl::GetTrajectColor(1), (float)CControl::GetTrajectColor(2), (float)CControl::GetTrajectColor(3), (float)CControl::GetTrajectColor(4)),
			D3DXCOLOR((float)CControl::GetTrajectCol(1), (float)CControl::GetTrajectCol(2), (float)CControl::GetTrajectCol(3), (float)CControl::GetTrajectCol(4)),
			D3DXVECTOR3(0.0, CControl::GetSize(), 0.0),
			D3DXVECTOR3(0.0, CControl::GetChangeSize(), 0.0),
			3, CControl::GetLife());
		break;
	case(2):
		break;
	case(3):

		Vectl = m_SwordTrajectPos - m_SwordTrajectPos2;

		fA = (float)atan2(Vectl.x, Vectl.z);

		Vectlx = (int)Vectl.x;
		Vectly = (int)Vectl.y;
		Vectlz = (int)Vectl.z;

		//�s�b�^��0����rand�Ŏ��ʂ̂�
		if (Vectlx == 0)
		{
			Vectlx = 1;
		}
		if (Vectly == 0)
		{
			Vectly = 1;
		}
		if (Vectlz == 0)
		{
			Vectlz = 1;
		}

		if (Vectlx <= 0)
		{
			Vectlx *= -1;
			bRx = true;
		}
		if (Vectly <= 0)
		{
			Vectly *= -1;
			bRy = true;
		}
		if (Vectlz <= 0)
		{
			Vectlz *= -1;
			bRz = true;
		}
		for (int nCnt = 0; nCnt < CControl::GetDensity(); nCnt++)
		{
			Rx = float(rand() % Vectlx);
			Ry = float(rand() % Vectly);
			Rz = float(rand() % Vectlz);

			if (bRx == true)
			{
				Rx *= -1;
			}
			if (bRy == true)
			{
				Ry *= -1;
			}
			if (bRz == true)
			{
				Rz *= -1;
			}

			//���������n�_���班��������
			x = float(rand()% CControl::GetRandMove1()) + 1;
			y = float(rand()% CControl::GetRandMove1()) + 1;
			z = float(rand()% CControl::GetRandMove1()) + 1;

			x /= 100;
			y /= 100;
			z /= 100;

			CStraight3D::Create(D3DXVECTOR3(m_SwordTrajectPos2.x + Rx, m_SwordTrajectPos2.y + Ry, m_SwordTrajectPos2.z + Rz),
				D3DXVECTOR3(CControl::GetSize(), CControl::GetSize(), 0.0f),
				D3DXVECTOR3(CControl::GetChangeSize(), CControl::GetChangeSize(), 0.0f),
				D3DXVECTOR3(sinf(fA) * x, y, cosf(fA) * z),
				D3DXCOLOR((float)CControl::GetControlCoror(1), (float)CControl::GetControlCoror(2), (float)CControl::GetControlCoror(3), (float)CControl::GetControlCoror(4)),
				D3DXCOLOR((float)CControl::GetChangeCol(1), (float)CControl::GetChangeCol(2), (float)CControl::GetChangeCol(3), (float)CControl::GetChangeCol(4)),
				CControl::GetTex(), CControl::GetLife());
		}
		break;

		break;
	default:
		assert(false);
		break;
	}
}

//�`�揈��
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxPlayer, mtxRot, mtxTrans;


	pDevice = CManager::GetRenderer()->GetDevice();		 //�f�o�C�X���擾����
	//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxPlayer);
	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxRot);
	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxTrans);
	//�v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxPlayer);

	SetMatrix(mtxPlayer);

	int nCntModel;
	for (nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		m_pModel[nCntModel]->Draw();
	}


	m_SwordTrajectOldPos = m_SwordTrajectPos;
	m_SwordTrajectOldPos2 = m_SwordTrajectPos2;

}

void CPlayer::Load(const char *aFileName)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	D3DXVECTOR3 rot;
	D3DXVECTOR3 pos;
	int nParent;
	CModel *paModel[32];

	int nCntParts = 0;
	//int nCntModelParts = 0;
	int nCntMotion = 0;
	int nCntKey = 0;
	char aFile[256];
	float fRadius;
	int nLoop = 0;

	bool bChara = false;
	bool bParts = false;
	bool bMotion = false;
	bool bKey = false;
	bool bKeySet = false;

	//bool bEffect = false;
	//int nCntEffect = 0;

	int nIndex;
	//int nLoop;

	FILE *pFile;
	pFile = fopen(aFileName, "r");
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nNumModel);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //���f���t�@�C���ǂݍ���
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				paModel[nCntParts] = CModel::Create(&aFile[0]);
				nCntParts++;
			}
			if (bChara == true) //CHARACTERSET��
			{
				if (strcmp(&aFile[0], "MOVE") == 0) //�ړ����x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fMove);
				}
				if (strcmp(&aFile[0], "JUMP") == 0) //�W�����v��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fJump);
				}
				if (strcmp(&aFile[0], "GRAVITY") == 0) //�d��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fGravity);
				}
				if (strcmp(&aFile[0], "RADIUS") == 0) //���a
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &fRadius);
					SetRadius(fRadius);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //�g��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fHeight);
				}
				if (strcmp(&aFile[0], "PARTSSET") == 0)
				{
					bParts = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)
				{
					bParts = false;
					nCntParts++;
				}
				if (bParts == true) //PARTSSET��
				{
					if (strcmp(&aFile[0], "INDEX") == 0) //���f���t�@�C���ǂݍ��݂̎��́A���Ԗڂ̃��f�����Ăяo����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						m_pModel[nCntParts] = paModel[nIndex];
					}
					if (strcmp(&aFile[0], "PARENT") == 0) //�e���f��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);
						if (nParent != -1)
						{
							m_pModel[nCntParts]->SetParent(m_pModel[nParent]);
						}
					}
					if (strcmp(&aFile[0], "POS") == 0) //�e�p�[�c�̏ꏊ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
						m_pModel[nCntParts]->SetOriPos(pos);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //�e�p�[�c�̊p�x
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
						m_pModel[nCntParts]->SetOriRot(rot);
					}
				}
			}
			////�G�t�F�N�g���̓ǂݍ���
			//if (bEffect == true)
			//{
			//	if (strcmp(&aFile[0], "MODEL") == 0) //���f��
			//	{
			//		fscanf(pFile, "%s", &aFile[0]);
			//		fscanf(pFile, "%d", &m_Traject[nCntEffect].CreateModel);
			//	}
			//	if (strcmp(&aFile[0], "SIZE") == 0) //�傫��
			//	{
			//		fscanf(pFile, "%s", &aFile[0]);
			//		fscanf(pFile, "%f", &m_Traject[nCntEffect].Size);
			//	}
			//	if (strcmp(&aFile[0], "ADDSIZE") == 0) //�傫���ϓ�
			//	{
			//		fscanf(pFile, "%s", &aFile[0]);
			//		fscanf(pFile, "%f", &m_Traject[nCntEffect].AddSize);
			//	}
			//	if (strcmp(&aFile[0], "COLOR") == 0) //�J���[
			//	{
			//		fscanf(pFile, "%s", &aFile[0]);
			//		fscanf(pFile, "%f %f %f %f", &m_Traject[nCntEffect].Color.r, &m_Traject[nCntEffect].Color.g, &m_Traject[nCntEffect].Color.b, &m_Traject[nCntEffect].Color.a);
			//	}
			//	if (strcmp(&aFile[0], "CHANGECOLOR") == 0) //�J���[�ϓ��l
			//	{
			//		fscanf(pFile, "%s", &aFile[0]);
			//		fscanf(pFile, "%f %f %f %f", &m_Traject[nCntEffect].ChangeColor.r, &m_Traject[nCntEffect].ChangeColor.g, &m_Traject[nCntEffect].ChangeColor.b, &m_Traject[nCntEffect].ChangeColor.a);
			//	}
			//	if (strcmp(&aFile[0], "LIFE") == 0) //���C�t
			//	{
			//		fscanf(pFile, "%s", &aFile[0]);
			//		fscanf(pFile, "%d", &m_Traject[nCntEffect].Life);
			//	}
			//}

			if (bMotion == true) //MOTIONSET��
			{
				if (strcmp(&aFile[0], "LOOP") == 0) //���̃��[�V���������[�v���邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);
					if (nLoop == 0)
					{
						m_aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						m_aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0) //�����L�[�����邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNumKey);
				}
				if (strcmp(&aFile[0], "KEYSET") == 0)
				{
					bKeySet = true;
					nCntParts = 0;
				}
				if (strcmp(&aFile[0], "END_KEYSET") == 0)
				{
					bKeySet = false;
					nCntKey++;
				}
				if (bKeySet == true) //KEYSET��
				{
					if (strcmp(&aFile[0], "FRAME") == 0) //�t���[����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "KEY") == 0)
					{
						bKey = true;
					}
					if (strcmp(&aFile[0], "END_KEY") == 0)
					{
						bKey = false;
						nCntParts++;
					}
					if (bKey == true) //KEY��
					{
						if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY, &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
						}
						if (strcmp(&aFile[0], "ROT") == 0) //�p�x
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY, &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
						}
					}
				}

			}
			//if (strcmp(&aFile[0], "EFFECTSTATE3D") == 0)
			//{
			//	bEffect = true;
			//}
			//if (strcmp(&aFile[0], "END_EFFECTSTATE3D") == 0)
			//{
			//	bEffect = false;
			//	nCntEffect++;
			//}

			if (strcmp(&aFile[0], "CHARACTERSET") == 0)
			{
				bChara = true;
				nCntParts = 0;
			}
			if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)
			{
				bChara = false;
			}
			if (strcmp(&aFile[0], "MOTIONSET") == 0)
			{
				bMotion = true;
				nCntKey = 0;
			}
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)
			{
				bMotion = false;
				nCntMotion++;
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I����1��
			{
				break;
			}
		}
		fclose(pFile);
	}
	//�uMOTIONTYPE_RETURN�v�́A�j���[�g�������[�V�����ɖ߂�ۂɌo�R���郂�[�V����
	m_aMotionInfo[MOTIONTYPE_RETURN].bLoop = false;
	m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].nFrame = 10;
	m_aMotionInfo[MOTIONTYPE_RETURN].nNumKey = 1;
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fPosX = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosX;
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fPosY = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosY;
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fPosZ = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fPosZ;
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fRotX = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotX;
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fRotY = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotY;
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts].fRotZ = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[1].aKey[nCntParts].fRotZ;
	}
}

void CPlayer::Move(float fRotY)
{
	m_move.x += (sinf(m_pCamera->GetRotY() + D3DX_PI * fRotY) * m_fMove - m_move.x) * 0.1f;
	m_move.z += (cosf(m_pCamera->GetRotY() + D3DX_PI * fRotY) * m_fMove - m_move.z) * 0.1f;
	m_rotDesh.y = m_pCamera->GetRotY() + D3DX_PI * fRotY + D3DX_PI;
}

void CPlayer::SlackMove(float fRotY)
{
	m_move.x += (sinf(fRotY) * m_fMove * 0.2f - m_move.x) * 0.05f;
	m_move.z += (cosf(fRotY) * m_fMove * 0.2f - m_move.z) * 0.05f;
}

void CPlayer::Stop()
{
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;
}

void CPlayer::Motion() //���[�V�����̓���
{
	int nCntParts;
	m_nCntMotion++;
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		if (m_nCntMotion == 1) //���������߂�(�Ή�����L�[�̊e�p�[�c��pos(rot) - ���̊e�p�[�c��pos(rot))
		{
			/*if (nCntParts != g_player.nMoveParts)
			{*/
			m_aKeyDiff[nCntParts].fPosX = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fPosX - m_pModel[nCntParts]->GetPos().x;
			m_aKeyDiff[nCntParts].fPosY = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fPosY - m_pModel[nCntParts]->GetPos().y;
			m_aKeyDiff[nCntParts].fPosZ = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fPosZ - m_pModel[nCntParts]->GetPos().z;
			//}
			//else
			//{
			//	g_player.KeyMove.fPosX = sinf(D3DX_PI + g_player.rot.y) * g_player.MotionInfo.aKeyInfo[g_player.nKey].fMove;
			//	//g_player.KeyMove.fPosY = g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].aKey[nCntParts].fPosY;
			//	g_player.KeyMove.fPosZ = cosf(D3DX_PI + g_player.rot.y) * g_player.MotionInfo.aKeyInfo[g_player.nKey].fMove;
			//}
			m_aKeyDiff[nCntParts].fRotX = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fRotX - m_pModel[nCntParts]->GetRot().x;
			if (m_aKeyDiff[nCntParts].fRotX < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotX += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].fRotX > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotX -= D3DX_PI * 2;
			}
			m_aKeyDiff[nCntParts].fRotY = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fRotY - m_pModel[nCntParts]->GetRot().y;
			if (m_aKeyDiff[nCntParts].fRotY < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotY += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].fRotY > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotY -= D3DX_PI * 2;
			}
			m_aKeyDiff[nCntParts].fRotZ = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].fRotZ - m_pModel[nCntParts]->GetRot().z;
			if (m_aKeyDiff[nCntParts].fRotZ < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotZ += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].fRotZ > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].fRotZ -= D3DX_PI * 2;
			}
		}
		//if (nCntParts != g_player.nMoveParts)
		//{
		D3DXVECTOR3 posOld;
		posOld = m_pModel[nCntParts]->GetPos();
		posOld.x += m_aKeyDiff[nCntParts].fPosX / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		posOld.y += m_aKeyDiff[nCntParts].fPosY / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		posOld.z += m_aKeyDiff[nCntParts].fPosZ / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		m_pModel[nCntParts]->SetPos(posOld);
		//}
		//else
		//{
		//	if (g_player.KeyMove.fPosX != 0.0f)
		//	{
		//		g_player.move.x = g_player.KeyMove.fPosX;
		//	}
		//	//g_player.pos.y += g_player.KeyMove.fPosY / g_player.aMotionInfo[g_player.motionType].aKeyInfo[g_player.nKey].nFrame;
		//	if (g_player.KeyMove.fPosZ != 0.0f)
		//	{
		//		g_player.move.z = g_player.KeyMove.fPosZ;
		//	}
		//}
		D3DXVECTOR3 rotOld;
		rotOld = m_pModel[nCntParts]->GetRot();
		rotOld.x += m_aKeyDiff[nCntParts].fRotX / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		rotOld.y += m_aKeyDiff[nCntParts].fRotY / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		rotOld.z += m_aKeyDiff[nCntParts].fRotZ / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		m_pModel[nCntParts]->SetRot(rotOld);
	}
	if (m_nCntMotion == m_MotionInfo.aKeyInfo[m_nKey].nFrame)
	{
		m_nCntMotion = 0;
		m_nKey++;
		if (m_nKey == m_MotionInfo.nNumKey)
		{
			if (m_MotionInfo.bLoop == false)
			{
				if (m_motionType != MOTIONTYPE_RETURN)
				{
					MotionChange(MOTIONTYPE_RETURN);
				}
				else
				{
					MotionChange(MOTIONTYPE_NEUTRAL);
				}
			}
			m_nKey = 0;
		}
	}
}

void CPlayer::MotionChange(MOTIONTYPE motionType)
{
	m_motionType = motionType;
	m_MotionInfo = m_aMotionInfo[motionType];
	m_nCntMotion = 0;
	m_nKey = 0;
}

bool CPlayer::Land(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld)
{
	CScene *pScene;
	pScene = GetScene(0);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD)
		{
			D3DXVECTOR3 pos = pScene->GetPos();
			D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
			D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
			if (pPos->x - GetRadius() <= pos.x + VtxMax.x && pos.x + VtxMin.x <= pPos->x + GetRadius() &&
				pPos->z - GetRadius() <= pos.z + VtxMax.z && pos.z + VtxMin.z <= pPos->z + GetRadius())
			{
				float fRotX = atan2f(VtxMax.y - VtxMin.y, VtxMax.z - VtxMin.z);
				float fFieldY = (pPos->z - (pos.z + VtxMin.z * 0.75f)) * tanf(fRotX) + pos.y + VtxMin.y * 0.75f;
				if (posOld.y + 3.0f >= fFieldY && fFieldY >= pPos->y - 3.0f)
				{
					m_move.y = 0.0f;
					pPos->y = fFieldY;
					if (m_bLanding == false)
					{
						MotionChange(MOTIONTYPE_LANDING);
						m_bLanding = true;
					}
					return true;
				}

			}
		}
		pScene = pSceneNext;
	}
	return false;
}

void CPlayer::UnderSearch(D3DXVECTOR3 pos)
{
	CScene *pScene;
	CScene *pUnderScene = NULL;
	int nCntScene;
	for (nCntScene = 0; nCntScene < 7; nCntScene++)
	{
		pScene = GetScene(nCntScene);
		float fPosY = -10000.0f;
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->GetNext();
			if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD)
			{
				D3DXVECTOR3 Scenepos = pScene->GetPos();
				D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
				D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
				if (pos.x - GetRadius() < Scenepos.x + VtxMax.x && Scenepos.x + VtxMin.x < pos.x + GetRadius() &&
					pos.z - GetRadius() < Scenepos.z + VtxMax.z && Scenepos.z + VtxMin.z < pos.z + GetRadius())
				{
					if (pos.y >= Scenepos.y + VtxMin.y && fPosY <= Scenepos.y + VtxMin.y)
					{
						fPosY = Scenepos.y + VtxMin.y;
						pUnderScene = pScene;
					}
				}
			}
			pScene = pSceneNext;
		}
	}
	if (pUnderScene != NULL)
	{
		D3DXVECTOR3 Scenepos = pUnderScene->GetPos();
		D3DXVECTOR3 VtxMax = pUnderScene->GetVtxMax();
		D3DXVECTOR3 VtxMin = pUnderScene->GetVtxMin();
		float fRotX;
		float fFieldY;
		if (pUnderScene->GetObjType() == CScene::OBJECTTYPE_FIELD)
		{
			fRotX = atan2f(VtxMax.y - VtxMin.y, VtxMax.z - VtxMin.z);
			fFieldY = (pos.z - (Scenepos.z + VtxMin.z * 0.75f)) * tanf(fRotX) + Scenepos.y + VtxMin.y * 0.75f;
			if (pos.y < fFieldY)
			{
				fFieldY = -100000.0f;
			}
		}
		else
		{
			fRotX = 0.0f;
			fFieldY = Scenepos.y + VtxMax.y;
		}
	}
}

CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer(3);
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, rot, aFileName);
	}
	return pPlayer;
}
