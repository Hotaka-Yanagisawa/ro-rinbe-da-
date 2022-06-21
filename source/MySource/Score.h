//=======================================================================
// Score.h
//-----------------------------------------------------------------------
// �쐬�� : ���򔿋M
//-----------------------------------------------------------------------
// �X�V����
//	2020/12/06	�쐬
//			
//
//=======================================================================
#pragma once

//--- �C���N���[�h��
#include "Transform.h"
#include "Pol2D.h"

//--- �N���X
class Score
{
public:
	static Score *GetInstance()
	{
		static Score instance;
		return &instance;
	}

	void Init();
	void Update();
	void Draw();

	void SetA()
	{
		for (int i = 0; i < 4; i++)
		{
			m_DrawCnt = 300;
			m_Pol[i].m_a = 1;
			m_Pol[i].m_Transform.Move.y = 1.0f;
			m_Pol[i].m_Transform.Position.y = -100;
			m_Frme.m_a = 1;
		}
		for (int i = 0; i < 3; i++)
		{
			m_ComboPoly[i].m_a = 1;
		}
	}

	Float3 m_Pos;
	int m_DrawScore;		//�`�悷��l���X�R�A�̒l
	Pol2D m_ComboPoly[3];	//�R���{���`��
	Pol2D m_Pol[4];			//�l�������X�R�A�̕`��p
	Pol2D m_TotalPol[10];	//���v�X�R�A�̕`��p
	Pol2D m_Frme;			//�`��X�R�A�̃t���[��
	int m_TotalScore;		//���݂̊l�����Ă���X�R�A�̍��v
	int m_curCombo;			//���݂̃R���{��
	int m_oldCombo;			//1�t���[���O�̃R���{��
	int m_MaxCombo;			//�ő�R���{��
	int m_comboCnt;			//�R���{�̓r�؂��Ԋu�̃J�E���g
	int m_curIdx;			//�Y�����p

private:
	Score() {}
	~Score() {}
	unsigned int m_ComboDigits;	//�`�悷��R���{�̌���
	unsigned int m_Digits;		//�`�悷��X�R�A�̌���
	int m_TotalDigits;			//�`�悷��g�[�^���X�R�A�̌���
	int m_DrawCnt;				//�`�悷�鎞��
};
//�����`�F�b�N
unsigned int GetDigit(unsigned int num);
