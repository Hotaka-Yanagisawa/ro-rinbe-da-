#include "HoistingState.h"
#include "EnemyPlayer.h"
#include "SucksState.h"
#include "WindState.h"
#include "FireState.h"

void HoistingState::Init(EnemyPlayer *obj)
{
	ChangeState(obj, SucksState::GetInstance());
}

void HoistingState::Update(EnemyPlayer *obj)
{
	obj->GetState()->Update(obj, HoistingState::GetInstance());
}

void HoistingState::ChangeState(EnemyPlayer *obj, EnemyState *newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}

//トルネードと敵との半径の距離の絶対値を取る
//最初は半径を減らすだけ→少しずつ回転して半径減らす→半径０になったら次のステートへ
//→クルクル回り続ける→発射