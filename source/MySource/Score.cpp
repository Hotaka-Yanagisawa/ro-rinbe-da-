#include "Score.h"
#include "Defines.h"

//--- �萔��` 
#define COMBO_TIME (300)	//�R���{�̓r�؂��Ԋu

void Score::Init()
{
	m_MaxCombo = m_DrawScore = m_TotalDigits = m_curIdx = m_curCombo = m_oldCombo = m_TotalScore = 0;
	
	m_DrawCnt = 300;
	m_Digits = 0;
	m_comboCnt = COMBO_TIME;

	m_Frme.Init();
	m_Frme.m_bParallel = true;
	m_Frme.SetTexture(TEX_PNG("Combo"));
	m_Frme.m_Transform.Position = { SCREEN_WIDTH / 2 - 130, 120, 0 };
	m_Frme.m_Transform.Size = 300;
	//m_Frme.m_a = 0;
	//�l���X�R�A
	for (int i = 0; i < 10; i++)
	{
		m_Pol[i].Init();
		m_Pol[i].m_bParallel = true;
		m_Pol[i].SetTexture(TEX_PNG("Number2"));
		m_Pol[i].m_Transform.Position = { 0, 10, 0 };
		m_Pol[i].m_Transform.Size = 60;
		m_Pol[i].m_fSplitX = 5;
		m_Pol[i].m_fSplitY = 2;
		m_Pol[i].m_fTexCoordX = -1;
		m_Pol[i].m_fTexCoordY = -1;
		//m_Pol[i].m_r = 0;
	}

	for (int i = 0; i < 3; i++)
	{	
		//�R���{��
		m_ComboPoly[i].Init();
		m_ComboPoly[i].m_bParallel = true;
		m_ComboPoly[i].SetTexture(TEX_PNG("Number2"));
		m_ComboPoly[i].m_Transform.Position = { -9999, -9999, -9999 };
		m_ComboPoly[i].m_Transform.Size = 150;
		m_ComboPoly[i].m_fSplitX = 5;
		m_ComboPoly[i].m_fSplitY = 2;
		m_ComboPoly[i].m_g = 0;
	}


	for (int i = 0; i < 10; i++)
	{
		//�g�[�^���X�R�A
		m_TotalPol[i].Init();
		m_TotalPol[i].m_bParallel = true;
		m_TotalPol[i].SetTexture(TEX_PNG("Number2"));
		m_TotalPol[i].m_Transform.Position = { -9999, -9999, -9999 };
		m_TotalPol[i].m_Transform.Size = 30;
		m_TotalPol[i].m_fSplitX = 5;
		m_TotalPol[i].m_fSplitY = 2;
		//m_TotalPol[i].m_fTexCoordX = -1;
		//m_TotalPol[i].m_fTexCoordY = -1;
		m_TotalPol[i].m_r = 0;
	}
}

void Score::Update()
{
	if (m_curCombo > m_MaxCombo) m_MaxCombo = m_curCombo;
	//�R���{���������Ă��邩���ׂ�
	//�����Ă���J�E���g���Z�b�g�A�����Ă��Ȃ��Ȃ�J�E���g���炷
	if (m_curCombo != m_oldCombo)	m_comboCnt = COMBO_TIME;
	else if (m_curCombo > 0)		m_comboCnt--;

	//300�t���[���R���{���r�؂ꂽ��O�R���{�ɂ���
	if (m_comboCnt < 1)
	{
		m_comboCnt = COMBO_TIME;
		m_curCombo = 0;
	}
	//�ߋ��̃R���{�X�V
	m_oldCombo = m_curCombo;
	
	//�R���{�̌����`�F�b�N
	m_ComboDigits = GetDigit(m_curCombo);
	int tempCombo = m_curCombo;
	int Rank = 0;
	while (tempCombo> 0)
	{
		int num = tempCombo % 10;
		//�摜��uv�ݒ�
		m_ComboPoly[Rank].m_fTexCoordX = num % 5;
		m_ComboPoly[Rank].m_fTexCoordY = num / 5;
		//���̕����ɂ��邽�ߓY�����̒l���₷
		++Rank;
		//�����炵
		tempCombo /= 10;
	}


	//������ł��Ȃ�������m_DrawScore�̒l�͂O�̂܂܂Ȃ̂ŃR���e�j���[����
	if (m_DrawScore != 0)
	{
		if (m_DrawScore > 9000)m_DrawScore = 9000;
		//�l�������X�R�A�̌����`�F�b�N
		m_Digits = GetDigit(m_DrawScore);
		int tempScore = m_DrawScore;
		int Rank = 0;
		while (tempScore > 0)
		{
			int num = tempScore % 10;
			//�摜��uv�ݒ�
			m_Pol[Rank].m_fTexCoordX = num % 5;
			m_Pol[Rank].m_fTexCoordY = num / 5;
			//���̕����ɂ��邽�ߓY�����̒l���₷
			++Rank;
			//�����炵
			tempScore /= 10;
		}
	}

	m_TotalDigits = 0;
	int tempScore = m_TotalScore;
	int index = 0;
	if (tempScore == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			m_TotalPol[index].m_fTexCoordX = 0;
			m_TotalPol[index].m_fTexCoordY = 0;
			++index;
			++m_TotalDigits;
		}
	}
	while (tempScore > 0)
	{
		int num = tempScore % 10;
		//�摜��uv�ݒ�
		m_TotalPol[index].m_fTexCoordX = num % 5;
		m_TotalPol[index].m_fTexCoordY = num / 5;
		//���̕����ɂ��邽�ߓY�����̒l���₷
		++index;

		++m_TotalDigits;
		//�����炵
		tempScore /= 10;
	}

	//�R���{���̃|���S���̍X�V
	//���������[�v���s��
	for (int i = 0; i < m_ComboDigits; i++)
	{
		//m_ComboPoly[i].m_Transform.Position = m_Pos;
		m_ComboPoly[i].Update();
	}

	//�l���X�R�A�̃|���S���̍X�V
		//���������[�v���s��
	for (int i = 0; i < m_Digits; i++)
	{
		//m_Pol[i].m_Transform.Position = m_Pos;
		m_Pol[i].m_Transform.Position.x = SCREEN_WIDTH / 2 -40 - i * 60.0f;
		m_Pol[i].m_Transform.Position.y += m_Pol[i].m_Transform.Move.y;
		m_Pol[i].m_Transform.Move.y -= 2.0f / 300.0f;
		m_Pol[i].Update();
	}

	//�g�[�^���X�R�A�̃|���S���̍X�V
	for (int j = 0; j < 6; j++)
	{
		m_TotalPol[j].m_Transform.Position.x = -SCREEN_WIDTH / 2 + 170 - j * 30.0f;
		m_TotalPol[j].m_Transform.Position.y = 270;
		m_TotalPol[j].Update();
	}
	m_Frme.Update();
}

void Score::Draw()
{
	m_Frme.Draw();
	//�g�[�^���X�R�A�̃|���S���̍X�V
	for (int i = 0; i < 6; i++)
	{
		m_TotalPol[i].Draw();
	}

	float AddX;
	for (int i = 0; i < m_ComboDigits; i++)
	{
		if (m_ComboDigits == 1)	AddX = 100.0f;
		if (m_ComboDigits == 2) AddX = 75.0f;
		if (m_ComboDigits == 3) AddX = 50.0f;
		//if (m_curCombo % 10 == 0)
		//{
		//	AddX = 500.0f;
		//}
		m_ComboPoly[i].m_Transform.Size = AddX;
		m_ComboPoly[i].m_Transform.Position.x = 550.0f - i * AddX;
		if (m_ComboDigits == 1)	m_ComboPoly[i].m_Transform.Position.x = 500.0f - i * AddX;
		if (m_ComboDigits == 3) m_ComboPoly[i].m_Transform.Position.x = 560.0f - i * AddX;
		m_ComboPoly[i].m_Transform.Position.y = 110;
		m_ComboPoly[i].Draw();
	}
	//������ł��Ȃ�������m_DrawScore�̒l�͂O�̂܂܂Ȃ̂ŃR���e�j���[����
	if (m_DrawScore != 0)
	{
		//�l�������X�R�A�̌����`�F�b�N
		m_Digits = GetDigit(m_DrawScore);
		//������Draw����
		for (int i = 0; i < m_Digits; i++)
		{
			if (m_Pol[i].m_fTexCoordX == -1) continue;
			m_Pol[i].Draw();
		}
		//Draw���ԃJ�E���g
		m_DrawCnt--;
		//Draw���ԃJ�E���g��0�ɂȂ�ƒl������
		if (m_DrawCnt < 1)
		{
			m_DrawCnt = 300;
			m_DrawScore = 0;
			//m_Frme.m_a = 0;
			for (int i = 0; i < m_Digits; i++)
			{
				m_Pol[i].m_a = 0;
			}
		}
		else
		{
			for (int i = 0; i < m_Digits; i++)
			{
				m_Pol[i].m_a -= 1.0f / 300.0f;
			}
			for (int i = 0; i < 3; i++)
			{
				m_ComboPoly[i].m_a -= 1.0f / 300.0f;
			}
		}
	}
}

//�����`�F�b�N
unsigned int GetDigit(unsigned int num)
{
	unsigned int digit = 0;
	while (num != 0)
	{
		num /= 10;
		digit++;
	}
	return digit;
}
