//=============================================================================
// �V�[���̃��[�h���� [load.h]
// Author : �����G��
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

#include "main.h"


class CLoad
{
public:
	CLoad();
	~CLoad();
	static void Load(const char *aModelName);
	static void Load2D(const char *aModelName);	//�{�^���̓ǂݍ���

private:
};

#endif