//=======================================================================
// Component.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/15	�쐬 Init, Update, Draw
//			18	OnCollision����
//			23	OnCollision�̈����ŏՓˑ���̎���
//				OnCollisionEnter�쐬
//			24	Remove�p�ϐ�, Uninit�ǉ�
//
//=======================================================================
#pragma once

//--- �O���錾
class Object;

//--- �N���X
class Component		// �R���|�[�l���g���N���X
{
public:

	Component() {}
	virtual ~Component() {}

	virtual void Init() {}
	virtual void Uninit() {}

	virtual void Update() {}
	virtual void Draw() {}

	virtual void OnCollision(Object* pObj) {}
	virtual void OnCollisionEnter(Object* pObj) {}

	Object* m_Parent = nullptr;

	bool m_bRemove = false;
private:

};
