//--- �C���N���[�h
#include "PolygonList.h"

//==================================================
// ������
//==================================================
void PolygonList::Init()
{
	m_nCount = 0;
	m_nEmptyCount = 0;

	for (auto i : m_Polygon) i->Init();
}

//==================================================
// �I��
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
// �X�V
//==================================================
void PolygonList::Update()
{
	for (auto i : m_Polygon) i->Update();
}

//==================================================
// �`��
//==================================================
void PolygonList::Draw()
{
	for (auto i : m_Polygon) i->Draw();
}

//==================================================
// �ǉ�
//--------------------------------------------------
// ����1	: �|���S���̃A�h���X
// ����2	: �ݒ肷�閼�O
//==================================================
Pol2D* PolygonList::Add(Pol2D* pPolygon, std::string sName)
{
	// ������
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
// �擾
//--------------------------------------------------
// ����		: ���O
// �߂�l	: �|���S���̃A�h���X
//==================================================
Pol2D* PolygonList::Get(std::string sName)
{
	for (int i = 0; i < m_Name.size(); ++i)
		if (m_Name[i] == sName) return m_Polygon[i];

	return nullptr;
}

//==================================================
// �ړ��ʐݒ�
//==================================================
void PolygonList::SetMove(Float3 move)
{
	for (auto i : m_Polygon) i->m_Transform.Position += move;
}
