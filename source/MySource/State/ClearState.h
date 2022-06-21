////////////////////////////////////////////////////////////////////////////////////////////
// ClearState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �N���A���o��ԂɊւ��邱��
// 
//-----------------------------------------------------------------------------------------
// 2020/12/16	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "CameraState.h"

class Camera;

class ClearState :public CameraState
{
public:
	static ClearState *GetInstance()
	{
		static ClearState instance;
		return &instance;
	}

	void Init(Camera *);
	void Update(Camera *);
	void ChangeState(Camera *, CameraState *);

	//enum Phase
	//{
	//	UFO,
	//	ENEMY,
	//	TEMPLE,
	//	PLAYER,
	//	CNT_DOWN,
	//	END,
	//};

	//Phase m_Phase;
private:
	int m_nCnt;
	//std::queue<Phase> m_PhaseQueue;
};
