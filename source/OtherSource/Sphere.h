//=======================================================================
// Sphere.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/21	�`�悾������
//			26	UV���]�ł���悤��
//	2021/01/09	�[�x�N���b�v�I�t
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Object.h"
#include "DrawBuffer.h"

class Sphere : public Component
{
public:
	Sphere() {}
	~Sphere() {}

	void Init() override;

	void Draw() override;

private:
	Transform* m_Transform;

	DrawBuffer m_Buffer;

	ID3D11ShaderResourceView* m_pTexture;
};
