//=======================================================================
// Vitality.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/24	�쐬
//			26	�r���{�[�h�`��
//
//=======================================================================
#pragma once

//--- �C���N���[�h��
#include "Component.h"
#include "Transform.h"

//--- �N���X
class Vitality : public Component
{
public:

	Vitality() {}
	~Vitality() {}

	void Init() override;

	void Draw() override;

	float m_fMaxHp;
	float m_fHp;

	Transform m_Transform;

	void SetHP(int, bool = true);

private:

};
