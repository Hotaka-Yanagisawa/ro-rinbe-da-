//=======================================================================
// Rigidbody.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/18	�쐬 �����
//			19	Unity�Q�l�Ɏ���
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
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
