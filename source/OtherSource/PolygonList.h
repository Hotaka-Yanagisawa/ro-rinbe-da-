//=======================================================================
// PolygonList.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/12/11	�쐬
//			14	���O�w��Ȃ��Œǉ��ł���悤�ɂ���
//	2021/01/18	map��߂�vector2�ɂ���
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Pol2D.h"
#include <vector>
#include <string>

//--- �N���X
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
