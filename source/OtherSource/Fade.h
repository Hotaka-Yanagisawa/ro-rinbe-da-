//=======================================================================
// Fade.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/12/05	�쐬 FadeOut
//			10	SetFade����
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Pol2D.h"

//--- �񋓑�
namespace FADE
{
	enum STATUS
	{
		_NO,
		_OUT,
		_IN,

		MAX
	};
}

//--- �N���X
class Fade
{
public:
	void Init();
	void Uninit();
	bool Update();
	void Draw();

	void FadeOut(int Time);
	void SetFade(float alpha);

	FADE::STATUS m_Status;

private:

	Pol2D m_Polygon;

	int m_nCount;
	int m_nTime;
};
