//--- �C���N���[�h
#include "Field.h"
#include "Object.h"
#include "SceneManager.h"

//==================================================
// �X�V
//==================================================
void Field::Update()
{
	m_Transform = m_Parent->Get<Transform>();

}

//==================================================
// �`��
//==================================================
void Field::Draw()
{
	//float r = sqrt(rand()) * 0 + FIELD_RANGE;
	//float Angle = rand() * (3.141529f * 180.0f);

	//// �G�t�F�N�g
	//static int time;
	//if(++time % 15 == 0)
	//	EFFECT.SetEffect({ cosf(Angle) * r, 0, sinf(Angle) * r }, KIND::CIRCLE);
}
