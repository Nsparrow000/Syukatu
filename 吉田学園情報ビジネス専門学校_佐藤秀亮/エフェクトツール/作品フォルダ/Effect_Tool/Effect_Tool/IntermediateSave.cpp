//*****************************************************************************
// ���ԃZ�[�u�݂����Ȃ�(IntermediateSave.cpp)
// Author : �����G��
//*****************************************************************************
#include "IntermediateSave.h"
#include "control.h"
#include "seteffect.h"

#include <assert.h>
//*****************************************************************************
//�}�N����`
//*****************************************************************************


//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CIntermeiateSave::CIntermeiateSave()
{

}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CIntermeiateSave::~CIntermeiateSave(void)
{

}

//*****************************************************************************
//�Z�[�u
//*****************************************************************************
void CIntermeiateSave::IntermeiateSave(CManager::MODE mode, int nPattern, const char *aModelName)
{
	FILE *pFile = fopen(aModelName, "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "#========================================================================\n");
		fprintf(pFile, "#���ԃZ�[�u�����[�h�p�e�L�X�g\n");
		fprintf(pFile, "#Author : �����G��\n");
		fprintf(pFile, "#========================================================================\n\n\n");

		if (mode == CManager::MODE_2D)
		{
			fprintf(pFile, "EFFECTSTATE2D\n");
			fprintf(pFile, "	PATTERN = %d				//�����̃p�^�[��\n", nPattern);

			fprintf(pFile, "	POS = %.1f %.1f				//���W\n", CSetEffect::GetSetPos().x, CSetEffect::GetSetPos().y);

			switch (nPattern)
			{
			case(0):
				fprintf(pFile, "	MOVE = %.1f %.1f					//����\n", CControl::GetMove().x, CControl::GetMove().y);
				fprintf(pFile, "	ADDMOVE = %.1f %.1f				//�������Z�l\n", CControl::GetAddMove().x, CControl::GetAddMove().y);
				break;
			case(1):
				fprintf(pFile, "	MOVE = %.1f					//�X�s�[�h\n", CControl::GetMove().x);
				fprintf(pFile, "	DIFFUSION = %d					//�g�U��\n", CControl::GetDiffusion());
				fprintf(pFile, "	DESTROYVEC = %d					//������x�N�g��\n", CControl::GetUninitVectl());
				fprintf(pFile, "	DISTANCE = %.1f					//����\n", CControl::GetDistance());

			case(2):
				fprintf(pFile, "	ROTATE = %.2f					//��]\n", CControl::GetRotate());
				break;
			default:
				break;
			}
			fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
			fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
			fprintf(pFile, "	COLOR = %d %d %d %d			//�J���[\n", (int)CControl::GetControlCoror(1), (int)CControl::GetControlCoror(2), (int)CControl::GetControlCoror(3), (int)CControl::GetControlCoror(4));
			fprintf(pFile, "	CHANGECOLOR = %d %d %d %d			//�J���[�ϓ��l\n", (int)CControl::GetChangeCol(1), (int)CControl::GetChangeCol(2), (int)CControl::GetChangeCol(3), (int)CControl::GetChangeCol(4));
			fprintf(pFile, "	LIFE = %d						//���C�t\n", CControl::GetLife());
			fprintf(pFile, "	DENSITY = %d						//���x\n", CControl::GetDensity());
			fprintf(pFile, "	TEXTURE = %d						//�e�N�X�`��\n", CControl::GetTex());
			fprintf(pFile, "	SYNTHETIC = %d						//����\n", CControl::GetSynthetic());

			fprintf(pFile, "END_EFFECTSTATE2D\n");

		}
		else if (mode == CManager::MODE_3D)	//3D���[�h
		{
			fprintf(pFile, "EFFECTSTATE3D\n");
			fprintf(pFile, "	PATTERN = %d				//�����̃p�^�[��\n", nPattern);
			fprintf(pFile, "	COLOR = %d %d %d %d			//�J���[\n", (int)CControl::GetColor().r, (int)CControl::GetColor().g, (int)CControl::GetColor().b, (int)CControl::GetColor().a);
			fprintf(pFile, "	CHANGECOLOR = %d %d %d %d			//�J���[�ϓ��l\n", (int)CControl::GetChangeColor().r, (int)CControl::GetChangeColor().g, (int)CControl::GetChangeColor().b, (int)CControl::GetChangeColor().a);
			fprintf(pFile, "	LIFE = %d						//����\n", CControl::GetLife());
			switch (nPattern)
			{
			case(0):
				fprintf(pFile, "	SECONDCOLOR = %d %d %d %d				//���f���P�̐F\n", (int)CControl::GetTrajectColor(1), (int)CControl::GetTrajectColor(2), (int)CControl::GetTrajectColor(3), (int)CControl::GetTrajectColor(4));
				fprintf(pFile, "	SECONDADDCOLOR = %d %d %d %d				//���f���P�̐F����\n", (int)CControl::GetTrajectCol(1), (int)CControl::GetTrajectCol(2), (int)CControl::GetTrajectCol(3), (int)CControl::GetTrajectCol(4));

				fprintf(pFile, "	TRAJECTTOP = %d				//�������f���P\n", CControl::GetModelNum());
				fprintf(pFile, "	TRAJECTCUR = %d				//�������f���Q\n", CControl::GetTrajectModelNum());
				break;
			case(1):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
				fprintf(pFile, "	DENSITY = %d						//���x\n", CControl::GetDensity());

				fprintf(pFile, "	MOVE3D = %.1f %.1f %.1f					//�ړ�\n", CControl::Getmove3d().x, CControl::Getmove3d().y, CControl::Getmove3d().z);

				fprintf(pFile, "	DISTANCE = %.1f						//��������\n", CControl::GetDistance());
				fprintf(pFile, "	TYPE = %d					//�o���ʒu�̃p�^�[��\n", CControl::GetType());
				fprintf(pFile, "	SECONDTYPE = %d					//�����_���ړ��̃p�^�[��\n", CControl::GetSecondType());
				fprintf(pFile, "	PARTICLETIME = %d						//�������Ԋu\n", CControl::GetParticleTime());
			break;
			case(2):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
				fprintf(pFile, "	DENSITY = %d						//���x\n", CControl::GetDensity());

				fprintf(pFile, "	RANDMOVE = %d				//�ړ��l\n", CControl::GetRandMove1());
				fprintf(pFile, "	TRAJECTTOP = %d				//�������f���P\n", CControl::GetModelNum());
				fprintf(pFile, "	TRAJECTCUR = %d				//�������f���Q\n", CControl::GetTrajectModelNum());
				break;
			case(3):
				fprintf(pFile, "	ROTATE = %.2f						//��]\n", CControl::GetRotate());
				fprintf(pFile, "	MOVE = %.1f						//�ړ�\n", CControl::Getmove3d().x);
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
				fprintf(pFile, "	DENSITY = %d						//�����x\n", CControl::GetDensity());

				fprintf(pFile, "	PARTICLESIZE = %.1f						//���T�C�Y\n", CControl::GetParticleSize());
				fprintf(pFile, "	PARTICLETIME = %d						//�������Ԋu\n", CControl::GetParticleTime());
				fprintf(pFile, "	DISTANCE = %.1f						//���̔�������\n", CControl::GetDistance());

				fprintf(pFile, "	ACTIVE = %d						//�ғ�����\n", CControl::GetActiveTime());
				fprintf(pFile, "	PARTICLEADDSIZE = %.1f						//���T�C�Y�ύX\n", CControl::GetParticleAddSize());
				fprintf(pFile, "	MAXSIZE = %.1f						//�t�B�[���h�ő�T�C�Y\n", CControl::GetMaxSize());

				fprintf(pFile, "	SECONDCOLOR = %d %d %d %d			//�p�[�e�B�N���J���[\n", (int)CControl::GetParticleColor(1), (int)CControl::GetParticleColor(2), (int)CControl::GetParticleColor(3), (int)CControl::GetParticleColor(4));
				fprintf(pFile, "	SECONDADDCOLOR = %d %d %d %d			//�p�[�e�B�N���J���[����\n", (int)CControl::GetParticleAddCol(1), (int)CControl::GetParticleAddCol(2), (int)CControl::GetParticleAddCol(3), (int)CControl::GetParticleAddCol(4));
				fprintf(pFile, "	SECONDSYNTHETIC = %d			//�p�[�e�B�N������\n", (int)CControl::GetParticleSynthetic());
				fprintf(pFile, "	ACTIVEADDSIZE = %.1f					//�ғ����̉ғ�����\n", CControl::GetAvctiveAddSize());

				break;
			case(4):
				fprintf(pFile, "	MOVE3D = %.1f %.1f %.1f					//�ړ�\n", CControl::Getmove3d().x, CControl::Getmove3d().y, CControl::Getmove3d().z);
				fprintf(pFile, "	ACTIVE = %d						//�ғ�����\n", CControl::GetActiveTime());
				fprintf(pFile, "	MAXSIZE = %.1f						//�t�B�[���h�ő�T�C�Y\n", CControl::GetMaxSize());
				fprintf(pFile, "	DENSITY = %d						//�����x\n", CControl::GetDensity());

				break;
			case(5):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
				fprintf(pFile, "	DENSITY = %d						//�����x\n", CControl::GetDensity());

				fprintf(pFile, "	ROTATE = %.2f						//��]\n", CControl::GetRotate());
				fprintf(pFile, "	DISTANCE = %.1f						//���̔�������\n", CControl::GetDistance());
				fprintf(pFile, "	PARTICLETIME = %d						//�������Ԋu\n", CControl::GetParticleTime());
				fprintf(pFile, "	SECONDTIME = %d						//�߂Â��܂ł̎���\n", CControl::GetSecondTime());
				fprintf(pFile, "	MAXSIZE = %.1f						//�A�N�e�B�u�T�C�Y\n", CControl::GetMaxSize());
				fprintf(pFile, "	MOVE = %.1f						//�������Z\n", CControl::Getmove3d().x);
				fprintf(pFile, "	TYPE = %d					//�p�[�e�B�N��(0)or�O��(1)\n", CControl::GetType());
				fprintf(pFile, "	SECONDTYPE = %d					//�ړ������_��\n", CControl::GetSecondType());

				break;
			case(6):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());

				fprintf(pFile, "	ROTATE = %.2f						//��]\n", CControl::GetRotate());
				fprintf(pFile, "	VTX = %d						//���_��\n", CControl::GetVtx());
				fprintf(pFile, "	TYPE = %d					//��(0)or����(1)\n", CControl::GetType());

				break;
			case(7):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());

				fprintf(pFile, "	DISTANCE = %.1f						//�㔭������\n", CControl::GetDistance());
				fprintf(pFile, "	HIGTH = %.1f						//�㋗��\n", CControl::GetHigth());
				fprintf(pFile, "	PARTICLESIZE = %.1f						//�������̕�\n", CControl::GetParticleSize());

				break;
			case(8):
				fprintf(pFile, "	SIZE = %.1f						//�傫��\n", CControl::GetSize());
				fprintf(pFile, "	ADDSIZE = %.1f					//�傫���ϓ�\n", CControl::GetChangeSize());
				fprintf(pFile, "	DENSITY = %d						//���x\n", CControl::GetDensity());

				fprintf(pFile, "	CONTROLBEZIER = %.1f %.1f %.1f						//�x�W�F����_\n", CControl::GetContorolBezierX(), CControl::GetContorolBezierY(), CControl::GetContorolBezierZ());
				fprintf(pFile, "	MOVE = %.1f						//�ړ��i����_�̐��j\n", CControl::Getmove3d().x);

				fprintf(pFile, "	SECONDCOLOR = %d %d %d %d			//�O�Ղ̐F�P\n", (int)CControl::GetParticleColor(1), (int)CControl::GetParticleColor(2), (int)CControl::GetParticleColor(3), (int)CControl::GetParticleColor(4));
				fprintf(pFile, "	SECONDADDCOLOR = %d %d %d %d			//�O�Ղ̐F�P����\n", (int)CControl::GetParticleAddCol(1), (int)CControl::GetParticleAddCol(2), (int)CControl::GetParticleAddCol(3), (int)CControl::GetParticleAddCol(4));

				fprintf(pFile, "	THERDCOLOR = %d %d %d %d				//�O�Ղ̐F�Q\n", (int)CControl::GetTrajectColor(1), (int)CControl::GetTrajectColor(2), (int)CControl::GetTrajectColor(3), (int)CControl::GetTrajectColor(4));
				fprintf(pFile, "	THERDADDCOLOR = %d %d %d %d				//�O�Ղ̐F�Q����\n", (int)CControl::GetTrajectCol(1), (int)CControl::GetTrajectCol(2), (int)CControl::GetTrajectCol(3), (int)CControl::GetTrajectCol(4));

				fprintf(pFile, "	MAXSIZE = %.1f						//�O�ՃT�C�Y\n", CControl::GetMaxSize());
				fprintf(pFile, "	SECONDTEX = %d						//�O�Ճe�N�X�`��\n", CControl::GetSecondTex());
				fprintf(pFile, "	PARTICLETIME = %d						//�O�Վ���\n", CControl::GetParticleTime());

				fprintf(pFile, "	DISTANCE = %.1f						//�^�[�Q�b�g����̃����_������\n", CControl::GetDistance());
				fprintf(pFile, "	SECONDSYNTHETIC = %d			//�O�Ս���\n", (int)CControl::GetParticleSynthetic());
				break;
			case(9):
				break;
			default:
				break;
			}

			fprintf(pFile, "	COLOR = %d %d %d %d			//�J���[\n", (int)CControl::GetControlCoror(1), (int)CControl::GetControlCoror(2), (int)CControl::GetControlCoror(3), (int)CControl::GetControlCoror(4));
			fprintf(pFile, "	CHANGECOLOR = %d %d %d %d			//�J���[�ϓ��l\n", (int)CControl::GetChangeCol(1), (int)CControl::GetChangeCol(2), (int)CControl::GetChangeCol(3), (int)CControl::GetChangeCol(4));
			fprintf(pFile, "	TEXTURE = %d						//�e�N�X�`��\n", CControl::GetTex());
			fprintf(pFile, "	SYNTHETIC = %d						//����\n", CControl::GetSynthetic());

			fprintf(pFile, "	TEXMOVE = %.3f %.3f					//�e�N�X�`���ړ�\n", CControl::GetTexMoveU(), CControl::GetTexMoveV());
			fprintf(pFile, "	TEXNUM = %.1f %.1f					//�e�N�X�`������\n", CControl::GetTexNum().x, CControl::GetTexNum().y);

			fprintf(pFile, "	TEXMOVE = %.3f %.3f					//�e�N�X�`���ړ�\n", CControl::GetTexMoveU(), CControl::GetTexMoveV());


			fprintf(pFile, "	TEXANIMCOUNT = %d					//�e�N�X�`���A�j���[�V�����J�E���g\n", CControl::GetAnimCont());
			fprintf(pFile, "	TEXSPLIT = %.0f %.0f					//�e�N�X�`��������\n", CControl::GetSplitU(), CControl::GetSplitV());
			fprintf(pFile, "	ANIMPATTERNTYPE = %d					//�A�j���[�V�����p�^�[���^�C�v\n", CControl::GetAnimPatternType());


			fprintf(pFile, "END_EFFECTSTATE3D\n");

		}

		fprintf(pFile, "END_SCRIPT\n\n");

		fclose(pFile);
	}

}

//*****************************************************************************
//���[�h
//*****************************************************************************
void CIntermeiateSave::IntermeiateLoad(CManager::MODE mode, const char *aModelName)
{
#if 1
	FILE *pFile = fopen(aModelName, "r");
	char aFile[256];

	bool bEffectState2D = false;
	bool bEffectState3D = false;

	int nPattern = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 Addmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int Diffusion = 1;
	int Destroyvec = 0;
	float fSize = 0;
	float fAddSize = 0;
	D3DCOLORVALUE col;
	D3DCOLORVALUE ChangeColor;
	int nLife = 0;
	int Density = 1;
	int nTexture = 0;
	int nSynthetic = 0;
	float fRotate = 0.0f;

	int TrajectTop = 0;
	int TrajectCur = 0;
	int RandMove = 1;
	float ParticleSize = 0.0f;
	float ParticleAddSize = 0.0f;

	int ParticleTime = 1;
	float fDistance = 1.0f;
	int nActive = 60;
	float fMaxSize = 100.0f;
	D3DCOLORVALUE Particlecol;
	D3DCOLORVALUE ParticleAddColor;

	D3DCOLORVALUE Therdcol;
	D3DCOLORVALUE TherdAddColor;

	int nParticleSynthetic = 0;
	int nSecondTime = 0;
	int nVtx = 0;
	int nType = 0;
	D3DXVECTOR2 TexMove = D3DXVECTOR2(0.0f,0.0f);
	D3DXVECTOR2 TexNum = D3DXVECTOR2(1.0f, 1.0f);
	int nSecondType = 0;
	D3DXVECTOR2 TexSplit = D3DXVECTOR2(1.0f, 1.0f);
	int AnimCont = -1;
	float fHigth = 30.0f;

	D3DXVECTOR3 ControlBezier = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	int SecondTex = 1;
	int AnimPatternType = 0;
#endif
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (mode == CManager::MODE_2D)
			{
				if (bEffectState2D == true)
				{
					if (strcmp(&aFile[0], "PATTERN") == 0)	//�����̃p�^�[��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nPattern);
					}
					if (strcmp(&aFile[0], "POS") == 0)	//�o���ʒu
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
					}
					if (strcmp(&aFile[0], "MOVE") == 0)	//�ړ���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &move.x, &move.y, &move.z);
					}
					if (strcmp(&aFile[0], "ADDMOVE") == 0)	//�������Z
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &Addmove.x, &Addmove.y, &Addmove.z);
					}
					if (strcmp(&aFile[0], "DIFFUSION") == 0)	//�g�U��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &Diffusion);
					}
					if (strcmp(&aFile[0], "DESTROYVEC") == 0)	//������x�N�g��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &Destroyvec);
					}
					if (strcmp(&aFile[0], "SIZE") == 0)	//�傫��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &fSize);
					}
					if (strcmp(&aFile[0], "ADDSIZE") == 0)	//�傫�����Z
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &fAddSize);
					}
					if (strcmp(&aFile[0], "COLOR") == 0)	//�J���[
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f %f", &col.r, &col.g, &col.b, &col.a);
					}
					if (strcmp(&aFile[0], "ROTATE") == 0)	//��]
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &fRotate);
					}
					if (strcmp(&aFile[0], "CHANGECOLOR") == 0)	//�J���[�ϓ�
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f %f", &ChangeColor.r, &ChangeColor.g, &ChangeColor.b, &ChangeColor.a);
					}
					if (strcmp(&aFile[0], "LIFE") == 0)	//����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nLife);
					}
					if (strcmp(&aFile[0], "DENSITY") == 0)	//���x
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &Density);
					}
					if (strcmp(&aFile[0], "TEXTURE") == 0)	//�e�N�X�`��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nTexture);
					}
					if (strcmp(&aFile[0], "SYNTHETIC") == 0)	//�e�N�X�`��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nSynthetic);
					}
					if (strcmp(&aFile[0], "DISTANCE") == 0)	//�������n�_
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &fDistance);
					}

				}

				//�G�t�F�N�g���Z�b�g
				if (strcmp(&aFile[0], "EFFECTSTATE2D") == 0)
				{
					bEffectState2D = true;
				}
				if (strcmp(&aFile[0], "END_EFFECTSTATE2D") == 0)
				{
					bEffectState2D = false;

					if (CControl::GetPattern() != nPattern)
					{
						CControl::SetButten(nPattern);
					}

					//���ꂼ��̓K��
					CControl::SetPattern(nPattern);
					CControl::SetColor(col);
					CControl::SetChangeColor(ChangeColor);
					CControl::SetSize(fSize);
					CControl::SetChangeSize(fAddSize);
					CControl::SetLife(nLife);
					CControl::SetDensity(Density);
					CControl::SetAddRotate(fRotate);
					CControl::SetDiffusion(Diffusion);
					CControl::SetMove(D3DXVECTOR2(move.x, move.y));
					CControl::SetAddmove(D3DXVECTOR2(Addmove.x, Addmove.y));
					CControl::SetUninitVectl(Destroyvec);
					CControl::SetTexture(nTexture);
					CControl::SetSynthetic(nSynthetic);
					CControl::SetDistance(fDistance);

				}
			}
			else if (mode == CManager::MODE_3D)
			{

				if (bEffectState3D == true)
				{
					if (strcmp(&aFile[0], "PATTERN") == 0)	//�����̃p�^�[��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nPattern);
					}
					if (strcmp(&aFile[0], "COLOR") == 0)	//�J���[
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f %f", &col.r, &col.g, &col.b, &col.a);
					}
					if (strcmp(&aFile[0], "CHANGECOLOR") == 0)	//�J���[�ϓ�
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f %f", &ChangeColor.r, &ChangeColor.g, &ChangeColor.b, &ChangeColor.a);
					}
					if (strcmp(&aFile[0], "LIFE") == 0)	//����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nLife);
					}
					if (strcmp(&aFile[0], "TEXTURE") == 0)	//�e�N�X�`��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nTexture);
					}
					if (strcmp(&aFile[0], "SYNTHETIC") == 0)	//����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nSynthetic);
					}
					if (strcmp(&aFile[0], "DENSITY") == 0)	//���x
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &Density);
					}
					if (strcmp(&aFile[0], "TRAJECTTOP") == 0)	//�������f���P
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &TrajectTop);
					}
					if (strcmp(&aFile[0], "TRAJECTCUR") == 0)	//�������f���Q
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &TrajectCur);
					}
					if (strcmp(&aFile[0], "MOVE") == 0)	//�ړ���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &move.x, &move.y, &move.z);
					}
					if (strcmp(&aFile[0], "RANDMOVE") == 0)	//�ړ���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &RandMove);
					}
					if (strcmp(&aFile[0], "SIZE") == 0)	//���T�C�Y
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &fSize);
					}
					if (strcmp(&aFile[0], "ADDSIZE") == 0)	//�傫���ϓ�
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &fAddSize);
					}
					if (strcmp(&aFile[0], "PARTICLESIZE") == 0)	//���T�C�Y
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &ParticleSize);
					}
					if (strcmp(&aFile[0], "PARTICLETIME") == 0)	//�������Ԋu
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &ParticleTime);
					}
					if (strcmp(&aFile[0], "DISTANCE") == 0)	//�������n�_
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &fDistance);
					}
					if (strcmp(&aFile[0], "ACTIVE") == 0)	//�A�N�e�B�u����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nActive);
					}
					if (strcmp(&aFile[0], "PARTICLEADDSIZE") == 0)	//���傫���ύX
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &ParticleAddSize);
					}
					if (strcmp(&aFile[0], "MAXSIZE") == 0)	//�t�B�[���h�ő�T�C�Y
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &fMaxSize);
					}
					if (strcmp(&aFile[0], "ROTATE") == 0)	//��]
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &fRotate);
					}
					if (strcmp(&aFile[0], "SECONDCOLOR") == 0)	//�p�[�e�B�N���J���[
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f %f", &Particlecol.r, &Particlecol.g, &Particlecol.b, &Particlecol.a);
					}
					if (strcmp(&aFile[0], "SECONDADDCOLOR") == 0)	//�p�[�e�B�N���J���[
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f %f", &ParticleAddColor.r, &ParticleAddColor.g, &ParticleAddColor.b, &ParticleAddColor.a);
					}
					if (strcmp(&aFile[0], "SECONDSYNTHETIC") == 0)	//�p�[�e�B�N������
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParticleSynthetic);
					}
					if (strcmp(&aFile[0], "SECONDTIME") == 0)	//2�Ԗڂ̎���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nSecondTime);
					}
					if (strcmp(&aFile[0], "VTX") == 0)	//���_��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nVtx);
					}
					if (strcmp(&aFile[0], "TYPE") == 0)	//���_��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nType);
					}
					if (strcmp(&aFile[0], "TEXMOVE") == 0)	//�e�N�X�`���ړ���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f", &TexMove.x, &TexMove.y);
					}
					if (strcmp(&aFile[0], "TEXNUM") == 0)	//�e�N�X�`������
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f", &TexNum.x , &TexNum.y);
					}
					if (strcmp(&aFile[0], "SECONDTYPE") == 0)	//���_��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nSecondType);
					}
					if (strcmp(&aFile[0], "TEXSPLIT") == 0)	//�e�N�X�`���ړ���
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f", &TexSplit.x, &TexSplit.y);
					}
					if (strcmp(&aFile[0], "TEXANIMCOUNT") == 0)	//�e�N�X�`���J�E���g
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &AnimCont);
					}
					if (strcmp(&aFile[0], "HIGTH") == 0)	//����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &fHigth);
					}
					if (strcmp(&aFile[0], "THERDCOLOR") == 0)	//�p�[�e�B�N���J���[
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f %f", &Therdcol.r, &Therdcol.g, &Therdcol.b, &Therdcol.a);
					}
					if (strcmp(&aFile[0], "THERDADDCOLOR") == 0)	//�p�[�e�B�N���J���[
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f %f", &TherdAddColor.r, &TherdAddColor.g, &TherdAddColor.b, &TherdAddColor.a);
					}
					if (strcmp(&aFile[0], "SECONDTEX") == 0)	//�p�[�e�B�N���J���[
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &SecondTex);
					}
					if (strcmp(&aFile[0], "CONTROLBEZIER") == 0)	//�p�[�e�B�N���J���[
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &ControlBezier.x, &ControlBezier.y, &ControlBezier.z);
					}
					if (strcmp(&aFile[0], "ANIMPATTERNTYPE") == 0)	//�A�j���[�V�����p�^�[���^�C�v
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &AnimPatternType);
					}


				}

				//�G�t�F�N�g���Z�b�g
				if (strcmp(&aFile[0], "END_EFFECTSTATE3D") == 0)
				{
					bEffectState3D = false;
					if (CControl::GetPattern() != nPattern)
					{
						CControl::SetButten(nPattern);
					}

					CControl::SetPattern(nPattern);
					CControl::SetColor(col);
					CControl::SetChangeColor(ChangeColor);
					CControl::SetTrajectColor(Therdcol);
					CControl::SetTrajectChangeColor(TherdAddColor);
					CControl::SetLife(nLife);
					CControl::SetTrajectTop(TrajectTop);
					CControl::SetTrajectCur(TrajectCur);
					CControl::SetMove3D(move);
					CControl::SetSynthetic(nSynthetic);
					CControl::SetDensity(Density);
					CControl::SetRandMove(RandMove);
					CControl::SetSize(fSize);
					CControl::SetChangeSize(fAddSize);
					CControl::SetAddRotate(fRotate);
					CControl::SetParticleSize(ParticleSize);
					CControl::SetParticleTime(ParticleTime);
					CControl::SetDistance(fDistance);
					CControl::SetParticleAddSize(ParticleAddSize);
					CControl::SetMaxSize(fMaxSize);
					CControl::SetParticleColor(Particlecol);
					CControl::SetParticleAddCol(ParticleAddColor);
					CControl::SetParticleSynthetic(nParticleSynthetic);
					CControl::SetActive(nActive);
					CControl::SetSecondTime(nSecondTime);
					CControl::SetVtx(nVtx);
					CControl::SetType(nType);
					CControl::SetTexMoveUV(TexMove);
					CControl::SetTexNum(TexNum);
					CControl::SetSecondType(nSecondType);
					CControl::SetnAnimCont(AnimCont);
					CControl::SetnSplit(TexSplit);
					CControl::SetHigth(fHigth);
					CControl::SetSecondTex(SecondTex);
					CControl::SetControlBezier(ControlBezier);
					CControl::SetAnimPatternType(AnimPatternType);
				}
				if (strcmp(&aFile[0], "EFFECTSTATE3D") == 0)
				{
					bEffectState3D = true;
				}
			}

			//�I���
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
	}
	fclose(pFile);

}