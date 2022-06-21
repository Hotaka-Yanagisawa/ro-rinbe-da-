//--- �C���N���[�h
#include "Rigidbody.h"
#include "Object.h"

//==================================================
// ������
//==================================================
void Rigidbody::Init()
{
	m_fMass = 1.0f;
	m_fDrag = 0.0f;
	m_bGravity = true;

	m_Transform = m_Parent->Get<Transform>();
}

//==================================================
// �X�V
//==================================================
void Rigidbody::Update()
{
	// �d��
	if (m_bGravity)
	{
		m_Transform->Move.y -= 0.06f;
		m_Transform->Position.y += m_Transform->Move.y;
	}

	// �n��(���E����)
	if (m_Transform->Position.y < m_Transform->Size.y / 2) m_Transform->Position.y = m_Transform->Size.y / 2;

}
