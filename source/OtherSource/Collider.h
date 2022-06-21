//=======================================================================
// Collider.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/12	授業のやつ
//			19	Collisionをstaticで所持
//			22	判定対象をリストにした
//			23	判定描画用キューブ実装
//			24	Uninitでリストから外れるようにした
//			27	Collisionにコンポーネントを渡す処理にした
//
//=======================================================================
#pragma once

//--- インクルード部
#include "Component.h"
#include "Cube.h"

//--- クラス
class Collider : public Component
{
public:

	Collider() {}
	~Collider() {}

	void Init() override;
	void Uninit() override;

	void Update() override;
	void Draw() override;

	void AddTarget(int Tag);
	void RemoveTarget(int Tag);

	std::list<int> m_TargetList;

private:
	Cube m_Cube;

};
