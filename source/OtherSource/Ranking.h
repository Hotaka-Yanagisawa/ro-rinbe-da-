//=======================================================================
// Ranking.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/12/13	�쐬
//			
//=======================================================================
#pragma once

//--- �萔
#define MAX_RANK	(6)	// �ő包
#define SAVE_NUM	(3)	// �ۑ����鐔
#define STAGE_NUM	(3)	// �X�e�[�W�̐�

//--- �\����
struct RANKING_DATA
{
	int Score[SAVE_NUM];
};

//--- �N���X
class Ranking
{
public:
	Ranking() {}
	~Ranking() {}

	void Load(const char* FileName);
	void Save(const char* FileName);

	void SetScore(int Value, int StageNum);

	RANKING_DATA m_Data[STAGE_NUM];

private:
	void Swap(int&, int&);
};
