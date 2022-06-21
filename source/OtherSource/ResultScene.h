//=======================================================================
// ResultScene.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/12/11	�쐬
//
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Scene.h"
#include "PolygonList.h"
#include "Number.h"
#include "MySound.h"

//--- �񋓑�
enum RESULT_STEP
{
	RESULT_STEP_BEGIN = -1,
	// �X�R�A�̉��Z
	ADD_SCORE_ENEMY,
	ADD_SCORE_TIME,
	ADD_SCORE_LIFE,
	ADD_SCORE_CLEAR,
	ADD_SCORE_MISSION,

	RESULT_STEP_MAX
};

//--- �N���X
class ResultScene : public Scene
{
public:
	ResultScene() {}
	~ResultScene() {}

	void Init() override;
	void Uninit() override;

	SCENE::TYPE Update() override;
	void Draw() override;

private:
	int m_nType;

	int m_nScore;
	int m_nTotalScore;
	int m_nTime;		//�c�莞��
	int m_nMaxCombo;	//�ő�R���{��
	int m_nHp;			//�c��HP
	int m_nEnemyNum;	//�����񂾐��̍��v

	RESULT_STEP m_Step;
	int m_nWait;
	int m_nAdd;

	PolygonList m_PolList;
	PolygonList m_Result;
	Number m_Number[RESULT_STEP_MAX];

	CSound m_Sound;
	CSound m_SE;
	CSound m_SE2;

};
