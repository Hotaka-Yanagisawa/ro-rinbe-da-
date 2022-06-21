//=======================================================================
// UI2D.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/28	作成
//		 12/10	ポーズ画面作成はじめ Updateの戻り値変更
//			
//=======================================================================
#pragma once

//--- インクルード
#include "PolygonList.h"
#include "Timer.h"
#include "MySound.h"

//--- 列挙体
namespace UISYS
{
	enum STATUS
	{
		NO,
		PAUSE,
		RETRY,
		EXIT,

		MAX
	};
}

//--- クラス
class UI2D
{
public:
	UI2D() {}
	~UI2D() {}

	void Init();
	void Uninit();

	UISYS::STATUS Update();
	void Draw();

	static int m_nResultHP;
	static bool m_bTmplHPFrag;

private:

	Pol2D m_BossHP;
	Pol2D m_BossGa;
	Pol2D m_TmplHP;
	Pol2D m_TmplGa;

	int m_nBasePos, m_nBaseSize;
	int m_nCount;
	int m_nSECnt;

	Pol2D m_Start;
	Pol2D m_Clear;
	Pol2D m_GOver;
	Pol2D m_Number;

	PolygonList m_Gage;

	bool m_bPause;
	bool m_bCntDown;

	std::string m_fileName[12];

	CSound m_Sound;
};
