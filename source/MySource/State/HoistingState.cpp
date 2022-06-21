#include "HoistingState.h"
#include "EnemyPlayer.h"
#include "SucksState.h"
#include "WindState.h"
#include "FireState.h"

void HoistingState::Init(EnemyPlayer *obj)
{
	ChangeState(obj, SucksState::GetInstance());
}

void HoistingState::Update(EnemyPlayer *obj)
{
	obj->GetState()->Update(obj, HoistingState::GetInstance());
}

void HoistingState::ChangeState(EnemyPlayer *obj, EnemyState *newState)
{
	obj->SetState(newState);
	obj->GetState()->Init(obj);
}

//�g���l�[�h�ƓG�Ƃ̔��a�̋����̐�Βl�����
//�ŏ��͔��a�����炷��������������]���Ĕ��a���炷�����a�O�ɂȂ����玟�̃X�e�[�g��
//���N���N����葱���遨����