//=======================================================================
// Timer.h
//-----------------------------------------------------------------------
// 作成者 : 藤田拓也
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/29	作成
//		 12/01	Pol2D.hを利用して描画
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Pol2D.h"

//--- クラス
class Timer 
{
	Timer() {}
	~Timer() {}
public:
	static Timer *GetInstance()
	{
		static Timer instance;
		return &instance;
	}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTime(int count, int alert = 0);
	int GetTime();
private:

	Pol2D m_Timer;
	Pol2D m_Number[3];

	int m_nCount;
	int m_nAlert;
};
