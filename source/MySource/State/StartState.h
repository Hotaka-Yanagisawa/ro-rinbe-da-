////////////////////////////////////////////////////////////////////////////////////////////
// StartState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �Q�[���V�[���n�܂�̉��o��ԂɊւ��邱��
// 
//-----------------------------------------------------------------------------------------
// 2020/12/13	�쐬
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
