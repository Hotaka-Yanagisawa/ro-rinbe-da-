////////////////////////////////////////////////////////////////////////////////////////////
// EnemyPlayer.h
//----------------------------------------------------------------------------------------
// ì¬ÒFöò ¿M
//----------------------------------------------------------------------------------------
// EnemyêpÌR|[lg
// EnemyÌs®SÊÌ
// óÔÌÏ»Åðs¤R|[lg
// NªKw   : Ã~E_aÉÚ®EGlM[zûEAé
// ªÝKw : z¢ÝEª«ã°(wind)E­Ë
//-----------------------------------------------------------------------------------------
// 2020/11/24	NªKw   : Ã~E_aÉÚ®EGlM[zûEAé
//              ªÝKw : z¢ÝEª«ã°(wind)EUE­Ë ðì¬
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

//GÌÁ¥
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


	//Zb^[Qb^[ÉÏ¦é±Æ
	//¼ÌEnemy¯¶lðg¢½­È¢êÍ
	//±ÌNXÉoÏðìéKv è
	bool m_bESC;
	bool m_bUse;
	bool m_bPlusOrMinusX;
	bool m_bPlusOrMinusZ;
	float m_DistanceX;
	float m_DistanceZ;
	float m_xzAngle;
	float m_yAngle;
	float m_Angle;	// ãºÚ®p
	float m_radius;	// ¼a
	float m_fWeight;
	float m_fAttack;
	float m_AbsorbMax;
	float m_AbsorbSpd;
	float m_AbsorbTotal;
	static float m_fCapa;		//ÏÚÊ¨Gl~[ªÂÌÍs©R
	static int m_nLoadingNum;	//½ÌU³êÄ¢éÌ©
	static int m_TotalSucksNum;	//XRAp@1Q[ÅIuWFNgðª«ñ¾
	CSound m_Sound;


	//L[ÉüÁ½É­ËÅ«éæ¤É·é½ß¨WindState¨FireStateÌ¬ê
	static std::queue<EnemyPlayer*> m_FireQueue;
	//¯­ËpÌ­ß
	static std::queue<EnemyPlayer*> m_LoadingQueue; 
	//Gl~[ðÄp·é½ßÉg¤
	static std::queue<EnemyPlayer*> m_ReuseQueue;
	//±ÌR|[lgðÛµÄ¢é¶Ý·é
	static int MyNum;
	int m_nReuseCnt;
	Features m_Features;
	Transform* m_Transform;

private:
	
	//KwÍßé±ÆªÈ¢½ßgp
	//RWªêx¾¯µ©½µÈ¢ÌÈçÁ¹é
	bool m_bEnd;
	HierarchyEnemyState *m_HierarchyState;	//Kw
	EnemyState *m_State;					//óÔ
};

