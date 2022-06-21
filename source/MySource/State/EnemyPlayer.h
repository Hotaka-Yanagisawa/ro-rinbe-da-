////////////////////////////////////////////////////////////////////////////////////////////
// EnemyPlayer.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// Enemy��p�̃R���|�[�l���g
// Enemy�̍s���S�ʂ̏���
// ��Ԃ̕ω��ŏ������s���R���|�[�l���g
// �N���K�w   : �Î~�E�_�a�Ɉړ��E�G�l���M�[�z���E�A��
// �����݊K�w : �z�����݁E�����グ(wind)�E����
//-----------------------------------------------------------------------------------------
// 2020/11/24	�N���K�w   : �Î~�E�_�a�Ɉړ��E�G�l���M�[�z���E�A��
//              �����݊K�w : �z�����݁E�����グ(wind)�E���U�E���� ���쐬
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

//�G�̓���
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


	//�Z�b�^�[�Q�b�^�[�ɕς��邱��
	//����Enemy�����l���g�������Ȃ��ꍇ��
	//���̃N���X�Ƀ����o�ϐ������K�v����
	bool m_bESC;
	bool m_bUse;
	bool m_bPlusOrMinusX;
	bool m_bPlusOrMinusZ;
	float m_DistanceX;
	float m_DistanceZ;
	float m_xzAngle;
	float m_yAngle;
	float m_Angle;	// �㉺�ړ��p
	float m_radius;	// ���a
	float m_fWeight;
	float m_fAttack;
	float m_AbsorbMax;
	float m_AbsorbSpd;
	float m_AbsorbTotal;
	static float m_fCapa;		//�ύڗʁ��G�l�~�[�����͕̂s���R
	static int m_nLoadingNum;	//���̑��U����Ă���̂�
	static int m_TotalSucksNum;	//�X�R�A�p�@1�Q�[���ŃI�u�W�F�N�g���������񂾐�
	CSound m_Sound;


	//�L���[�ɓ��������ɔ��˂ł���悤�ɂ��邽�߁�WindState��FireState�̗���
	static std::queue<EnemyPlayer*> m_FireQueue;
	//�������˗p�̗���
	static std::queue<EnemyPlayer*> m_LoadingQueue; 
	//�G�l�~�[���ė��p���邽�߂Ɏg��
	static std::queue<EnemyPlayer*> m_ReuseQueue;
	//���̃R���|�[�l���g��ێ����Ă��鑶�݂��鐔
	static int MyNum;
	int m_nReuseCnt;
	Features m_Features;
	Transform* m_Transform;

private:
	
	//�K�w�͖߂邱�Ƃ��Ȃ����ߎg�p
	//�R���W��������x���������������Ȃ��̂Ȃ������
	bool m_bEnd;
	HierarchyEnemyState *m_HierarchyState;	//�K�w
	EnemyState *m_State;					//���
};

