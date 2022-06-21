//=======================================================================
// Control.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/17	����Ă݂����č쐬
//			30	�ړ��������J�����̕�������ɂȂ�悤�Ƀv���O�����i����
//		/12/01	�Q�[���p�b�h�ƃL�[�{�[�h���͂ňړ��ł���悤�ɕύX (����
//		/01/08  �v���C���[�̖��@�w�isymbol�j�̈ڐA
//
//=======================================================================
#pragma once

//--- �C���N���[�h�@
#include "Component.h"
#include "Transform.h"
#include "Pol2D.h"

//--- �N���X
class Control : public Component
{
public:

	Control() {}
	~Control() {}

	void Init() override;
	void Uninit() override;

	void Update() override;
	void Draw() override;

private:

	Transform* m_Transform;
	Pol2D m_Symbol;

	Pol2D m_Aim;

};
