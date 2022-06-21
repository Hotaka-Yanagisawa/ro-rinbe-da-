////////////////////////////////////////////////////////////////////////////////////////////
// GameOverState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// ゲームオーバー演出状態に関すること
// 
//-----------------------------------------------------------------------------------------
// 2020/12/16	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "CameraState.h"


class Camera;

class GameOverState :public CameraState
{
public:
	static GameOverState *GetInstance()
	{
		static GameOverState instance;
		return &instance;
	}

	void Init(Camera *);
	void Update(Camera *);
	void ChangeState(Camera *, CameraState *);


private:
	int m_nCnt;
};
