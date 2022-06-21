////////////////////////////////////////////////////////////////////////////////////////////
// StartState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// ゲームシーン始まりの演出状態に関すること
// 
//-----------------------------------------------------------------------------------------
// 2020/12/13	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "CameraState.h"
#include <queue>

class Camera;

class StartState :public CameraState
{
public:
	static StartState *GetInstance()
	{
		static StartState instance;
		return &instance;
	}

	void Init(Camera *);
	void Update(Camera *);
	void ChangeState(Camera *, CameraState *);

	enum Phase
	{
		UFO,
		ENEMY,
		TEMPLE,
		PLAYER,
		CNT_DOWN,
		END,
	};

	Phase m_Phase;
private:
	int m_PhaseCnt;
	std::queue<Phase> m_PhaseQueue;
};
