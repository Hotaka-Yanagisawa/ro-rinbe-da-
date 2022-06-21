//=======================================================================
// GameScene.h
//-----------------------------------------------------------------------
// 作成者 : 水野樹生
//-----------------------------------------------------------------------
// 更新履歴
//	2020/11/19	ObjectListを管理させるために作成
//			27	流れの列挙体
//			28	仮のタイマーとスコア
//		 12/01	タイマー
//
//=======================================================================
#pragma once

//--- インクルード
#include "Scene.h"
#include "ObjectList.h"
#include "EnemyManager.h"
#include "UI2D.h"
#include "Score.h"
#include "MySound.h"

//--- 列挙体
namespace GAMESCENE
{
	// ゲームシーンの流れ
	enum STEP
	{
		START,
		MAIN,
		CLEAR,
		GOVER,

		MAX
	};
}

//--- クラス
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