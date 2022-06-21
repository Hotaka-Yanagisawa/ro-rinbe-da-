//=======================================================================
// EnemyManager.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/27	�쐬
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Object.h"

//--- �萔
#define MAX_ENEMY	(50)	// ��ʏ�ɏo������ő吔

//--- �N���X
class EnemyManager
{
public:
	inline static EnemyManager* GetInstance()
	{
		static EnemyManager instance;
		return &instance;
	}

	void Init();
	void Uninit();

	void Create();
	void Destroy(Object*);

	friend class GameScene;

private:
	EnemyManager() {}
	~EnemyManager() {}

	int m_nCount;

	Object* m_Enemy[MAX_ENEMY];
	bool m_bUse[MAX_ENEMY];
};
