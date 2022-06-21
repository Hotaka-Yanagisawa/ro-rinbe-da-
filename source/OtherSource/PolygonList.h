//=======================================================================
// PolygonList.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/12/11	作成
//			14	名前指定なしで追加できるようにした
//	2021/01/18	mapやめてvector2個にした
//			
//=======================================================================
#pragma once

//--- インクルード
#include "Pol2D.h"
#include <vector>
#include <string>

//--- クラス
class PolygonList
{
public:
	PolygonList() {}
	~PolygonList() {}

	void Init();
	void Uninit();

	void Update();
	void Draw();

	Pol2D* Add(Pol2D* pPolygon, std::string sName = "empty");
	Pol2D* Get(std::string sName);

	void SetMove(Float3 move);

private:
	std::vector<std::string> m_Name;
	std::vector<Pol2D*> m_Polygon;

	int m_nCount;
	int m_nEmptyCount;
};
