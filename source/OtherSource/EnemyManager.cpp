//--- インクルード
#include "EnemyManager.h"
#include "GameScene.h"
#include "Transform.h"
#include "State/EnemyPlayer.h"
#include "SelectScene.h"

//==================================================
// 初期化
//==================================================
void EnemyManager::Init()
{
	m_nCount = 0;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		m_bUse[i] = false;
		// 種類
		Features Kind;
		switch (SelectScene::m_nSelect)
		{
		case 0:
			Kind = Features::NORMAL;
			break;
		case 1:
			Kind = Features::FAT;
			//Kind = Features::SPEED;
			break;
		case 2:
			if (i < 30) Kind = Features::NORMAL;
			else  Kind = Features::FAT;
			break;
		}
		//if (i < 30) Kind = Features::NORMAL;
		//else if (i < 40) Kind = Features::SPEED;
		//else if (i < 50) Kind = Features::FAT;
		// 生成後ポインタを保持
		switch (Kind)
		{
		case NORMAL:
			m_Enemy[i] = GameScene::m_pObjList->Create(OBJECT::ENEMY1, false);
			m_Enemy[i]->Get<Transform>()->Size *= 2.0f;
			break;
		case SPEED:
			m_Enemy[i] = GameScene::m_pObjList->Create(OBJECT::ENEMY2, false);
			m_Enemy[i]->Get<Transform>()->Size *= 0.5f;
			break;
		case FAT:
			m_Enemy[i] = GameScene::m_pObjList->Create(OBJECT::ENEMY3, false);
			m_Enemy[i]->Get<Transform>()->Size *= 2.0f;
			break;
		default:
			break;
		}
		// 種類設定
		m_Enemy[i]->Get<EnemyPlayer>()->m_Features = Kind;
	}
}

//==================================================
// 終了
//==================================================
void EnemyManager::Uninit()
{
}

//==================================================
// 敵生成
//--------------------------------------------------
// 引数		: 敵の種類(のちのち)
//==================================================
void EnemyManager::Create()
{
	if (m_nCount == MAX_ENEMY) return;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_bUse[i]) continue;

		// ポインタをリストに追加
		GameScene::m_pObjList->Add(m_Enemy[i]);
		m_bUse[i] = true;

		++m_nCount;

		break;
	}
}

//==================================================
// 敵消去
//--------------------------------------------------
// 引数		: ポインタ
//==================================================
void EnemyManager::Destroy(Object *pEnemy)
{
	GameScene::m_pObjList->Destroy(pEnemy);
	--m_nCount;
}
