//*****************************************************************************
// エフェクトの諸々設定(control.h)
// Author : 佐藤秀亮
//*****************************************************************************
#ifndef _CONTROL_H_
#define _CONTROL_H_
#include "main.h"
#include "manager.h"
//=============================================================================
//マクロ
//=============================================================================
//前方宣言
class CKeyboard;

class CControl
{
public:
	CControl();		//コンストラクタ
	~CControl();	//デストラクタ

	static HRESULT Init();
	static void Update();

	static void Control();
	static void Control2D();
	static void Control3D();

	static int GetControlCoror(int nSerectcolor);	//色取得

	static int GetChangeCol(int nSerectcolor);	//増減値取得
	static void SetControlCoror(int nSerectcolor);	//色セット

	static bool GetRandCol(int nSerectcolor);	//色ランダム化取得

	static void AddColor(int Color, int nSerect);
	static void AddChangeCol(int Color, int nSerect);

	static int GetSerectColor() { return m_SerectColor; }	//色選択番号
	
	static float GetSize() { return m_ControlSize; }	//サイズ
	static float GetChangeSize() { return m_ControlChangeSize; }	//サイズ増減


	static int GetLife() { return m_nLife; }			//寿命
	static int GetTex() { return m_nTex; }				//テクスチャ
	static int GetDensity() { return m_nDensity; }		//密度
	static bool GetTap() { return m_bTap; }	//タップON or OFF
	static int GetPattern() { return m_nPattern; }		//パターン

	static bool GetRandMoveX() { return m_RandMoveX; }	//ランダムXON or OFF
	static bool GetRandMoveY() { return m_RandMoveY; }	//ランダムYON or OFF

	static void SetColorRandom(int nSerectcol , bool bAdaptation);	//カラーランダムON or OFF

	//2D
	static D3DXVECTOR2 GetMove() { return m_move; }		//初期の動き値
	static bool GetMouseCursor() { return m_bMouseCursor; }	//カーソル追従ON or OFF
	//固有
	static D3DXVECTOR2 GetAddMove() { return m_Addmove; }		//移動加算
	static int GetDiffusion() { return m_Diffusion; }
	static int GetUninitVectl() { return m_nUninitVectl; }		//消えるベクトル

	//3D
	static bool GetPlayerMode() { return m_bPlayerMode; }
	static void SetPlayerMode(bool bMode) {m_bPlayerMode = bMode; }
	static int GetModelNum() { return m_ModelNum; }
	static D3DXVECTOR3 Getmove3d() { return m_move3d; }		//移動
	static int GetTrajectModelNum() { return m_ModelTrajecNum; }
	static int GetRandMove1() { return m_nRandMove1; }

	//固有
	static void TrajectColor(int Color, int nSerect);
	static int GetTrajectColor(int nSerectcolor);	//色取得

	static void AddTrajectCol(int Color, int nSerect);
	static int GetTrajectCol(int nSerectcolor);	//色取得

	//テキストセーブ
	static void SaveEffect(CManager::MODE mode, int nPattern);

private:
	static CKeyboard *m_pKeyboard;
	static int m_SerectColor;		//色選択
	static bool m_bTap;	//タップで出すかどうか
	static D3DCOLORVALUE m_ControlColor;		//色変更
	static D3DCOLORVALUE m_ControlChangeCol;	//増減値
	static float m_ControlSize;			//サイズ
	static float m_ControlChangeSize;		//サイズ増減
	static int m_nLife;	//寿命
	static int m_nTex;	//テクスチャ選択
	static int m_nDensity;	//密度
	static int m_nPattern;	//パターン

	static bool m_RandMoveX;	//ランダムX ON OFF
	static bool m_RandMoveY;	//ランダムY ON OFF

	static bool m_ColorR;	//カラーランダム ON OFF
	static bool m_ColorG;	//カラーランダム ON OFF
	static bool m_ColorB;	//カラーランダム ON OFF

	//２D
	static bool m_bMouseCursor;			//カーソル追従
	static D3DXVECTOR2 m_move;	//初期の移動値
	//固有
	static D3DXVECTOR2 m_Addmove;	//移動加算
	static int m_Diffusion;		//ランダム拡散率
	static int m_nUninitVectl;	//消える直線距離
	//3D
	static bool m_bPlayerMode;	//プレイヤー操作かどうか
	static int m_ModelNum;	//軌跡手元
	static D3DXVECTOR3 m_move3d;	//移動加算
	static int m_nRandMove1;	//ランダムの最大・最小移動量

	//メッシュくん
	static int m_ModelTrajecNum;	//軌跡先端
	static D3DCOLORVALUE m_TrajectColor;		//色変更
	static D3DCOLORVALUE m_TrajectChangeCol;	//色変更

};

#endif