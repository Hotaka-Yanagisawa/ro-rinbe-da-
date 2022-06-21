//--- �C���N���[�h
#include "Fade.h"
#include "Defines.h"

//==================================================
// ������
//==================================================
void Fade::Init()
{
	m_Polygon.Init();
	//m_Polygon.SetTexture("Assets/sora.jpg");
	m_Polygon.m_Transform.Size.x = SCREEN_WIDTH;
	m_Polygon.m_Transform.Size.y = SCREEN_HEIGHT;
	m_Polygon.m_Transform.Position.x = 0;
	m_Polygon.m_Transform.Position.y = 0;
	m_Polygon.m_r = m_Polygon.m_g = m_Polygon.m_b = 0;
	m_Polygon.m_a = 0;
	m_Polygon.m_bParallel = true;

	m_Status = FADE::_NO;
	m_nCount = m_nTime = 0;
}

//==================================================
// �I��
//==================================================
void Fade::Uninit()
{
	m_Polygon.Uninit();
}

//==================================================
// �X�V
//==================================================
bool Fade::Update()
{
	// �t�F�[�h�C��
	if (m_Status == FADE::_IN)
	{
		if (m_nCount > 0)
		{
			m_nCount--;
			m_Polygon.m_a -= 1.0f / m_nTime;
		}
		else
		{
			m_Polygon.m_a = 0;
			m_Status = FADE::_NO;
			m_nCount = m_nTime = 0;
		}
	}

	// �t�F�[�h�A�E�g
	if (m_Status == FADE::_OUT)
	{
		if (m_nCount > -m_nTime)
		{
			m_nCount--;
			m_Polygon.m_a += 1.0f / m_nTime;
		}
		else
		{
			m_Polygon.m_a = 1;
			m_Status = FADE::_IN;
			m_nCount = m_nTime;

			// �t�F�[�h�A�E�g����
			return true;
		}
	}

	m_Polygon.Update();
	return false;
}

//==================================================
// �`��
//==================================================
void Fade::Draw()
{
	m_Polygon.Draw();
}

//==================================================
// �t�F�[�h�A�E�g�̊J�n
//--------------------------------------------------
// ����		: ���s����
//==================================================
void Fade::FadeOut(int Time)
{
	if (m_Status != FADE::_NO) return;

	m_nTime = m_nCount = Time;
	m_Status = FADE::_OUT;
	m_Polygon.m_a = 0;
}

//==================================================
// �t�F�[�h�̐ݒ�
//--------------------------------------------------
// ����		: �s�����x
//==================================================
void Fade::SetFade(float alpha)
{
	m_Polygon.m_a = alpha;

	if (alpha <= 0) m_Status = FADE::_NO;
}
