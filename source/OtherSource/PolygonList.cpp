//--- インクルード
#include "PolygonList.h"

//==================================================
// 初期化
//==================================================
void PolygonList::Init()
{
	m_nCount = 0;
	m_nEmptyCount = 0;

	for (auto i : m_Polygon) i->Init();
}

//==================================================
// 終了
//==================================================
void PolygonList::Uninit()
{
	m_nCount = 0;
	m_nEmptyCount = 0;

	for (auto i : m_Polygon) i->Uninit();

	m_Name.clear();
	m_Polygon.clear();
}

//==================================================
// 更新
//==================================================
void PolygonList::Update()
{
	for (auto i : m_Polygon) i->Update();
}

//==================================================
// 描画
//==================================================
void PolygonList::Draw()
{
	for (auto i : m_Polygon) i->Draw();
}

//==================================================
// 追加
//--------------------------------------------------
// 引数1	: ポリゴンのアドレス
// 引数2	: 設定する名前
//==================================================
Pol2D* PolygonList::Add(Pol2D* pPolygon, std::string sName)
{
	// 名無し
	if (sName == "empty")
	{
		sName += std::to_string(m_nEmptyCount);
		++m_nEmptyCount;
	}

	m_Name.push_back(sName);
	m_Polygon.push_back(pPolygon);

	++m_nCount;

	return pPolygon;
}

//==================================================
// 取得
//--------------------------------------------------
// 引数		: 名前
// 戻り値	: ポリゴンのアドレス
//==================================================
Pol2D* PolygonList::Get(std::string sName)
{
	for (int i = 0; i < m_Name.size(); ++i)
		if (m_Name[i] == sName) return m_Polygon[i];

	return nullptr;
}

//==================================================
// 移動量設定
//==================================================
void PolygonList::SetMove(Float3 move)
{
	for (auto i : m_Polygon) i->m_Transform.Position += move;
}
