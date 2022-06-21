//--- インクルード部
#include "Collision.h"
#include "Object.h"
#include "Transform.h"

//==================================================
// 初期化
//==================================================
void Collision::Init()
{
}

//==================================================
// 終了
//==================================================
void Collision::Uninit()
{
	m_List.clear();
}

//==================================================
// 更新
//==================================================
void Collision::Update()
{
	// リストを回す
	for (auto Self = m_List.begin(); Self != m_List.end(); )
	{
		for (auto Target : m_List)
		{
			// 自分
			if ((*Self) == Target) continue;
			// 対象外
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

			// 判定
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

		// リストから外して次へ
		Self = m_List.erase(Self);
	}

	// リストを初期化
	m_List.clear();
}

//==================================================
// 登録
//--------------------------------------------------
// 引数		: 登録するコライダ
//==================================================
void Collision::Add(Collider *pCollider)
{
	m_List.push_back(pCollider);
}

//==================================================
// 当たり判定
//--------------------------------------------------
// 引数1	: 判定をとるオブジェクト
// 引数2	: 対象のオブジェクト
// 戻り値	: 当たってる true
//==================================================
bool Collision::CheckCollision(Object* &pSelf, Object* &pTarget)
{
	// ボックス
	const Float3 aPos = pSelf->Get<Transform>()->Position;
	const Float3 bPos = pTarget->Get<Transform>()->Position;
	Float3 distance = Float3(bPos - aPos).abs();
	const Float3 aSize = pSelf->Get<Transform>()->Size * 2;
	const Float3 bSize = pTarget->Get<Transform>()->Size * 2;
	if (!(distance.x < (aSize.x + bSize.x) * 0.5f)) return false;
	if (!(distance.y < (aSize.y + bSize.y) * 0.5f)) return false;
	if (!(distance.z < (aSize.z + bSize.z) * 0.5f)) return false;
	//--- 当たってる
	// 初めて
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
