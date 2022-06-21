//=======================================================================
// Collider.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/12	���Ƃ̂��
//			19	Collision��static�ŏ���
//			22	����Ώۂ����X�g�ɂ���
//			23	����`��p�L���[�u����
//			24	Uninit�Ń��X�g����O���悤�ɂ���
//			27	Collision�ɃR���|�[�l���g��n�������ɂ���
//
//=======================================================================
#pragma once

//--- �C���N���[�h��
#include "Component.h"
#include "Cube.h"

//--- �N���X
class Collider : public Component
{
public:

	Collider() {}
	~Collider() {}

	void Init() override;
	void Uninit() override;

	void Update() override;
	void Draw() override;

	void AddTarget(int Tag);
	void RemoveTarget(int Tag);

	std::list<int> m_TargetList;

private:
	Cube m_Cube;

};
