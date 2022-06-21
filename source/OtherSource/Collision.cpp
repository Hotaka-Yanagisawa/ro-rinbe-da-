//--- �C���N���[�h��
#include "Collision.h"
#include "Object.h"
#include "Transform.h"

//==================================================
// ������
//==================================================
void Collision::Init()
{
}

//==================================================
// �I��
//==================================================
void Collision::Uninit()
{
	m_List.clear();
}

//==================================================
// �X�V
//==================================================
void Collision::Update()
{
	// ���X�g����
	for (auto Self = m_List.begin(); Self != m_List.end(); )
	{
		for (auto Target : m_List)
		{
			// ����
			if ((*Self) == Target) continue;
			// �ΏۊO
			bool isTarget = false;
			for (int i : (*Self)->m_TargetList)
			{
				if (Target->m_Parent->m_Tag == i)
				{
					isTarget = true;
					break;
				}
			}
			if (!isTarget) continue;

			// ����
			if (CheckCollision((*Self)->m_Parent, Target->m_Parent))
			{
				(*Self)->m_Parent->m_bHit =
				Target->m_Parent->m_bHit = true;
			}
			else
			{
				(*Self)->m_Parent->m_bHit =
				Target->m_Parent->m_bHit = false;
			}
		}

		// ���X�g����O���Ď���
		Self = m_List.erase(Self);
	}

	// ���X�g��������
	m_List.clear();
}

//==================================================
// �o�^
//--------------------------------------------------
// ����		: �o�^����R���C�_
//==================================================
void Collision::Add(Collider *pCollider)
{
	m_List.push_back(pCollider);
}

//==================================================
// �����蔻��
//--------------------------------------------------
// ����1	: ������Ƃ�I�u�W�F�N�g
// ����2	: �Ώۂ̃I�u�W�F�N�g
// �߂�l	: �������Ă� true
//==================================================
bool Collision::CheckCollision(Object* &pSelf, Object* &pTarget)
{
	// �{�b�N�X
	const Float3 aPos = pSelf->Get<Transform>()->Position;
	const Float3 bPos = pTarget->Get<Transform>()->Position;
	Float3 distance = Float3(bPos - aPos).abs();
	const Float3 aSize = pSelf->Get<Transform>()->Size * 2;
	const Float3 bSize = pTarget->Get<Transform>()->Size * 2;
	if (!(distance.x < (aSize.x + bSize.x) * 0.5f)) return false;
	if (!(distance.y < (aSize.y + bSize.y) * 0.5f)) return false;
	if (!(distance.z < (aSize.z + bSize.z) * 0.5f)) return false;
	//--- �������Ă�
	// ���߂�
	if (!pSelf->m_bHit)
	{
		pSelf->m_bHit = true;
		pSelf->OnCollisionEnter(pTarget);
	}
	if (!pTarget->m_bHit)
	{
		pTarget->m_bHit = true;
		pTarget->OnCollisionEnter(pSelf);
	}
	pSelf->OnCollision(pTarget);
	pTarget->OnCollision(pSelf);

	return true;
}
