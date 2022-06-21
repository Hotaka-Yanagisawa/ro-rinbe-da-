#include "ReturnState.h"
#include "EnemyPlayer.h"
#include"../Transform.h"
#include "../Object.h"

void ReturnState::Init(EnemyPlayer *obj)
{
	obj->GetTransform()->Rotate = Float3(0, 0, 0);
	obj->GetTransform()->Move = Float3(0, 0, 0);
}

void ReturnState::Update(EnemyPlayer *obj, HierarchyEnemyState *parent)
{
	//�G���A��n�_�܂Ŗ߂鏈�����s��
	float sx = 0, sz = 0;
	//�_�a�ɍs���̌v�Z
	float Rad = atan2f(sz - obj->GetTransform()->Position.z, sx - obj->GetTransform()->Position.x);


	//*5�̂Ƃ���̓v���C���[��Move+1���炢�H
	obj->GetTransform()->Move.x = cosf(Rad) * 0.3f;
	obj->GetTransform()->Move.y = 0.0f;
	obj->GetTransform()->Move.z = sinf(Rad) * 0.3f;

	obj->m_Parent->Get<Transform>()->Rotate = Float3(0, 270 * 3.14f / 180.0f - Rad, 0);

	//���W�X�V
	obj->GetTransform()->Position -= obj->GetTransform()->Move;
}
