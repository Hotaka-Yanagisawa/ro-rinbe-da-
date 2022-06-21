//--- インクルード
#include "Vitality.h"
#include "Object.h"
#include "Shader.h"
#include "SceneManager.h"

//==================================================
// 初期化
//==================================================
void Vitality::Init()
{
	m_fMaxHp = m_fHp = 10;
}

//==================================================
// 描画
//==================================================
void Vitality::Draw()
{
	static int time;
	if ((m_fHp < 3) && (m_Parent->m_Tag == OBJECT::BOSS))
	{
		// エフェクト
		if (++time % 3 == 0)
			EFFECT.SetEffect(m_Parent->Get<Transform>()->Position, KIND::SMOKE);
	}
}

//==================================================
// HPの設定
//--------------------------------------------------
// 引数1	: 値
// 引数2	: false - fHPのみ、true - fMaxHPも
//			  デフォルトでtrue
//==================================================
void Vitality::SetHP(int HP, bool Recov)
{
	if (Recov) m_fMaxHp = m_fHp = HP;
	else m_fHp = HP;
}
