#include "AbsorbState.h"
#include "../GameScene.h"
#include "EnemyPlayer.h"
#include "ReturnState.h"
#include "../SceneManager.h"
#include "../UI2D.h"

void AbsorbState::Init(EnemyPlayer *obj)
{
	TempleVitality = GameScene::GetObjectList()->Get(OBJECT::TEMPLE)->Get<Vitality>();
}

void AbsorbState::Update(EnemyPlayer *obj, HierarchyEnemyState * parent)
{
	//ƒGƒlƒ‹ƒM[‹zŽû‚Ìˆ—
	if (obj->GetAbsorbTotal() < obj->GetAbsorbMax())
	{
		UI2D::m_bTmplHPFrag = true;

		TempleVitality->m_fHp -= obj->GetAbsorbSpd();
		obj->SubtractAbsorbTotal(obj->GetAbsorbSpd());

		static int time;
		if (++time % 20 == 0) EFFECT.SetEffect(obj->GetTransform()->Position, ABSORB);

	}
	else
	{
		parent->ChangeState(obj, ReturnState::GetInstance());
	}
}
