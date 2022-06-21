//=======================================================================
// Rigidbody.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/18	作成 空実装
//			19	Unity参考に実装
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Component.h"
#include "Transform.h"

class Rigidbody : public Component
{
public:

	Rigidbody() {}
	~Rigidbody() {}

	void Init() override;

	void Update() override;

private:
	Transform* m_Transform;

	float m_fMass;
	float m_fDrag;

	bool m_bGravity;

};
