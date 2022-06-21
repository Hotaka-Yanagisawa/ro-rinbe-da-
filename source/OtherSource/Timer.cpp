//--- �C���N���[�h
#include "Timer.h"
#include "Pol2D.h"
#include <math.h>
#include "Shader.h"
#include "Defines.h"

//==================================================
// ������
//==================================================
void Timer::Init()
{
	m_nCount = 0 * 60;
	m_nAlert = 0;

	// �^�C�}�[
	m_Timer.Init();
	m_Timer.m_bParallel = true;
	m_Timer.SetTexture(TEX_PNG("SandWatch"));
	m_Timer.m_Transform.Position = { SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 30, 0 };
	m_Timer.m_Transform.Size = { 200, 150, 0 };
	for (int i = 0; i < 3; i++)
	{
		m_Number[i].Init();
		m_Number[i].m_bParallel = true;
		m_Number[i].SetTexture(TEX_PNG("Number"));
		m_Number[i].m_Transform.Position = { SCREEN_WIDTH / 2 - 45 - i * 40.0f, SCREEN_HEIGHT / 2 - 65, 0 };
		m_Number[i].m_Transform.Size = { 70, 80, 0 };
		m_Number[i].m_fSplitX = 5; m_Number[i].m_fSplitY = 2;
		m_Number[i].m_fTexCoordX = 1;
		m_Number[i].m_r = m_Number[i].m_g = m_Number[i].m_b = m_Number[i].m_a = 1;
	}
}

//==================================================
// �I��
//==================================================
void Timer::Uninit()
{
	m_Timer.Uninit();
	for (int i = 0; i < 3; i++)
		m_Number[i].Uninit();
}

//==================================================
// �X�V
//==================================================
void Timer::Update()
{
	int Num = m_nCount / 60;
	int Rank = 0;
	while (Num > 0)
	{
		int a = Num % 10;

		m_Number[Rank].m_fTexCoordX = a % 5;
		m_Number[Rank].m_fTexCoordY = a / 5;

		++Rank;

		Num /= 10;
	}
	if (Rank < 3) m_Number[2].m_fTexCoordX = m_Number[2].m_fTexCoordY = 0;
	if (Rank < 2) m_Number[1].m_fTexCoordX = m_Number[1].m_fTexCoordY = 0;

	m_Timer.Update();

	for (int i = 0; i < 3; i++)
		m_Number[i].Update();

	// �J�E���g
	if (m_nCount > 0) --m_nCount;
}

//==================================================
// �`��
//==================================================
void Timer::Draw()
{
	m_Timer.Draw();
	for (int i = 0; i < 3; i++) m_Number[i].Draw();

}

//==================================================
// �@�\�̊T�v
//--------------------------------------------------
// ����1	: 
// �߂�l	: 
//==================================================
void Timer::SetTime(int count, int alert)
{
	m_nCount = count;
	m_nAlert = alert;
}

int Timer::GetTime()
{
	return m_nCount;
}
