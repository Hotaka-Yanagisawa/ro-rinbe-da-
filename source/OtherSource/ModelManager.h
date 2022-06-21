//=======================================================================
// ModelManager.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/12/19	�쐬
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include <unordered_map>
#include "FBX/FBXPlayer.h"

//--- �}�N��
#define FILE_MODEL(name)	"Assets/Model/"##name##".fbx"

#define MODEL	(ModelManager::GetInstance())

//--- �N���X
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
