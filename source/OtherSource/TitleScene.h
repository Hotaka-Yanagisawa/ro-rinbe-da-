//=======================================================================
// TitleScene.h
//-----------------------------------------------------------------------
// �쐬�� : ���c���
//-----------------------------------------------------------------------
// �X�V����
//	2020/12/01	�쐬
//			10	PUSHENTER
//			23	�w�i�X�N���[��
//
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Scene.h"
#include "PolygonList.h"
#include "MySound.h"

//--- �N���X
class TitleScene : public Scene
{
public:
	TitleScene() {}
	~TitleScene() {}

	void Init() override;
	void Uninit() override;

	SCENE::TYPE Update() override;
	void Draw() override;

private:
	CSound m_Sound;
	CSound m_SE;
	PolygonList m_PolList;

	//----------------
	float m_timer;
	//--------------
	bool m_Color;
	float m_ColorA;
	bool m_AlphaFlag;

	//--------------
	float m_RogoRadian;//�p�x
	float m_RogoRadius;//���a

	bool m_RogoFlag;

};
