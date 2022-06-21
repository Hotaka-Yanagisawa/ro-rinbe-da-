//=======================================================================
// Timer.h
//-----------------------------------------------------------------------
// �쐬�� : ���c���
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/29	�쐬
//		 12/01	Pol2D.h�𗘗p���ĕ`��
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Pol2D.h"

//--- �N���X
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
