//=======================================================================
// Field.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/20	�쐬
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Component.h"
#include "Transform.h"

//--- �萔
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
