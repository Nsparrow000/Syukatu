//*****************************************************************************
// エフェクトの諸々設定(control.cpp)
// Author : 佐藤秀亮
//*****************************************************************************
#include "manager.h"
#include "control.h"
#include "keyboard.h"

#include "seteffect.h"
#include <assert.h>

//マクロ定義
#define MAX_SERECT_COLOR (5)	//最大選択色
#define MAX_COLOR (255)			//最大色値

#define MAX_CHANGECOL (10)		//最大増減色値
#define MAX_SIZE (30.0f)		//最大サイズ

#define MAX_LIFE (300)			//最大寿命
#define MAX_TEX (2)				//最大テクスチャ

#define MAX_DENSITY (10)		//最大密度
#define RAND_COLOR (float(rand()% 255) + 5)	//ランダムカラー

#define MAX_PATTERN (4)	//最大パターン
#define MAX_MOVE (200)	//動きの最大値

#define SAVE_TEXT "data/SaveText.txt"	//セーブするテキストファイル

//静的メンバ変数宣言
CKeyboard *CControl::m_pKeyboard = NULL;
bool CControl::m_bMouseCursor = false;
bool CControl::m_bTap = false;
D3DCOLORVALUE CControl::m_ControlColor = {};
int CControl::m_SerectColor = 1;
D3DCOLORVALUE CControl::m_ControlChangeCol = {};

float CControl::m_ControlSize = 0;
float CControl::m_ControlChangeSize = 0;
int CControl::m_nLife = 0;
int CControl::m_nTex = 0;

int CControl::m_nDensity = 0;
int CControl::m_nPattern = 1;
int CControl::m_nRandMove1 = 1;

int CControl::m_ModelNum = 0;
int CControl::m_Diffusion = 1;
int CControl::m_ModelTrajecNum = 0;

int CControl::m_nUninitVectl = 300;

D3DXVECTOR2 CControl::m_move = {};
D3DXVECTOR2 CControl::m_Addmove = {};

bool CControl::m_RandMoveX = false;
bool CControl::m_RandMoveY = false;

bool CControl::m_ColorR = false;
bool CControl::m_ColorG = false;
bool CControl::m_ColorB = false;

bool CControl::m_bPlayerMode = false;

D3DXVECTOR3 CControl::m_move3d = {};

D3DCOLORVALUE CControl::m_TrajectColor = {};
D3DCOLORVALUE CControl::m_TrajectChangeCol = {};

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CControl::CControl()
{
	m_bMouseCursor = false;
}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CControl::~CControl()
{

}

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CControl::Init()
{
	m_pKeyboard = CManager::GetKeyboard();
	m_SerectColor = 1;

	m_ControlColor.r = MAX_COLOR;
	m_ControlColor.g = MAX_COLOR;
	m_ControlColor.b = MAX_COLOR;
	m_ControlColor.a = MAX_COLOR;

	m_ControlChangeCol.r = 0;
	m_ControlChangeCol.g = 0;
	m_ControlChangeCol.b = 0;
	m_ControlChangeCol.a = 0;

	m_TrajectColor.r = MAX_COLOR;
	m_TrajectColor.g = MAX_COLOR;
	m_TrajectColor.b = MAX_COLOR;
	m_TrajectColor.a = MAX_COLOR;

	m_TrajectChangeCol.r = 0;
	m_TrajectChangeCol.g = 0;
	m_TrajectChangeCol.b = 0;
	m_TrajectChangeCol.a = 0;

	m_ControlSize = 20;
	m_ControlChangeSize = 0;
	m_nLife = 100;
	m_nTex = 1;
	m_nDensity = 1;
	m_nPattern = 1;

	m_move = D3DXVECTOR2(0.0f, 0.0f);
	m_Addmove = D3DXVECTOR2(0.0f, 0.0f);

	m_ColorR = false;
	m_ColorG = false;
	m_ColorB = false;

	m_bMouseCursor = false;
	m_bTap = false;

	m_bPlayerMode = false;

	return S_OK;
}

//*****************************************************************************
//更新
//*****************************************************************************
void CControl::Update()
{
	CManager::MODE mode = CManager::GetMode();

	if (m_pKeyboard != NULL)
	{
		//タップON　OFF
		if (m_pKeyboard->GetKey(DIK_F5) == true)
		{
			if (m_bPlayerMode == false)
			{
				m_bPlayerMode = true;
			}
			else if (m_bPlayerMode == true)
			{
				m_bPlayerMode = false;
			}
		}
	}

	if (mode == CManager::MODE_2D)
	{
		Control();
	}
	else if (mode == CManager::MODE_3D)
	{
		if (m_bPlayerMode == false)
		{
			Control();
		}
	}
}

//*****************************************************************************
//操作
//*****************************************************************************
void CControl::Control()
{
	CManager::MODE mode = CManager::GetMode();

	if (m_pKeyboard != NULL)
	{
		//タップON　OFF
		if (m_pKeyboard->GetKey(DIK_N) == true)
		{
			if (m_bTap == false)
			{
				m_bTap = true;
			}
			else if (m_bTap == true)
			{
				m_bTap = false;
			}
		}

		//選択カラー変更
		if (m_pKeyboard->GetKey(DIK_LEFT) == true)
		{
			m_SerectColor--;
			if (m_SerectColor <= 0)
			{
				m_SerectColor = MAX_SERECT_COLOR - 1;
			}
		}
		else if (m_pKeyboard->GetKey(DIK_RIGHT) == true)
		{
			m_SerectColor++;
			if (m_SerectColor >= MAX_SERECT_COLOR)
			{
				m_SerectColor = 1;
			}
		}

		//カラーランダムON　OFF
		if (m_pKeyboard->GetKey(DIK_1) == true)
		{
			if (GetRandCol(m_SerectColor) == false)
			{
				SetColorRandom(m_SerectColor, true);
			}
			else if (GetRandCol(m_SerectColor) == true)
			{
				SetColorRandom(m_SerectColor, false);
				SetControlCoror(m_SerectColor);
			}
		}

		//選択エフェクトタイプ変更
		if (m_pKeyboard->GetKey(DIK_UP) == true)
		{
			m_nPattern++;
			if (m_nPattern >= MAX_PATTERN)
			{
				m_nPattern = MAX_PATTERN - 1;
			}
		}
		else if (m_pKeyboard->GetKey(DIK_DOWN) == true)
		{
			m_nPattern--;
			if (m_nPattern <= 0)
			{
				m_nPattern = 1;
			}
		}

		//初期色の変更
		if (m_pKeyboard->GetPress(DIK_Q) == true)
		{
			CControl::AddColor(1, m_SerectColor);
		}
		else if (m_pKeyboard->GetPress(DIK_A) == true)
		{
			CControl::AddColor(-1, m_SerectColor);
		}

		//増減色の変更
		if (m_pKeyboard->GetKey(DIK_W) == true)
		{
			CControl::AddChangeCol(1, m_SerectColor);
		}
		else if (m_pKeyboard->GetKey(DIK_S) == true)
		{
			CControl::AddChangeCol(-1, m_SerectColor);
		}

		//初期サイズの変更
		if (m_pKeyboard->GetKey(DIK_E) == true)
		{
			m_ControlSize++;
			if (m_ControlSize >= MAX_SIZE)
			{
				m_ControlSize = MAX_SIZE;
			}
		}
		else if (m_pKeyboard->GetKey(DIK_D) == true)
		{
			m_ControlSize--;
			if (m_ControlSize <= 0)
			{
				m_ControlSize = 0;
			}

		}

		//サイズ増減の変更
		if (m_pKeyboard->GetKey(DIK_R) == true)
		{
			m_ControlChangeSize += 0.1f;
			if (m_ControlChangeSize >= 1.0f)
			{
				m_ControlChangeSize = 1.0f;
			}

		}
		else if (m_pKeyboard->GetKey(DIK_F) == true)
		{
			m_ControlChangeSize -= 0.1f;
			if (m_ControlChangeSize <= -1.0f)
			{
				m_ControlChangeSize = -1.0f;
			}

		}

		//寿命の変更
		if (m_pKeyboard->GetPress(DIK_T) == true)
		{
			m_nLife++;
			if (m_nLife >= MAX_LIFE)
			{
				m_nLife = MAX_LIFE;
			}

		}
		else if (m_pKeyboard->GetPress(DIK_G) == true)
		{
			m_nLife--;
			if (m_nLife <= 0)
			{
				m_nLife = 0;
			}
		}

		if (CManager::GetMode() == CManager::MODE_3D && m_nPattern != 3)
		{
			//テクスチャ
			if (m_pKeyboard->GetKey(DIK_Z) == true)
			{
				m_nTex++;
				if (m_nTex > MAX_TEX)
				{
					m_nTex = MAX_TEX;
				}

			}
			else if (m_pKeyboard->GetKey(DIK_X) == true)
			{
				m_nTex--;
				if (m_nTex <= 1)
				{
					m_nTex = 1;
				}
			}
		}

		//密度
		if (m_pKeyboard->GetKey(DIK_C) == true)
		{
			m_nDensity++;
			if (m_nDensity > MAX_DENSITY)
			{
				m_nDensity = MAX_DENSITY;
			}

		}
		else if (m_pKeyboard->GetKey(DIK_V) == true)
		{
			m_nDensity--;
			if (m_nDensity <= 1)
			{
				m_nDensity = 1;
			}
		}
	}
	if (m_ColorR == true)
	{
		m_ControlColor.r = RAND_COLOR;
	}
	if (m_ColorG == true)
	{
		m_ControlColor.g = RAND_COLOR;
	}
	if (m_ColorB == true)
	{
		m_ControlColor.b = RAND_COLOR;
	}
	if (mode == CManager::MODE_2D)
	{
		CControl::Control2D();
	}
	else if (mode == CManager::MODE_3D)
	{
		CControl::Control3D();
	}
}
//*****************************************************************************
//2D専用操作
//*****************************************************************************
void CControl::Control2D()
{
	if (m_pKeyboard != NULL)
	{
		//カーソル追従ON　OFF
		if (m_pKeyboard->GetKey(DIK_M) == true)
		{
			if (m_bMouseCursor == false)
			{
				m_bMouseCursor = true;
			}
			else if (m_bMouseCursor == true)
			{
				m_bMouseCursor = false;
			}
		}

		//移動値ランダムON　OFF
		if (m_pKeyboard->GetKey(DIK_6) == true)
		{
			if (m_RandMoveX == false)
			{
				m_RandMoveX = true;
			}
			else if (m_RandMoveX == true)
			{
				m_RandMoveX = false;
				m_move.x = 0;
			}
		}

		//移動値ランダムON　OFF
		if (m_pKeyboard->GetKey(DIK_7) == true)
		{
			if (m_RandMoveY == false)
			{
				m_RandMoveY = true;
			}
			else if (m_RandMoveY == true)
			{
				m_RandMoveY = false;
				m_move.y = 0;
			}
		}

		//移動値X
		if (m_RandMoveX == false)
		{
			if (m_pKeyboard->GetKey(DIK_Y) == true)
			{
				m_move.x++;
			}
			else if (m_pKeyboard->GetKey(DIK_H) == true)
			{
				m_move.x--;
			}
		}
		//移動値Y
		if (m_RandMoveY == false)
		{
			if (m_pKeyboard->GetKey(DIK_U) == true)
			{
				m_move.y++;
			}
			else if (m_pKeyboard->GetKey(DIK_J) == true)
			{
				m_move.y--;
			}
		}

		//各パターン固有の値変動
		switch (m_nPattern)
		{
		case(1):
			//移動加算値X
			if (m_pKeyboard->GetKey(DIK_I) == true)
			{
				m_Addmove.x += 0.1f;
			}
			else if (m_pKeyboard->GetKey(DIK_K) == true)
			{
				m_Addmove.x -= 0.1f;
			}

			//移動加算値Y
			if (m_pKeyboard->GetKey(DIK_O) == true)
			{
				m_Addmove.y += 0.1f;
			}
			else if (m_pKeyboard->GetKey(DIK_L) == true)
			{
				m_Addmove.y -= 0.1f;
			}

			break;
		case(2):
			//ランダム拡散率
			if (m_pKeyboard->GetPress(DIK_I) == true)
			{
				m_Diffusion += 1;
				if (m_Diffusion >= 334)
				{
					m_Diffusion = 334;
				}
			}
			else if (m_pKeyboard->GetPress(DIK_K) == true)
			{
				m_Diffusion -= 1;
				if (m_Diffusion <= 0)
				{
					m_Diffusion = 1;
				}
			}

			//消えるベクトル
			if (m_pKeyboard->GetPress(DIK_U) == true)
			{
				m_nUninitVectl += 1;
				if (m_nUninitVectl >= 1000)
				{
					m_nUninitVectl = 1000;
				}
			}
			else if (m_pKeyboard->GetPress(DIK_J) == true)
			{
				m_nUninitVectl -= 1;
				if (m_nUninitVectl <= 0)
				{
					m_nUninitVectl = 1;
				}
			}

			break;
		case(3):
			break;
		default:
			assert(false);
			break;
		}

		if (m_pKeyboard->GetKey(DIK_F9) == true)
		{
			SaveEffect(CManager::MODE_2D, m_nPattern);
		}

	}
}

//*****************************************************************************
//3D専用操作
//*****************************************************************************
void CControl::Control3D()
{
	if (m_pKeyboard != NULL)
	{
		if (m_nPattern == 1)
		{
			//軌跡先端の出すモデル変更
			if (m_pKeyboard->GetKey(DIK_X) == true)
			{
				m_ModelTrajecNum++;
				if (m_ModelTrajecNum > 14)
				{
					m_ModelTrajecNum = 0;
				}
			}
			//軌跡先端の出すモデル変更
			if (m_pKeyboard->GetKey(DIK_Z) == true)
			{
				m_ModelNum++;
				if (m_ModelNum > 14)
				{
					m_ModelNum = 0;
				}
			}

			//メッシュ色の変更
			if (m_pKeyboard->GetPress(DIK_C) == true)
			{
				CControl::TrajectColor(1, m_SerectColor);
			}
			else if (m_pKeyboard->GetPress(DIK_V) == true)
			{
				CControl::TrajectColor(-1, m_SerectColor);
			}

			//メッシュ増減色の変更
			if (m_pKeyboard->GetKey(DIK_B) == true)
			{
				CControl::AddTrajectCol(1, m_SerectColor);
			}
			else if (m_pKeyboard->GetKey(DIK_N) == true)
			{
				CControl::AddTrajectCol(-1, m_SerectColor);
			}
		}
		else if (m_nPattern == 2)
		{
			//移動変更X
			if (m_pKeyboard->GetKey(DIK_U) == true)
			{
				m_move3d.x += 0.5f;
			}
			else if (m_pKeyboard->GetKey(DIK_J) == true)
			{
				m_move3d.x -= 0.5f;
			}
			//移動変更Y
			if (m_pKeyboard->GetKey(DIK_I) == true)
			{
				m_move3d.y += 0.5f;
			}
			else if (m_pKeyboard->GetKey(DIK_K) == true)
			{
				m_move3d.y -= 0.5f;
			}
			//移動変更Z
			if (m_pKeyboard->GetKey(DIK_O) == true)
			{
				m_move3d.z += 0.5f;
			}
			else if (m_pKeyboard->GetKey(DIK_L) == true)
			{
				m_move3d.z -= 0.5f;
			}

		}
		else if (m_nPattern == 3)
		{
			//パーティクルの比較先
			if (m_pKeyboard->GetKey(DIK_X) == true)
			{
				m_ModelTrajecNum++;
				if (m_ModelTrajecNum > 14)
				{
					m_ModelTrajecNum = 0;
				}
			}
			//パーティクルが出るモデル
			if (m_pKeyboard->GetKey(DIK_Z) == true)
			{
				m_ModelNum++;
				if (m_ModelNum > 14)
				{
					m_ModelNum = 0;
				}
			}

			//パーティクルが動く最大・最小
			if (m_pKeyboard->GetPress(DIK_Y) == true)
			{
				m_nRandMove1++;
				if (m_nRandMove1 > MAX_MOVE)
				{
					m_nRandMove1 = MAX_MOVE;
				}
			}
			else if (m_pKeyboard->GetPress(DIK_H) == true)
			{
				m_nRandMove1--;
				if (m_nRandMove1 <= 0)
				{
					m_nRandMove1 = 1;
				}
			}
		}

		//セーブ
		if (m_pKeyboard->GetKey(DIK_F9) == true)
		{
			SaveEffect(CManager::MODE_3D, m_nPattern);
		}
	}

}

//*****************************************************************************
//セーブ
//*****************************************************************************
void CControl::SaveEffect(CManager::MODE mode, int nPattern)
{
	FILE *pFile = fopen(SAVE_TEXT, "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "#========================================================================\n");
		fprintf(pFile, "#エフェクトの情報をこのテキストファイルに書き出します\n");
		fprintf(pFile, "#読み込むテキストファイルにコピペするなりしてご自由に\n");
		fprintf(pFile, "#========================================================================\n\n\n");

		fprintf(pFile, "#========================================================================\n");
		fprintf(pFile, "#エフェクトパターン ()番目\n");
		fprintf(pFile, "#メモ：(このエフェクトの使い道等、書いてください)\n");
		fprintf(pFile, "#========================================================================\n");


		if (mode == CManager::MODE_2D)
		{
			fprintf(pFile, "EFFECTSTATE2D\n");
			fprintf(pFile, "	PATTERN = %d				//動きのパターン\n", nPattern);


			fprintf(pFile, "	POS = %.1f %.1f				//座標\n", CSetEffect::GetSetPos().x, CSetEffect::GetSetPos().y);

			switch (nPattern)
			{
			case(1):
				fprintf(pFile, "	MOVE = %.1f %.1f					//動き\n", m_move.x, m_move.y);
				fprintf(pFile, "	ADDMOVE = %.1f %.1f				//動き加算値\n", m_Addmove.x, m_Addmove.y);
				break;
			case(2):
				fprintf(pFile, "	MOVE = %.1f					//スピード\n", m_move.x);
				fprintf(pFile, "	DIFFUSION = %d					//拡散率\n", m_Diffusion);
				fprintf(pFile, "	DESTROYVEC = %d					//消えるベクトル\n", m_nUninitVectl);
				break;
			default:
				assert(false);
				break;
			}
			fprintf(pFile, "	SIZE = %.1f						//大きさ\n", m_ControlSize);
			fprintf(pFile, "	ADDSIZE = %.1f					//大きさ変動\n", m_ControlChangeSize);
			fprintf(pFile, "	COLOR = %d %d %d %d			//カラー\n", (int)m_ControlColor.r, (int)m_ControlColor.g, (int)m_ControlColor.b, (int)m_ControlColor.a);
			fprintf(pFile, "	CHANGECOLOR = %d %d %d %d			//カラー変動値\n", (int)m_ControlChangeCol.r, (int)m_ControlChangeCol.g, (int)m_ControlChangeCol.b, (int)m_ControlChangeCol.a);
			fprintf(pFile, "	LIFE = %d						//ライフ\n", m_nLife);
			fprintf(pFile, "	DENSITY = %d						//密度\n", m_nDensity);

			fprintf(pFile, "	COLORRANDR = %d						//カラーランダム赤 1だと有効\n", m_ColorR);
			fprintf(pFile, "	COLORRANDG = %d						//カラーランダム緑 1だと有効\n", m_ColorG);
			fprintf(pFile, "	COLORRANDB = %d						//カラーランダム青 1だと有効\n", m_ColorB);

			fprintf(pFile, "	MOVERANDX = %d						//移動ランダムX 1だと有効\n", m_RandMoveX);

			if (m_nPattern != 2)
			{
				fprintf(pFile, "	MOVERANDY = %d						//移動ランダムY 1だと有効\n", m_RandMoveY);
			}

			fprintf(pFile, "	MOUSEPOS = %d						//マウス追従ON 1だと有効\n", m_bMouseCursor);


			fprintf(pFile, "END_EFFECTSTATE2D\n\n");
		}
		else if (mode == CManager::MODE_3D)	//3Dモード
		{
			fprintf(pFile, "EFFECTSTATE3D\n");

			fprintf(pFile, "	COLOR = %d %d %d %d			//カラー\n", (int)m_ControlColor.r, (int)m_ControlColor.g, (int)m_ControlColor.b, (int)m_ControlColor.a);
			fprintf(pFile, "	CHANGECOLOR = %d %d %d %d			//カラー変動値\n", (int)m_ControlChangeCol.r, (int)m_ControlChangeCol.g, (int)m_ControlChangeCol.b, (int)m_ControlChangeCol.a);
			fprintf(pFile, "	LIFE = %d						//寿命\n", m_nLife);

			switch (nPattern)
			{
			case(1):
				fprintf(pFile, "	TRAJECTCOLOR = %d %d %d %d			//先端カラー\n", (int)m_TrajectColor.r, (int)m_TrajectColor.g, (int)m_TrajectColor.b, (int)m_TrajectColor.a);
				fprintf(pFile, "	TRAJECTCHANGECOLOR = %d %d %d %d			//先端カラー変動値\n", (int)m_TrajectChangeCol.r, (int)m_TrajectChangeCol.g, (int)m_TrajectChangeCol.b, (int)m_TrajectChangeCol.a);

				fprintf(pFile, "	MODEL = %d						//軌跡手元モデル\n", m_ModelNum);
				fprintf(pFile, "	TRAJECTMODEL = %d				//軌跡先端モデル\n", m_ModelTrajecNum);
				break;
			case(2):
				fprintf(pFile, "	SIZE = %.1f						//大きさ\n", m_ControlSize);
				fprintf(pFile, "	ADDSIZE = %.1f					//大きさ変動\n", m_ControlChangeSize);

				fprintf(pFile, "	COLORRANDR = %d						//カラーランダム赤1だと有効\n", m_ColorR);
				fprintf(pFile, "	COLORRANDG = %d						//カラーランダム緑1だと有効\n", m_ColorG);
				fprintf(pFile, "	COLORRANDB = %d						//カラーランダム青1だと有効\n", m_ColorB);
				break;
			case(3):
				fprintf(pFile, "	SIZE = %.1f						//大きさ\n", m_ControlSize);
				fprintf(pFile, "	ADDSIZE = %.1f					//大きさ変動\n", m_ControlChangeSize);

				fprintf(pFile, "	DENSITY = %d						//発生量\n", m_nDensity);
				fprintf(pFile, "	RANDMOVE = %d					//動きの幅\n", m_nRandMove1);

				fprintf(pFile, "	SPAWNMODEL = %d						//発生モデル\n", m_ModelNum);
				fprintf(pFile, "	COMPARISONMODEL = %d				//比較モデル\n", m_ModelTrajecNum);

				break;
			default:
				assert(false);
				break;
			}

			fprintf(pFile, "END_EFFECTSTATE3D\n\n");
		}
		fclose(pFile);
	}

}

//*****************************************************************************
//選択色の取得
//*****************************************************************************
int CControl::GetControlCoror(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		return (int)m_ControlColor.r;
		break;
	case(2):
		return (int)m_ControlColor.g;
		break;
	case(3):
		return (int)m_ControlColor.b;
		break;
	case(4):
		return (int)m_ControlColor.a;
		break;
	default:
		return 0;		//例外処理(処理不可能）
		break;
	}
}

//*****************************************************************************
//選択色がランダムかどうか
//*****************************************************************************
bool CControl::GetRandCol(int nSerectcolor)	//色ランダム化取得
{
	switch (nSerectcolor)
	{
	case(1):
		return m_ColorR;
		break;
	case(2):
		return m_ColorG;
		break;
	case(3):
		return m_ColorB;
		break;
	case(4):
		return false;
		break;
	default:
		return false;		//例外処理(処理不可能）
		break;
	}
}

//*****************************************************************************
//選択色ランダム化
//*****************************************************************************
void CControl::SetColorRandom(int nSerect, bool bAdaptation)
{
	switch (nSerect)
	{
	case(1):
		m_ColorR = bAdaptation;
		break;
	case(2):
		m_ColorG = bAdaptation;
		break;
	case(3):
		m_ColorB = bAdaptation;
		break;
	case(4):
		return;
		break;
	default:
		assert(false);
		break;
	}
}

//*****************************************************************************
//増減値取得
//*****************************************************************************
int CControl::GetChangeCol(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		return (int)m_ControlChangeCol.r;
		break;
	case(2):
		return (int)m_ControlChangeCol.g;
		break;
	case(3):
		return (int)m_ControlChangeCol.b;
		break;
	case(4):
		return (int)m_ControlChangeCol.a;
		break;
	default:
		return 0;		//例外処理
		break;
	}
}

//*****************************************************************************
//選択色の変更
//*****************************************************************************
void CControl::AddColor(int nColor, int nSerect)
{
	switch (nSerect)
	{
	case(1):
		m_ControlColor.r += nColor;
		if (m_ControlColor.r > MAX_COLOR)
		{
			m_ControlColor.r = MAX_COLOR;
		}
		else if (m_ControlColor.r < 0)
		{
			m_ControlColor.r = 0;
		}
		break;
	case(2):
		m_ControlColor.g += nColor;
		if (m_ControlColor.g > MAX_COLOR)
		{
			m_ControlColor.g = MAX_COLOR;
		}
		else if (m_ControlColor.g < 0)
		{
			m_ControlColor.g = 0;
		}
		break;
	case(3):
		m_ControlColor.b += nColor;
		if (m_ControlColor.b > MAX_COLOR)
		{
			m_ControlColor.b = MAX_COLOR;
		}
		else if (m_ControlColor.b < 0)
		{
			m_ControlColor.b = 0;
		}
		break;
	case(4):
		m_ControlColor.a += nColor;
		if (m_ControlColor.a > MAX_COLOR)
		{
			m_ControlColor.a= MAX_COLOR;
		}
		else if (m_ControlColor.a < 0)
		{
			m_ControlColor.a = 0;
		}
		break;
	default:
		assert(false);		//例外処理
		break;
	}
}

//*****************************************************************************
//増減値の変更
//*****************************************************************************
void CControl::AddChangeCol(int nColor, int nSerect)
{
	switch (nSerect)
	{
	case(1):
		m_ControlChangeCol.r += nColor;
		if (m_ControlChangeCol.r > MAX_CHANGECOL)
		{
			m_ControlChangeCol.r = MAX_CHANGECOL;
		}
		else if (m_ControlChangeCol.r < -MAX_CHANGECOL)
		{
			m_ControlChangeCol.r = -MAX_CHANGECOL;
		}
		break;
	case(2):
		m_ControlChangeCol.g += nColor;
		if (m_ControlChangeCol.g > MAX_CHANGECOL)
		{
			m_ControlChangeCol.g = MAX_CHANGECOL;
		}
		else if (m_ControlChangeCol.g < -MAX_CHANGECOL)
		{
			m_ControlChangeCol.g = -MAX_CHANGECOL;
		}
		break;
	case(3):
		m_ControlChangeCol.b += nColor;
		if (m_ControlChangeCol.b > MAX_CHANGECOL)
		{
			m_ControlChangeCol.b = MAX_CHANGECOL;
		}
		else if (m_ControlChangeCol.b < -MAX_CHANGECOL)
		{
			m_ControlChangeCol.b = -MAX_CHANGECOL;
		}
		break;
	case(4):
		m_ControlChangeCol.a += nColor;
		if (m_ControlChangeCol.a > MAX_CHANGECOL)
		{
			m_ControlChangeCol.a = MAX_CHANGECOL;
		}
		else if (m_ControlChangeCol.a < -MAX_CHANGECOL)
		{
			m_ControlChangeCol.a = -MAX_CHANGECOL;
		}
		break;
	default:
		assert(false);		//例外処理
		break;
	}
}

//*****************************************************************************
//選択色のリセット
//*****************************************************************************
void CControl::SetControlCoror(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		m_ControlColor.r = 255;
		break;
	case(2):
		m_ControlColor.g = 255;
		break;
	case(3):
		m_ControlColor.b = 255;
		break;
	case(4):
		m_ControlColor.a;
		break;
	default:
		return ;
		break;
	}
}

//*****************************************************************************
//メッシュ初期色の変更
//*****************************************************************************
void CControl::TrajectColor(int nColor, int nSerect)
{
	switch (nSerect)
	{
	case(1):
		m_TrajectColor.r += nColor;
		if (m_TrajectColor.r > MAX_COLOR)
		{
			m_TrajectColor.r = MAX_COLOR;
		}
		else if (m_TrajectColor.r < 0)
		{
			m_TrajectColor.r = 0;
		}
		break;
	case(2):
		m_TrajectColor.g += nColor;
		if (m_TrajectColor.g > MAX_COLOR)
		{
			m_TrajectColor.g = MAX_COLOR;
		}
		else if (m_TrajectColor.g < 0)
		{
			m_TrajectColor.g = 0;
		}
		break;
	case(3):
		m_TrajectColor.b += nColor;
		if (m_TrajectColor.b > MAX_COLOR)
		{
			m_TrajectColor.b = MAX_COLOR;
		}
		else if (m_TrajectColor.b < 0)
		{
			m_TrajectColor.b = 0;
		}
		break;
	case(4):
		m_TrajectColor.a += nColor;
		if (m_TrajectColor.a > MAX_COLOR)
		{
			m_TrajectColor.a = MAX_COLOR;
		}
		else if (m_TrajectColor.a < 0)
		{
			m_TrajectColor.a = 0;
		}
		break;
	default:
		assert(false);		//例外処理
		break;
	}
}

//*****************************************************************************
//メッシュ初期色の取得
//*****************************************************************************
int CControl::GetTrajectColor(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		return (int)m_TrajectColor.r;
		break;
	case(2):
		return (int)m_TrajectColor.g;
		break;
	case(3):
		return (int)m_TrajectColor.b;
		break;
	case(4):
		return (int)m_TrajectColor.a;
		break;
	default:
		return 0;		//例外処理(処理不可能）
		break;
	}
}

//*****************************************************************************
//メッシュ増減色の変更
//*****************************************************************************
void CControl::AddTrajectCol(int nColor, int nSerect)
{
	switch (nSerect)
	{
	case(1):
		m_TrajectChangeCol.r += nColor;
		if (m_TrajectChangeCol.r > MAX_CHANGECOL)
		{
			m_TrajectChangeCol.r = MAX_CHANGECOL;
		}
		else if (m_TrajectChangeCol.r < -MAX_CHANGECOL)
		{
			m_TrajectChangeCol.r = -MAX_CHANGECOL;
		}
		break;
	case(2):
		m_TrajectChangeCol.g += nColor;
		if (m_TrajectChangeCol.g > MAX_CHANGECOL)
		{
			m_TrajectChangeCol.g = MAX_CHANGECOL;
		}
		else if (m_TrajectChangeCol.g < -MAX_CHANGECOL)
		{
			m_TrajectChangeCol.g = -MAX_CHANGECOL;
		}
		break;
	case(3):
		m_TrajectChangeCol.b += nColor;
		if (m_TrajectChangeCol.b > MAX_CHANGECOL)
		{
			m_TrajectChangeCol.b = MAX_CHANGECOL;
		}
		else if (m_TrajectChangeCol.b < -MAX_CHANGECOL)
		{
			m_TrajectChangeCol.b = -MAX_CHANGECOL;
		}
		break;
	case(4):
		m_TrajectChangeCol.a += nColor;
		if (m_TrajectChangeCol.a > MAX_CHANGECOL)
		{
			m_TrajectChangeCol.a = MAX_CHANGECOL;
		}
		else if (m_TrajectChangeCol.a < -MAX_CHANGECOL)
		{
			m_TrajectChangeCol.a = -MAX_CHANGECOL;
		}
		break;
	default:
		assert(false);		//例外処理(処理不可能）
		break;
	}
}

//*****************************************************************************
//メッシュ増減色の取得
//*****************************************************************************
int CControl::GetTrajectCol(int nSerectcolor)
{
	switch (nSerectcolor)
	{
	case(1):
		return (int)m_TrajectChangeCol.r;
		break;
	case(2):
		return (int)m_TrajectChangeCol.g;
		break;
	case(3):
		return (int)m_TrajectChangeCol.b;
		break;
	case(4):
		return (int)m_TrajectChangeCol.a;
		break;
	default:
		return 0;		//例外処理(処理不可能）
		break;
	}
}
