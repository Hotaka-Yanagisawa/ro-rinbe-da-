//--- インクルード
#include "ModelManager.h"
#include "Model.h"

//==================================================
// 初期化
//==================================================
void ModelManager::Init()
{
	m_List.clear();

	Model::LoadMultiModel();
}

//==================================================
// 終了
//==================================================
void ModelManager::Uninit()
{
	m_List.clear();
}

//==================================================
// 更新
//==================================================
void ModelManager::Update()
{
	// アニメーション
	for (auto i : m_List) if(i.second->IsPlay()) i.second->Step();
}

//==================================================
// 描画
//==================================================
void ModelManager::Draw()
{
	Model::DrawMultiModel();
}

//==================================================
// モデル読み込み
//--------------------------------------------------
// 引数		: ファイル名
// 戻り値	: アドレス
//==================================================
FBXPlayer* ModelManager::Load(std::string Name)
{
	if (!m_List.count(Name))
	{
		FBXPlayer* pModel = new FBXPlayer();
		pModel->LoadModel(Name.c_str());
		m_List[Name] = pModel;
		return pModel;
	}
	else return m_List[Name];
}
