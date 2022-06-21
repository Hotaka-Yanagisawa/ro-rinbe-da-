#include "MoveState.h"
#include "EnemyPlayer.h"
#include"../Transform.h"
#include "../Object.h"

void MoveState::Init(EnemyPlayer *obj)
{
	//���͂Ƃ肠�������_�Ɍ����Ĉړ�
	obj->GetTransform()->Rotate = Float3(0, 0, 0);
	obj->GetTransform()->Move = Float3(0, 0, 0);
}

void MoveState::Update(EnemyPlayer *obj, HierarchyEnemyState * parent)
{
	//obj->GetTransform()->Position
	//�����ŃI�u�W�F�N�g���Ƃɏ����ʒu�����炷
	//float randNumX = (rand() % 100) - 50;
	//float randNumY = (rand() % 100) - 50;
	//�v���C���[���W�̑���Ƃ肠�������_
	//�v���C���[���W���擾�o�����璼��
	float sx = 0, sz = 0;
	//�_�a�ɍs���̌v�Z
	float Rad = atan2f(sz - obj->GetTransform()->Position.z, sx - obj->GetTransform()->Position.x);
	
	//*5�̂Ƃ���̓v���C���[��Move+1���炢�H
	obj->GetTransform()->Move.x = cosf(Rad) * 0.1f;
	obj->GetTransform()->Move.y = 0.0f;
	obj->GetTransform()->Move.z = sinf(Rad) * 0.1f;

	obj->m_Parent->Get<Transform>()->Rotate = Float3(0, 90 * 3.14f / 180.0f - Rad, 0);

	//���W�X�V
	obj->GetTransform()->Position += obj->GetTransform()->Move;
}
