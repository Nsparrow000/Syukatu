//=============================================================================
// �G�t�F�N�g�Z�b�g�I�u�W�F�N�g���� [SetObject.h]
// Author : �����G��
//=============================================================================

#include "Scene3D.h"

class CKeyboard;
class CMouse;

class CSetObject : public CScene3D
{
public:
	CSetObject();
	~CSetObject();

	HRESULT Init();
	void Uninit();
	void Update();
private:


};