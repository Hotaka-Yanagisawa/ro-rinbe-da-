////////////////////////////////////////////////////////////////////////////////////////////
// GameState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// ゲームシーン中の状態に関すること
// 
//-----------------------------------------------------------------------------------------
//	2020/12/13	作成
//			25	プレイヤーの背後にカメラが移動―＞母船ロックオン機能に変更 (中村
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
