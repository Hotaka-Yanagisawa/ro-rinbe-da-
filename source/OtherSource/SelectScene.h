//=======================================================================
// SelectScene.h
//-----------------------------------------------------------------------
// �쐬�� : ��������
//-----------------------------------------------------------------------
// �X�V����
//	2020/12/04	�^�C�g����̃X�e�[�W�I����ʎ����̂��ߍ쐬
//			11	�ꉞ��ՂƂȂ鏊�͂ł����Ǝv���B���Ȃ莞�Ԃ��������Ă��܂����B����
//				�X�e�[�W�̉摜�𑝂₵�Ă����Ȃ����삷��悤�ɂ��Ă������B
//				��]�ɒx��\���������B
//			13	�����L���O�̂Ƃ��ǉ�(����)
//			16	�����L���O�ƑI���X�e�[�W�ÓI�ɂ���(����)
//
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Scene.h"
#include "PolygonList.h"
#include "Ranking.h"
#include <array>
#include "MySound.h"

//--- �萔
#define SCORE_FILE	("Data/Ranking.txt")

//--- �񋓑�
namespace SELECTSCENE
{
	enum STEP
	{
		SELECT,
		STANDBY,

		MAX
	};
}

//--- �N���X
class SelectScene : public Scene
{
public:
	SelectScene() {}
	~SelectScene() {}

	void Init() override;
	void Uninit() override;

	SCENE::TYPE Update() override;
	void Draw() override;

	static Ranking m_Ranking;

	static int m_nSelect;

private:

	float m_radius;
	int m_nTexNum;
	float m_fDistanceAngle;

	float m_fpLatePositonY;
	float *m_fpPersonalAngle;
	float *m_fpLatePersonalAngle;
	Pol2D *m_pSelectSceneImage;

	int m_nTimer;
	int m_nReturnTime;

	std::array<Pol2D, 2> m_Cursor;

	PolygonList m_PolList;
	PolygonList m_SelectList;
	PolygonList m_ScorePol[STAGE_NUM];
	PolygonList m_Star;
	PolygonList m_Plate;

	SELECTSCENE::STEP m_Step;

	CSound m_Sound;
	CSound m_SE;
};
