////////////////////////////////////////////////////////////////////////////////////////////
// EnemyPlayer.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// Enemy専用のコンポーネント
// Enemyの行動全般の処理
// 状態の変化で処理を行うコンポーネント
// 侵略階層   : 静止・神殿に移動・エネルギー吸収・帰る
// 巻込み階層 : 吸い込み・巻き上げ(wind)・発射
//-----------------------------------------------------------------------------------------
// 2020/11/24	侵略階層   : 静止・神殿に移動・エネルギー吸収・帰る
//              巻込み階層 : 吸い込み・巻き上げ(wind)・装填・発射 を作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Transform.h"
#include "../Component.h"
#include "HierarchyEnemyState.h"
#include <queue>
#include <stdlib.h>
#include "../MySound.h"


std::pair<float, float> RecalculationMacro(float num1, float num2);
float RecalculationMacro();

//敵の特徴
enum Features
{
	NORMAL,
	SPEED,
	FAT,
};
class EnemyPlayer : public Component
{
public:
	EnemyPlayer();
	~EnemyPlayer();


	void Init() override;

	void Update() override;
	void Draw() override;

	void OnCollision(Object* pObj) override;
	void OnCollisionEnter(Object* pObj) override;

	static void QueueClear();
	
	Transform *GetTransform() { return m_Transform; }
	EnemyState *GetState() { return m_State; }
	static std::queue<EnemyPlayer*> GetQueue() { return m_FireQueue; }
	float GetAbsorbMax() { return m_AbsorbMax; }
	float GetAbsorbSpd() { return m_AbsorbSpd; }
	float GetAbsorbTotal() { return m_AbsorbTotal; }

	void SubtractAbsorbTotal(float num) { m_AbsorbTotal += num; }

	void SetAbsorbMax(float Max) { m_AbsorbMax = Max; }
	void SetAbsorbSpd(float Spd) { m_AbsorbSpd = Spd; }
	void SetState(EnemyState *newState) { m_State = newState; }
	void SetHierarchyState(HierarchyEnemyState *newState) { m_HierarchyState = newState; }

	void SetTransform(Transform newTransform) { m_Transform = &newTransform; }
	void SetNewTransformRotate(float, float, float);
	Float3 SetNewTransformPos(float, float, float);
	Transform *SetNewTransform(Transform*);


	//セッターゲッターに変えること
	//他のEnemy同じ値を使いたくない場合は
	//このクラスにメンバ変数を作る必要あり
	bool m_bESC;
	bool m_bUse;
	bool m_bPlusOrMinusX;
	bool m_bPlusOrMinusZ;
	float m_DistanceX;
	float m_DistanceZ;
	float m_xzAngle;
	float m_yAngle;
	float m_Angle;	// 上下移動用
	float m_radius;	// 半径
	float m_fWeight;
	float m_fAttack;
	float m_AbsorbMax;
	float m_AbsorbSpd;
	float m_AbsorbTotal;
	static float m_fCapa;		//積載量→エネミーが持つのは不自然
	static int m_nLoadingNum;	//何体装填されているのか
	static int m_TotalSucksNum;	//スコア用　1ゲームでオブジェクトを巻き込んだ数
	CSound m_Sound;


	//キューに入った順に発射できるようにするため→WindState→FireStateの流れ
	static std::queue<EnemyPlayer*> m_FireQueue;
	//同時発射用の溜め
	static std::queue<EnemyPlayer*> m_LoadingQueue; 
	//エネミーを再利用するために使う
	static std::queue<EnemyPlayer*> m_ReuseQueue;
	//このコンポーネントを保持している存在する数
	static int MyNum;
	int m_nReuseCnt;
	Features m_Features;
	Transform* m_Transform;

private:
	
	//階層は戻ることがないため使用
	//コリジョンが一度だけしか反応しないのなら消せる
	bool m_bEnd;
	HierarchyEnemyState *m_HierarchyState;	//階層
	EnemyState *m_State;					//状態
};

