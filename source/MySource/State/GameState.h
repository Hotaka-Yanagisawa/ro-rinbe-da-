////////////////////////////////////////////////////////////////////////////////////////////
// GameState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �Q�[���V�[�����̏�ԂɊւ��邱��
// 
//-----------------------------------------------------------------------------------------
//	2020/12/13	�쐬
//			25	�v���C���[�̔w��ɃJ�������ړ��\����D���b�N�I���@�\�ɕύX (����
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "CameraState.h"
#include "../Pol2D.h"

class Camera;
//class Pol2D;

class GameState :public CameraState
{
public:
	static GameState *GetInstance()
	{
		static GameState instance;
		return &instance;
	}

	void Init(Camera *);
	//void Uninit();
	void Update(Camera *);
	//void Draw();
	void ChangeState(Camera *, CameraState *);

	bool m_bTracking;
private:
	
};
