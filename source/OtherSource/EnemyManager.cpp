//--- �C���N���[�h
#include "EnemyManager.h"
#include "GameScene.h"
#include "Transform.h"
#include "State/EnemyPlayer.h"
#include "SelectScene.h"

//==================================================
// ������
//==================================================
void EnemyManager::Init()
{
	m_nCount = 0;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		m_bUse[i] = false;
		// ���
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
		// ������|�C���^��ێ�
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
		// ��ސݒ�
		m_Enemy[i]->Get<EnemyPlayer>()->m_Features = Kind;
	}
}

//==================================================
// �I��
//==================================================
void EnemyManager::Uninit()
{
}

//==================================================
// �G����
//--------------------------------------------------
// ����		: �G�̎��(�̂��̂�)
//==================================================
void EnemyManager::Create()
{
	if (m_nCount == MAX_ENEMY) return;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (m_bUse[i]) continue;

		// �|�C���^�����X�g�ɒǉ�
		GameScene::m_pObjList->Add(m_Enemy[i]);
		m_bUse[i] = true;

		++m_nCount;

		break;
	}
}

//==================================================
// �G����
//--------------------------------------------------
// ����		: �|�C���^
//==================================================
void EnemyManager::Destroy(Object *pEnemy)
{
	GameScene::m_pObjList->Destroy(pEnemy);
	--m_nCount;
}
