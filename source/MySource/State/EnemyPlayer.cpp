#include "EnemyPlayer.h"
#include "InvasionState.h"
#include "HoistingState.h"
#include "AbsorbState.h"
#include "WindState.h"
#include "WaitState.h"
#include "../Object.h"
#include "../GameScene.h"
#include"../Score.h"

std::queue<EnemyPlayer*> EnemyPlayer::m_FireQueue;
std::queue<EnemyPlayer*> EnemyPlayer::m_ReuseQueue;
std::queue<EnemyPlayer*> EnemyPlayer::m_LoadingQueue;
int EnemyPlayer::MyNum = 0;
int EnemyPlayer::m_TotalSucksNum = 0;
int EnemyPlayer::m_nLoadingNum;
float EnemyPlayer::m_fCapa = 0;

EnemyPlayer::EnemyPlayer()
	: m_fWeight(5)
	, m_fAttack(1.0f)
{
	m_bEnd = false;
	
	m_AbsorbMax = 1.0f;
	m_AbsorbSpd = 1.0f / 180.0f;
	m_AbsorbTotal = 0;
}

EnemyPlayer::~EnemyPlayer()
{

}

void EnemyPlayer::Init()
{
	m_Transform = m_Parent->Get<Transform>();

	m_HierarchyState = InvasionState::GetInstance();
	m_HierarchyState->Init(this);

	m_bESC = false;
	m_bEnd = false;
	m_AbsorbMax = 1.0f;
	m_AbsorbSpd = 1.0f / 180.0f;
	m_AbsorbTotal = 0;
	m_nReuseCnt = 0;
	switch (m_Features)
	{
	case Features::NORMAL:
		m_AbsorbMax = 1.0f;
		m_AbsorbSpd = 1.0f / 180.0f;
		m_AbsorbTotal = 0;
		m_fAttack = 1.0f;
		m_fWeight = 5.0f;
		m_bESC = false;
		m_bEnd = false;
		break;
	case Features::SPEED:
		m_AbsorbMax = 0.5f;
		m_AbsorbSpd = 1.0f / 180.0f;
		m_AbsorbTotal = 0;
		m_fAttack = 1.0f;
		m_fWeight = 5.0f;
		m_bESC = false;
		m_bEnd = false;
		break;
	case Features::FAT:
		m_AbsorbMax = 3.0f;
		m_AbsorbSpd = 3.0f / 180.0f;
		m_AbsorbTotal = 0;
		m_fAttack = 3.0f;
		m_fWeight = 15.0f;
		m_bESC = false;
		m_bEnd = false;
		break;
	default:
		break;
	}
	if (m_Parent->m_Tag == OBJECT::TREE)
	{
		m_fAttack = 0.5f;
		m_fWeight = 10.0f;
	}
}

void EnemyPlayer::Update()
{
	m_Sound.Update();
	m_HierarchyState->Update(this);
}

void EnemyPlayer::Draw()
{
}

void EnemyPlayer::OnCollision(Object* pObj)
{

}

void EnemyPlayer::OnCollisionEnter(Object* pObj)
{
	if (pObj->m_Tag == OBJECT::BOSS)
	{
		if ((m_Parent->m_Tag == OBJECT::ENEMY1)
			|| (m_Parent->m_Tag == OBJECT::ENEMY2)
			|| (m_Parent->m_Tag == OBJECT::ENEMY3))
		{
			m_Transform->Position = SetNewTransformPos(999, 0, 999);
			m_ReuseQueue.push(this);

			m_State = WaitState::GetInstance();
			m_State->Init(this);
		}
		else if (m_Parent->m_Tag == OBJECT::TREE)
		{
			// 消去
			GameScene::GetObjectList()->Destroy(m_Parent);
		}
	}
		
	//ステートがwindの時は処理を行わない→Initで違うステートになってしまうから
	if (pObj->m_Tag == OBJECT::PLAYER && m_HierarchyState != HoistingState::GetInstance())
	{
		if (m_fCapa < 120)
		{
			int num;
			Score::GetInstance()->m_curCombo++;
			num = 100 * (Score::GetInstance()->m_curCombo / 3 + 1);
			Score::GetInstance()->m_DrawScore = num;
			Score::GetInstance()->m_TotalScore += num;
			Score::GetInstance()->m_Pos = m_Transform->Position;
			Score::GetInstance()->m_curIdx++;
			Score::GetInstance()->SetA();
			if (Score::GetInstance()->m_curIdx > 9) Score::GetInstance()->m_curIdx = 0;
			m_HierarchyState = HoistingState::GetInstance();
			m_HierarchyState->Init(this);
		}
	}


	//階層がHoistingの時は処理を行わない→巻き込まれいるため吸収することできない
	if (pObj->m_Tag == OBJECT::TEMPLE && m_HierarchyState != HoistingState::GetInstance())
	{
		if (m_AbsorbTotal < m_AbsorbMax)
		{
			m_State = AbsorbState::GetInstance();
			m_State->Init(this);
		}
	}
}

void EnemyPlayer::QueueClear()
{
	while (!m_FireQueue.empty())	m_FireQueue.pop();
	while (!m_LoadingQueue.empty())
	{
		m_LoadingQueue.pop();
		--m_nLoadingNum;
	}
	//while (!m_ReuseQueue.empty())	m_ReuseQueue.pop();
}

void EnemyPlayer::SetNewTransformRotate(float x, float y, float z)
{
	m_Transform->Rotate.x = x;
	m_Transform->Rotate.y = y;
	m_Transform->Rotate.z = z;
}

Float3 EnemyPlayer::SetNewTransformPos(float x, float y, float z)
{
	m_Transform->Position.x = x;
	m_Transform->Position.y = y;
	m_Transform->Position.z = z;
	return m_Transform->Position;
}

Transform *EnemyPlayer::SetNewTransform(Transform *Transform)
{
	m_Transform = Transform;
	return nullptr;
}

std::pair<float, float> RecalculationMacro(float num1, float num2)
{
	std::pair<float, float> num;
	num.first = num1;
	num.second = num2;

	int flag;
	flag = rand() % 2;

	if (num.first > 150 || num.second > 150)
	{
		if (num.first <= num.second)
		{
			if (flag)
			{
				num.second = 150;
			}
			else
			{
				num.second = -150;

			}
		}
		else
		{
			if (flag)
			{
				num.first = 150;
			}
			else
			{
				num.first = -150;
			}
		}
		return num;
	}



	else
	{
		if (num.first <= num.second)
		{
			if (flag)
			{
				num.second = 150;
			}
			else
			{
				num.second = -150;
			}
		}
		else
		{
			if (flag)
			{
				num.first = 150;
			}
			else
			{
				num.first = -150;
			}
		}
	}
	return num;
}

float RecalculationMacro()
{
	float newNum;

	newNum = (rand() % 400) - 200;

	return newNum;
}