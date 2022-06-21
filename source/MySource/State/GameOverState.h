////////////////////////////////////////////////////////////////////////////////////////////
// GameOverState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �Q�[���I�[�o�[���o��ԂɊւ��邱��
// 
//-----------------------------------------------------------------------------------------
// 2020/12/16	�쐬
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
