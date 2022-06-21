//=======================================================================
// ModelManager.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/12/19	作成
//			
//=======================================================================
#pragma once

//--- インクルード
#include <unordered_map>
#include "FBX/FBXPlayer.h"

//--- マクロ
#define FILE_MODEL(name)	"Assets/Model/"##name##".fbx"

#define MODEL	(ModelManager::GetInstance())

//--- クラス
class ModelManager
{
public:
	inline static ModelManager* GetInstance()
	{
		static ModelManager instance;
		return &instance;
	}

	void Init();
	void Uninit();

	void Update();
	void Draw();

	FBXPlayer* Load(std::string Name);

private:
	ModelManager() {}
	~ModelManager() {}

	std::unordered_map<std::string, FBXPlayer*> m_List;
};
