//=======================================================================
// UI2D.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/28	�쐬
//		 12/10	�|�[�Y��ʍ쐬�͂��� Update�̖߂�l�ύX
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "PolygonList.h"
#include "Timer.h"
#include "MySound.h"

//--- �񋓑�
namespace UISYS
{
	enum STATUS
	{
		NO,
		PAUSE,
		RETRY,
		EXIT,

		MAX
	};
}

//--- �N���X
class UI2D
{
public:
	UI2D() {}
	~UI2D() {}

	void Init();
	void Uninit();

	UISYS::STATUS Update();
	void Draw();

	static int m_nResultHP;
	static bool m_bTmplHPFrag;

private:

	Pol2D m_BossHP;
	Pol2D m_BossGa;
	Pol2D m_TmplHP;
	Pol2D m_TmplGa;

	int m_nBasePos, m_nBaseSize;
	int m_nCount;
	int m_nSECnt;

	Pol2D m_Start;
	Pol2D m_Clear;
	Pol2D m_GOver;
	Pol2D m_Number;

	PolygonList m_Gage;

	bool m_bPause;
	bool m_bCntDown;

	std::string m_fileName[12];

	CSound m_Sound;
};
