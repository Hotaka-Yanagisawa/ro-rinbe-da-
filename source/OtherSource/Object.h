//=======================================================================
// Object.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/15	�N���X�쐬 �R���|�[�l���g����
//			20	�f�t�H���g��Transform�����悤�ɐݒ�
//			23	�R���|�[�l���g���O�����ǉ�
//			24	���̕s��C��			
//
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Component.h"
#include "Transform.h"
#include <list>

//--- �萔
namespace OBJECT
{
	enum TYPE	// ���
	{
		NO = -1,
		PLAYER,	// ��l��
		ENEMY1,	// �G��
		ENEMY2,	// �G��
		ENEMY3,	// �G��
		TREE,	// ��
		ROCK,	// ��
		BTREE,	// ���̖�
		BOSS,	// ���
		FIELD,	// �n��
		//--- �_�a
		TEMPLE,	// �{��
		PILLAR,	// ��
		CORE,	// �R�A
		FLOOR1,	// ����
		FLOOR2,	// ����
		FLOOR3,	// ����
		BACK,	// �w�i

		MAX
	};
}

//--- �N���X
class Object
{
public:
	Object() { this->Add<Transform>(); }
	~Object() { m_List.clear(); }

	// �X�V
	void Update()
	{
		// �폜
		for (auto it = m_List.begin(); it != m_List.end(); )
		{
			if ((*it)->m_bRemove)
			{
				(*it)->Uninit();
				delete *it;
				it = m_List.erase(it);
				continue;
			}
			it++;
		}
		// �X�V
		for (auto i : m_List) i->Update();
	}
	// �`��
	void Draw() { for (auto i : m_List) i->Draw(); }
	// �Փˎ�
	void OnCollision(Object* pObj) { for (auto i : m_List) i->OnCollision(pObj); }
	void OnCollisionEnter(Object* pObj) { for (auto i : m_List) i->OnCollisionEnter(pObj); }

	// �ǉ�
	template<class T>
	T* Add()
	{
		T* com = new T();
		com->m_Parent = this;
		m_List.push_back(com);
		com->Init();
		return com;
	}

	// �擾
	template<class T>
	T* Get()
	{
		for (auto i : m_List)
		{
			T* com = dynamic_cast<T*>(i);
			if (com != nullptr) return com;
		}
		return nullptr;
	}

	// �폜
	//void Remove(Component* com)
	//{
	//	com->m_bRemove = true;
	//}

	// ���X�g
	std::list<Component*> m_List;		// �X�V�Ώ�

	// �^�O
	OBJECT::TYPE m_Tag = OBJECT::NO;

	// �������Ă�
	bool m_bHit = false;
	// ���O�Ώ�
	bool m_bRemove = false;

private:

};
