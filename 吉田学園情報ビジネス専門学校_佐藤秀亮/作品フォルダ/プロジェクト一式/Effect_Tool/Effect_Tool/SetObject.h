//=============================================================================
// エフェクトセットオブジェクト処理 [SetObject.h]
// Author : 佐藤秀亮
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