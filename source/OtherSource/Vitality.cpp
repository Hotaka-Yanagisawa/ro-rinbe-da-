//--- �C���N���[�h
#include "Vitality.h"
#include "Object.h"
#include "Shader.h"
#include "SceneManager.h"

//==================================================
// ������
//==================================================
void Vitality::Init()
{
	m_fMaxHp = m_fHp = 10;
}

//==================================================
// �`��
//==================================================
void Vitality::Draw()
{
	static int time;
	if ((m_fHp < 3) && (m_Parent->m_Tag == OBJECT::BOSS))
	{
		// �G�t�F�N�g
		if (++time % 3 == 0)
			EFFECT.SetEffect(m_Parent->Get<Transform>()->Position, KIND::SMOKE);
	}
}

//==================================================
// HP�̐ݒ�
//--------------------------------------------------
// ����1	: �l
// ����2	: false - fHP�̂݁Atrue - fMaxHP��
//			  �f�t�H���g��true
//==================================================
void Vitality::SetHP(int HP, bool Recov)
{
	if (Recov) m_fMaxHp = m_fHp = HP;
	else m_fHp = HP;
}
