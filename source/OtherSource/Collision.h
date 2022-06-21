//=======================================================================
// Collision.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/12	���Ɠ��̂���������
//			19	�v���C���[��̂Ȕ���̎��� ��
//			23	�߂���
//			27	����ς�߂��� (�����蔻��Ǘ��N���X)
//			
//=======================================================================
#pragma once

//--- �C���N���[�h��
#include "Object.h"
#include "Collider.h"

class Collision
{
public:

	inline static Collision* GetInstance()
	{
		static Collision instance;
		return &instance;
	}

	void Init();
	void Uninit();

	void Update();

	void Add(Collider*);

private:

	bool CheckCollision(Object*&, Object*&);

	std::list<Collider*> m_List;
};
