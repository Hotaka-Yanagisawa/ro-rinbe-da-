////////////////////////////////////////////////////////////////////////////////////////////
// CameraState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 状態に関することの抽象クラス
//-----------------------------------------------------------------------------------------
// 2020/12/13	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

class Camera;

class CameraState
{
public:
	virtual ~CameraState() {}
	virtual void Init(Camera *) = 0;
	virtual void Update(Camera *) = 0;
	virtual void ChangeState(Camera *,CameraState *) = 0;
};