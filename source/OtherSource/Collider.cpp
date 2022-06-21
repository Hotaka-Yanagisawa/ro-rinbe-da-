//--- インクルード
#include "Collider.h"
#include "Object.h"
#include "Collision.h"

//==================================================
// 初期化
//==================================================
void Collider::Init()
{
#ifdef _DEBUG
	m_Cube.m_Transform = m_Parent->Get<Transform>();
	m_Cube.Init();
#endif
}

//==================================================
// 終了
//==================================================
void Collider::Uninit()
{
}

//==================================================
// 更新
//==================================================
void Collider::Update()
{
	Collision::GetInstance()->Add(this);
}

//==================================================
// 描画
//==================================================
void Collider::Draw()
{
#ifdef _DEBUG
	// 判定枠の描画
	//m_Cube.Draw(true);
#endif
}

//==================================================
// 判定をとる対象追加
//--------------------------------------------------
// 引数		: ObjectTag
// 戻り値	: なし
//==================================================
void Collider::AddTarget(int Tag)
{
	m_TargetList.push_back(Tag);
}

//==================================================
// 判定をとる対象除外
//--------------------------------------------------
// 引数		: ObjectTag
// 戻り値	: なし
//==================================================
void Collider::RemoveTarget(int Tag)
{
	m_TargetList.remove(Tag);
}
