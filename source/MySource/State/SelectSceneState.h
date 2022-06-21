////////////////////////////////////////////////////////////////////////////////////////////
// SlectSceneState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// セレクト画面のカメラの状態に関すること
//
//-----------------------------------------------------------------------------------------
// 2020/12/13	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "CameraState.h"

class Camera;

class SelectSceneState :public CameraState
{
public:
	static SelectSceneState *GetInstance()
	{
		static SelectSceneState instance;
		return &instance;
	}

	void Init(Camera *);
	void Update(Camera *);
	void ChangeState(Camera *, CameraState *);
};
