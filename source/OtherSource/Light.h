//=======================================================================
// Light.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/01/02	Camera���R�s�[���č쐬	
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Transform.h"

//--- �}�N��
#define LIGHT	(Light::GetInstance())

//--- �N���X
class Light
{
public:
	inline static Light* GetInstance()
	{
		static Light instance;
		return &instance;
	}

	void Init();
	void Uninit() {}

	void Update();

	DirectX::XMMATRIX GetView();

private:
	DirectX::XMMATRIX m_ViewMatrix;

	Float3 m_Position;

	Light() {}
	~Light() {}
};
