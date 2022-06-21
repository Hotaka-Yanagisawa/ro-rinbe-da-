#include "MoveState.h"
#include "EnemyPlayer.h"
#include"../Transform.h"
#include "../Object.h"

void MoveState::Init(EnemyPlayer *obj)
{
	//今はとりあえず原点に向けて移動
	obj->GetTransform()->Rotate = Float3(0, 0, 0);
	obj->GetTransform()->Move = Float3(0, 0, 0);
}

void MoveState::Update(EnemyPlayer *obj, HierarchyEnemyState * parent)
{
	//obj->GetTransform()->Position
	//乱数でオブジェクトごとに少し位置をずらす
	//float randNumX = (rand() % 100) - 50;
	//float randNumY = (rand() % 100) - 50;
	//プレイヤー座標の代わりとりあえず原点
	//プレイヤー座標が取得出来たら直す
	float sx = 0, sz = 0;
	//神殿に行くの計算
	float Rad = atan2f(sz - obj->GetTransform()->Position.z, sx - obj->GetTransform()->Position.x);
	
	//*5のところはプレイヤーのMove+1ぐらい？
	obj->GetTransform()->Move.x = cosf(Rad) * 0.1f;
	obj->GetTransform()->Move.y = 0.0f;
	obj->GetTransform()->Move.z = sinf(Rad) * 0.1f;

	obj->m_Parent->Get<Transform>()->Rotate = Float3(0, 90 * 3.14f / 180.0f - Rad, 0);

	//座標更新
	obj->GetTransform()->Position += obj->GetTransform()->Move;
}
