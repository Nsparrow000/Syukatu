//*****************************************************************************
// ���ԃZ�[�u�݂����Ȃ�(IntermediateSave.h)
// Author : �����G��
//*****************************************************************************
#ifndef _INTERMEIATESAVE_H_
#define _INTERMEIATESAVE_H_

#include "main.h"
#include "manager.h"

class CIntermeiateSave
{
	CIntermeiateSave();
	~CIntermeiateSave();
public:
	//�Z�[�u
	static void IntermeiateSave(CManager::MODE mode, int nPattern, const char *aModelName);
	//���[�h
	static void IntermeiateLoad(CManager::MODE mode, const char *aModelName);
private:
};
#endif // !_INTERMEIATESAVE_H_
