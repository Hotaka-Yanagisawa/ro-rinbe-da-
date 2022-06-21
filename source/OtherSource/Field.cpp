//--- インクルード
#include "Field.h"
#include "Object.h"
#include "SceneManager.h"

//==================================================
// 更新
//==================================================
void Field::Update()
{
	m_Transform = m_Parent->Get<Transform>();

}

//==================================================
// 描画
//==================================================
void Field::Draw()
{
	//float r = sqrt(rand()) * 0 + FIELD_RANGE;
	//float Angle = rand() * (3.141529f * 180.0f);

	//// エフェクト
	//static int time;
	//if(++time % 15 == 0)
	//	EFFECT.SetEffect({ cosf(Angle) * r, 0, sinf(Angle) * r }, KIND::CIRCLE);
}
