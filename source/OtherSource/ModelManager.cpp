//--- �C���N���[�h
#include "ModelManager.h"
#include "Model.h"

//==================================================
// ������
//==================================================
void ModelManager::Init()
{
	m_List.clear();

	Model::LoadMultiModel();
}

//==================================================
// �I��
//==================================================
void ModelManager::Uninit()
{
	m_List.clear();
}

//==================================================
// �X�V
//==================================================
void ModelManager::Update()
{
	// �A�j���[�V����
	for (auto i : m_List) if(i.second->IsPlay()) i.second->Step();
}

//==================================================
// �`��
//==================================================
void ModelManager::Draw()
{
	Model::DrawMultiModel();
}

//==================================================
// ���f���ǂݍ���
//--------------------------------------------------
// ����		: �t�@�C����
// �߂�l	: �A�h���X
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
