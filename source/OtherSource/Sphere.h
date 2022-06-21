//=======================================================================
// Sphere.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/21	描画だけ実装
//			26	UV反転できるように
//	2021/01/09	深度クリップオフ
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Object.h"
#include "DrawBuffer.h"

class Sphere : public Component
{
public:
	Sphere() {}
	~Sphere() {}

	void Init() override;

	void Draw() override;

private:
	Transform* m_Transform;

	DrawBuffer m_Buffer;

	ID3D11ShaderResourceView* m_pTexture;
};
