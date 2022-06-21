//=======================================================================
// Light.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/01/02	Cameraをコピーして作成	
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Transform.h"

//--- マクロ
#define LIGHT	(Light::GetInstance())

//--- クラス
class Light
{
public:
	inline static Light* GetInstance()
	{
		static Light instance;
		return &instance;
	}

	void Init();
	void Uninit() {}

	void Update();

	DirectX::XMMATRIX GetView();

private:
	DirectX::XMMATRIX m_ViewMatrix;

	Float3 m_Position;

	Light() {}
	~Light() {}
};
