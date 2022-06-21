//--- インクルード
#include "Rigidbody.h"
#include "Object.h"

//==================================================
// 初期化
//==================================================
void Rigidbody::Init()
{
	m_fMass = 1.0f;
	m_fDrag = 0.0f;
	m_bGravity = true;

	m_Transform = m_Parent->Get<Transform>();
}

//==================================================
// 更新
//==================================================
void Rigidbody::Update()
{
	// 重力
	if (m_bGravity)
	{
		m_Transform->Move.y -= 0.06f;
		m_Transform->Position.y += m_Transform->Move.y;
	}

	// 地面(境界判定)
	if (m_Transform->Position.y < m_Transform->Size.y / 2) m_Transform->Position.y = m_Transform->Size.y / 2;

}
