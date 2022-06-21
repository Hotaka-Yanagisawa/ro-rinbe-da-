//=======================================================================
// GameScene.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/19	ObjectList���Ǘ������邽�߂ɍ쐬
//			27	����̗񋓑�
//			28	���̃^�C�}�[�ƃX�R�A
//		 12/01	�^�C�}�[
//
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Scene.h"
#include "ObjectList.h"
#include "EnemyManager.h"
#include "UI2D.h"
#include "Score.h"
#include "MySound.h"

//--- �񋓑�
namespace GAMESCENE
{
	// �Q�[���V�[���̗���
	enum STEP
	{
		START,
		MAIN,
		CLEAR,
		GOVER,

		MAX
	};
}

//--- �N���X
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void Init() override;
	void Uninit() override;

	SCENE::TYPE Update() override;
	void Draw() override;

	static ObjectList* GetObjectList() { return m_pObjList; }

	friend class EnemyManager;
	EnemyManager m_EnemyManager;

	UI2D m_UI;

	static GAMESCENE::STEP m_Step;

private:

	static ObjectList* m_pObjList;
	int nWaitResult;
	CSound m_Sound;
};