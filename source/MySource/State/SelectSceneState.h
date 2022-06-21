////////////////////////////////////////////////////////////////////////////////////////////
// SlectSceneState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �Z���N�g��ʂ̃J�����̏�ԂɊւ��邱��
//
//-----------------------------------------------------------------------------------------
// 2020/12/13	�쐬
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
