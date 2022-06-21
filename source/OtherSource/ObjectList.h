//=======================================================================
// ObjectList.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/15	�N���X�쐬
//			16	Add, Update, Draw��Object����R�s�[
//				Add�̎d�l��ύX �� Create
//			17	OBJECT::TYPE�ǉ�
//			18	FIELD�Ƃ��ǉ��������Ǖʂ̂Ƃ���ɏ��������@/21 �ڂ���
//			22	Destroy����
//			28	�����シ�����X�g�ɒǉ����Ȃ��p�^�[������
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Object.h"
#include <list>

//--- �N���X
class ObjectList
{
public:

	ObjectList() {}
	~ObjectList() { m_List.clear(); }

	void Update();
	void Draw();

	// ����
	Object* Create(OBJECT::TYPE, bool Push = true);
	void Add(Object*);

	// �擾
	Object* Get(OBJECT::TYPE);

	// ����
	void Destroy(Object* pObj);

	// ���X�g
	std::list<Object*> m_List;

private:

};
