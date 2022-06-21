#include "ReturnState.h"
#include "EnemyPlayer.h"
#include"../Transform.h"
#include "../Object.h"

void ReturnState::Init(EnemyPlayer *obj)
{
	obj->GetTransform()->Rotate = Float3(0, 0, 0);
	obj->GetTransform()->Move = Float3(0, 0, 0);
}

void ReturnState::Update(EnemyPlayer *obj, HierarchyEnemyState *parent)
{
	//敵が帰る地点まで戻る処理を行う
	float sx = 0, sz = 0;
	//神殿に行くの計算
	float Rad = atan2f(sz - obj->GetTransform()->Position.z, sx - obj->GetTransform()->Position.x);


	//*5のところはプレイヤーのMove+1ぐらい？
	obj->GetTransform()->Move.x = cosf(Rad) * 0.3f;
	obj->GetTransform()->Move.y = 0.0f;
	obj->GetTransform()->Move.z = sinf(Rad) * 0.3f;

	obj->m_Parent->Get<Transform>()->Rotate = Float3(0, 270 * 3.14f / 180.0f - Rad, 0);

	//座標更新
	obj->GetTransform()->Position -= obj->GetTransform()->Move;
}
