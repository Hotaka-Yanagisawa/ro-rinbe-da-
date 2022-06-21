//=======================================================================
// Number.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2021/01/22	�쐬
//
//=======================================================================

//--- �C���N���[�h
#include "Pol2D.h"

//--- �萔
#define MAX_NUMBER_RANK	(9)

//--- �N���X
class Number
{
public:

	void Init(int MaxRank, int Num = 0);
	void Uninit();

	void Update();
	void Draw();

	void SetNum(int Num);
	void SetNumStep(int Num, int Time = 1);

	void SetPos(float x, float y);
	void SetSize(float x, float y = -1.0f);
	void SetDist(float d);

	void SetMove(float x, float y);
	void SetColor(float r, float g, float b, float a);

	void DrawZero(bool);

private:
	int m_nNumber;
	Pol2D m_NumPol[MAX_NUMBER_RANK];

	int m_nMaxRank;
	int m_nAddScore;
	int m_nTime;
	bool m_bUpdate;

	float m_fPosX, m_fPosY;
	float m_fDist;
	bool m_bDrawZero;
};
