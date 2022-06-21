//=======================================================================
// Field.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/20	作成
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Component.h"
#include "Transform.h"

//--- 定数
#define FIELD_RANGE	(255.0f)

class Field : public Component
{
public:
	Field() {}
	~Field() {}

	void Update() override;
	void Draw() override;

private:
	Transform* m_Transform;

};
