//=======================================================================
// Fade.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/12/05	作成 FadeOut
//			10	SetFade実装
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Pol2D.h"

//--- 列挙体
namespace FADE
{
	enum STATUS
	{
		_NO,
		_OUT,
		_IN,

		MAX
	};
}

//--- クラス
class Fade
{
public:
	void Init();
	void Uninit();
	bool Update();
	void Draw();

	void FadeOut(int Time);
	void SetFade(float alpha);

	FADE::STATUS m_Status;

private:

	Pol2D m_Polygon;

	int m_nCount;
	int m_nTime;
};
