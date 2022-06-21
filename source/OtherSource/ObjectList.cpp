//--- �C���N���[�h
#include "ObjectList.h"
#include "Transform.h"
#include "Control.h"
#include "Sphere.h"
#include "Model.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Fly.h"
#include "State/EnemyPlayer.h"
#include "Vitality.h"
#include "Field.h"
#include "SelectScene.h"

//==================================================
// �X�V
//==================================================
void ObjectList::Update()
{
	// �폜
	for (auto it = m_List.begin(); it != m_List.end(); )
	{
		if ((*it)->m_bRemove)
		{
			delete *it;
			it = m_List.erase(it);
			continue;
		}
		it++;
	}

	//�X�V
	for (auto i : m_List) i->Update();
}

//==================================================
// �`��
//==================================================
void ObjectList::Draw()
{
	for (auto i : m_List) i->Draw();
}

//==================================================
// �I�u�W�F�N�g����
//--------------------------------------------------
// ����		: �I�u�W�F�N�g�̎��
//==================================================
Object* ObjectList::Create(OBJECT::TYPE Type, bool Push)
{
	Object* pObj = new Object;

	pObj->m_Tag = Type;

	// �R���|�[�l���g����������
	switch (Type)
	{
	case OBJECT::PLAYER:
	{
		pObj->Add<Model>()->LoadModel();
		pObj->Add<Control>();
		pObj->Add<Collider>();

		pObj->Get<Transform>()->Position.z = -200.0f;
		pObj->Get<Transform>()->Position.y = 6.0f;
		pObj->Get<Transform>()->Size = 8;
		pObj->Get<Collider>()->AddTarget(OBJECT::ENEMY1);
		pObj->Get<Collider>()->AddTarget(OBJECT::ENEMY2);
		pObj->Get<Collider>()->AddTarget(OBJECT::ENEMY3);
		pObj->Get<Collider>()->AddTarget(OBJECT::TREE);

		break;
	}
	case OBJECT::ENEMY1:
	case OBJECT::ENEMY2:
	case OBJECT::ENEMY3:
	{
		pObj->Add<Model>()->LoadModel();
		pObj->Add<Rigidbody>();
		pObj->Add<EnemyPlayer>();
		pObj->Add<Collider>();

		float r = rand() % 150 + FIELD_RANGE;
		float Angle = rand() * (3.141529f * 180.0f);
		pObj->Get<Transform>()->Position = { cosf(Angle) * r, 0, sinf(Angle) * r };
		pObj->Get<Transform>()->Size = 4.0f;
		pObj->Get<Collider>()->AddTarget(OBJECT::BOSS);
		pObj->Get<Collider>()->AddTarget(OBJECT::TEMPLE);

		break;
	}
	case OBJECT::BOSS:
	{
		pObj->Add<Model>()->LoadModel();
		switch (SelectScene::m_nSelect)
		{
		case 0:
			pObj->Add<Vitality>()->SetHP(50);
			break;
		case 1:
			pObj->Add<Vitality>()->SetHP(60);
			break;
		case 2:
			pObj->Add<Vitality>()->SetHP(80);
			break;
		}

		pObj->Add<Fly>();
		pObj->Add<Collider>();
		pObj->Get<Transform>()->Position = { 0, 100, 0 };
		pObj->Get<Transform>()->Size = 30;
		pObj->Get<Collider>()->AddTarget(OBJECT::ENEMY1);
		pObj->Get<Collider>()->AddTarget(OBJECT::ENEMY2);
		pObj->Get<Collider>()->AddTarget(OBJECT::ENEMY3);
		pObj->Get<Collider>()->AddTarget(OBJECT::TREE);
		break;
	}
	case OBJECT::TREE:
	{
		pObj->Add<Model>()->LoadModel();
		pObj->Add<Rigidbody>();
		pObj->Add<EnemyPlayer>();
		pObj->Add<Collider>();

		float Angle = rand() * 1.0f;
		float circle = pow(60.0f / 250.0f, 2.0f);
		float random = ((rand() / 32767.0f) * (1.0f - circle)) + circle;// , 2.0f);
		float r = sqrtf(random) * 250.0f;
		pObj->Get<Transform>()->Size = 6.0f;
		pObj->Get<Transform>()->Position = { cosf(Angle) * r, pObj->Get<Transform>()->Size.y * 0.5f, sinf(Angle) * r };
		break;
	}
	case OBJECT::BTREE:
	{
		pObj->Add<Model>()->LoadModel();
		pObj->Add<Rigidbody>();

		float r = rand() % 150 + FIELD_RANGE;
		float Angle = rand() * (3.141529f * 180.0f);
		pObj->Get<Transform>()->Size = float(rand() % 5 + 8);
		pObj->Get<Transform>()->Position = { cosf(Angle) * r, pObj->Get<Transform>()->Size.y * 0.5f, sinf(Angle) * r };
		break;
	}
	case OBJECT::ROCK:
	{
		pObj->Add<Model>()->LoadModel();
		pObj->Add<Rigidbody>();
		pObj->Add<EnemyPlayer>();
		pObj->Add<Collider>();

		pObj->Get<Transform>()->Position = { float(rand() % 400 - 200), 0, float(rand() % 400 - 200) };
		pObj->Get<Transform>()->Size = 6.0f;
		break;
	}
	case OBJECT::FIELD:
	{
		pObj->Add<Model>()->LoadModel();
		pObj->Add<Field>();

		pObj->Get<Transform>()->Position = { 0, -1, 0 };
		pObj->Get<Transform>()->Size = { 600, 0.1f, 600 };
		break;
	}
	case OBJECT::TEMPLE:
	{
		pObj->Add<Model>()->LoadModel();
		pObj->Add<Vitality>()->SetHP(30);
		pObj->Add<Collider>();

		Transform* temp = pObj->Get<Transform>();
		temp->Position = { 0, 38, 0 };
		temp->Size = 40;
		pObj->Get<Collider>()->AddTarget(OBJECT::ENEMY1);
		pObj->Get<Collider>()->AddTarget(OBJECT::ENEMY2);
		pObj->Get<Collider>()->AddTarget(OBJECT::ENEMY3);
		break;
	}
	case OBJECT::PILLAR:
	{
		pObj->Add<Model>()->LoadModel();
		pObj->Add<Vitality>()->SetHP(5);
		pObj->Add<Collider>();

		Transform* temp = pObj->Get<Transform>();
		temp->Position = 0;
		temp->Size = 40;
		break;
	}
	case OBJECT::CORE:
	{
		pObj->Add<Model>()->LoadModel();
		Transform* temp = pObj->Get<Transform>();
		temp->Position = { 0, 20, 0 };
		temp->Size = 20.0f;
		break;
	}
	case OBJECT::FLOOR1:
	{
		pObj->Add<Model>()->LoadModel();
		Transform* temp = pObj->Get<Transform>();
		temp->Position.y = 1.0f;
		temp->Size = 30.0f;
		break;
	}
	case OBJECT::FLOOR2:
	{
		pObj->Add<Model>()->LoadModel();
		Transform* temp = pObj->Get<Transform>();
		temp->Position.y = 0.5f;
		temp->Size = 30.0f;
		break;
	}
	case OBJECT::FLOOR3:
	{
		pObj->Add<Model>()->LoadModel();
		Transform* temp = pObj->Get<Transform>();
		temp->Position.y = -1.0f;
		temp->Size = 30.0f;
		break;
	}
	case OBJECT::BACK:
	{
		pObj->Add<Sphere>();

		pObj->Get<Transform>()->Size = 400;
		break;
	}
	default:
		break;
	}

	if (Push) m_List.push_back(pObj);

	return pObj;
}

//==================================================
// ���X�g�ɒǉ�
//--------------------------------------------------
// ����		: �I�u�W�F�N�g�̃|�C���^
//==================================================
void ObjectList::Add(Object *pObj)
{
	m_List.push_back(pObj);
}

//==================================================
// �I�u�W�F�N�g�擾
//--------------------------------------------------
// ����		: �I�u�W�F�N�g�̎��
//==================================================
Object* ObjectList::Get(OBJECT::TYPE Type)
{
	for (auto i : m_List)
		if (i->m_Tag == Type) return i;

	return nullptr;
}

//==================================================
// �I�u�W�F�N�g����
//--------------------------------------------------
// ����		: �I�u�W�F�N�g�̃|�C���^
//==================================================
void ObjectList::Destroy(Object* pObj)
{
	pObj->m_bRemove = true;
}
