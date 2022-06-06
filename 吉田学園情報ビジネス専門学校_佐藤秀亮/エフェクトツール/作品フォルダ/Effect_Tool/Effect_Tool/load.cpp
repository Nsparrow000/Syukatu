//---------------------------
//Author:�����G��
//���[�h����(load.cpp)
//---------------------------
#include "load.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "field.h"
#include "light.h"
#include "fade.h"
#include "camera.h"
#include "scene.h"

#include "Butten.h"

CLoad::CLoad()
{

}

CLoad::~CLoad(void)
{

}

void CLoad::Load(const char *aFileName)
{
	FILE *pFile;
	pFile = fopen(aFileName, "r");
	char aFile[256];
	char aPlayerFile[256];
	int nNumModel;
	bool bField = false;
	bool bLight = false;
	bool bCamera = false;
	bool bPlayer = false;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nTex;
	int nBlock[2];
	D3DXVECTOR3 size;
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nCntLight = 0;
	D3DXCOLOR col;
	D3DXVECTOR3 vec;
	D3DXVECTOR2 Tex;
	D3DXVECTOR3 posV;
	D3DXVECTOR3 posR;
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) //���f����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nNumModel);
			}
			if (strcmp(&aFile[0], "FIELDSET") == 0) //�n��
			{
				bField = true;
			}
			if (strcmp(&aFile[0], "END_FIELDSET") == 0) //�n��
			{
				size.x = Tex.x * nBlock[0];
				size.z = Tex.y * nBlock[1];
				size.y = -sinf(rot.x) * size.z;
				//size.y = 0.0f;
				CField::Create(size, pos, nTex, Tex);
				bField = false;
			}
			if (strcmp(&aFile[0], "LIGHTSET") == 0) //���C�g
			{
				bLight = true;
			}
			if (strcmp(&aFile[0], "END_LIGHTSET") == 0) //���C�g
			{
				CLight::Create(col, vec, nCntLight);
				nCntLight++;
				bLight = false;
			}
			if (strcmp(&aFile[0], "CAMERASET") == 0) //�J����
			{
				bCamera = true;
			}
			if (strcmp(&aFile[0], "END_CAMERASET") == 0) //�J����
			{
				bCamera = false;
			}
			if (strcmp(&aFile[0], "PLAYERSET") == 0) //�v���C���[
			{
				bPlayer = true;
			}
			if (strcmp(&aFile[0], "END_PLAYERSET") == 0) //�v���C���[
			{
				CPlayer::Create(pos, rot, aPlayerFile);
				bPlayer = false;
			}

			if (bField == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //�p�x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
				if (strcmp(&aFile[0], "BLOCK") == 0) //�e�N�X�`���ׂ̍���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &Tex.x, &Tex.y);
				}
				if (strcmp(&aFile[0], "SIZE") == 0) //�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d %d", &nBlock[0], &nBlock[1]);
				}
				if (strcmp(&aFile[0], "TEXTYPE") == 0) //�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
			}
			if (bLight == true)
			{
				if (strcmp(&aFile[0], "DIRECTION") == 0) //���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &vec.x, &vec.y, &vec.z);
				}
				if (strcmp(&aFile[0], "DIFFUSE") == 0) //���̐F
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &col.r, &col.g, &col.b);
					col.a = 1.0f;
				}
			}
			if (bCamera == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //���_
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
					CManager::GetRenderer()->GetCamera()->SetPosV(pos);
				}
				if (strcmp(&aFile[0], "REF") == 0) //�����_
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
					CManager::GetRenderer()->GetCamera()->SetPosR(pos);
				}
			}
			if (bPlayer == true)
			{
				if (strcmp(&aFile[0], "MOTION_FILENAME") == 0) //���f���̏ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%s", &aPlayerFile[0]);
				}
				if (strcmp(&aFile[0], "POS") == 0) //���f���̏ꏊ
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "ROT") == 0) //���f���̕���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
					rot.x = rot.x / 180.0f * D3DX_PI;
					rot.y = rot.y / 180.0f * D3DX_PI;
					rot.z = rot.z / 180.0f * D3DX_PI;
				}
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I���
			{
				break;
			}
		}
	}
}

void CLoad::LoadButten(const char *aFileName)
{
	FILE *pFile = fopen(aFileName, "r");
	char aFile[256];

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	D3DXVECTOR2 Size = D3DXVECTOR2(0.0f,0.0f);
	int Operation = 0;
	int nTex = 0;
	float nIndeNum = 0.0f;
	int nDisplay;
	int nPattern;
	bool bButten = false;

	bool bButtenState = false;
	bool bButtenPatten = false;
	int nButtenPatten = 0;

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���

			if (bButten == true)
			{
				if (strcmp(&aFile[0], "POS") == 0) //���W
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
				}
				if (strcmp(&aFile[0], "SIZE") == 0)	//�傫��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f %f", &Size.x,&Size.y);
				}
				if (strcmp(&aFile[0], "TEXTURE") == 0)	//�e�N�X�`��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nTex);
				}
				if (strcmp(&aFile[0], "OPERATION") == 0)	//�ݒ���e
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &Operation);
				}
				if (strcmp(&aFile[0], "INDENUM") == 0)	//�������鐔�l
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &nIndeNum);
				}
				if (strcmp(&aFile[0], "DISPLAY") == 0)	//�\������{�^��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nDisplay);
				}
				if (strcmp(&aFile[0], "PATTERN") == 0)	//�ǂ̃p�^�[�����ɕ\�����邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nPattern);
				}
			}

			if (bButtenPatten == true)
			{
				if (bButtenState == true)
				{
					if (strcmp(&aFile[0], "POS") == 0) //���W
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
					}
					if (strcmp(&aFile[0], "SIZE") == 0)	//�傫��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f", &Size.x, &Size.y);
					}
					if (strcmp(&aFile[0], "TEXTURE") == 0)	//�e�N�X�`��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nTex);
					}
					if (strcmp(&aFile[0], "OPERATION") == 0)	//�ݒ���e
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &Operation);
					}
					if (strcmp(&aFile[0], "INDENUM") == 0)	//�������鐔�l
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &nIndeNum);
					}
					if (strcmp(&aFile[0], "PATTERN") == 0)	//�ǂ̃p�^�[�����ɕ\�����邩
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nPattern);
					}
				}

				if (strcmp(&aFile[0], "BUTTENSTATE") == 0) //�{�^��
				{
					bButtenState = true;
				}
				if (strcmp(&aFile[0], "END_BUTTENSTATE") == 0) //�{�^��
				{
					CButten::SetButtenState(pos, Size.x, Size.y, nTex, (CButten::OPERATION)Operation, nIndeNum, (CButten::DISPLAY_PATTERN)nPattern);

					bButtenState = false;
				}
			}

			if (strcmp(&aFile[0], "BUTTENSET") == 0) //�{�^��
			{
				bButten = true;
			}
			if (strcmp(&aFile[0], "END_BUTTENSET") == 0) //�{�^��
			{
				bButten = false;
				CButten::Create(pos, Size.x, Size.y, nTex, (CButten::OPERATION)Operation, nIndeNum,(CButten::DISPLAY)nDisplay,(CButten::DISPLAY_PATTERN)nPattern);
			}


			if (strcmp(&aFile[0], "BUTTENPATTENSET") == 0) //�{�^��
			{
				bButtenPatten = true;
			}
			if (strcmp(&aFile[0], "END_BUTTENPATTENSET") == 0) //�{�^��
			{
				bButtenPatten = false;
				CButten::SetTotal(nButtenPatten);
				CButten::SetPatten();
				CButten::ResetTotal();
				nButtenPatten++;
			}


			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I���
			{
				break;
			}
		}
	}

}