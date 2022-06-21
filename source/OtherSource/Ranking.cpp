//--- �C���N���[�h
#include "Ranking.h"
#include <fstream>

//==================================================
// �f�[�^�ǂݍ���
//--------------------------------------------------
// ����		: �t�@�C����
//==================================================
void Ranking::Load(const char* FileName)
{
	std::ifstream file(FileName);
	// �G���[
	if (!file) return;

	// �X�e�[�W�~�f�[�^�����ǂݍ���
	for (int j = 0; j < STAGE_NUM; ++j)
		for (int i = 0; i < SAVE_NUM; ++i)
			file >> m_Data[j].Score[i];
}

//==================================================
// �f�[�^�ۑ�
//--------------------------------------------------
// ����		: �t�@�C����
//==================================================
void Ranking::Save(const char* FileName)
{
	std::ofstream file(FileName);
	// �G���[
	if (!file) return;

	// �X�e�[�W�~�f�[�^������������
	for (int j = 0; j < STAGE_NUM; ++j)
		for (int i = 0; i < SAVE_NUM; ++i)
			file << m_Data[j].Score[i] << std::endl;
}

//==================================================
// �X�R�A�𔽉f
//--------------------------------------------------
// ����		: �X�R�A
//==================================================
void Ranking::SetScore(int Value, int StageNum)
{
	// �O�ʂɓ��邩�`�F�b�N
	if (Value > m_Data[StageNum].Score[2])
		m_Data[StageNum].Score[2] = Value;

	// �~���\�[�g
	for (int i = SAVE_NUM - 1; i > 0; --i)
	{
		if (m_Data[StageNum].Score[i] > m_Data[StageNum].Score[i - 1])
			Swap(m_Data[StageNum].Score[i], m_Data[StageNum].Score[i - 1]);
	}

}

//==================================================
// �l����ւ�
//--------------------------------------------------
// ����1, 2	: �l
//==================================================
void Ranking::Swap(int& a, int& b)
{
	int Tmp = a;
	a = b;
	b = Tmp;
}

