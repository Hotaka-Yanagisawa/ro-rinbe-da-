//=======================================================================
// Fly.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/20	�쐬
//			23	�Ԃ�������h��鏈��
//			27	�e�̃e�N�X�`���`��
//		 12/16	Transform���p�u���b�N��
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Component.h"
#include "Transform.h"
#include "Texture.h"
#include "DrawBuffer.h"
#include "Vitality.h"
#include "MySound.h"

class Fly : public Component
{
public:
	Fly() {}
	~Fly() {}

	void Init() override;

	void Update() override;
	void Draw() override;

	void OnCollisionEnter(Object* pObj) override;

	Transform* m_Transform;
private:
	Vitality *m_Vitality;

	float m_fAngle;
	float m_fRadius;
	float m_nCount;
	bool m_bFlag;


	ID3D11ShaderResourceView* m_pTexture;

	DrawBuffer m_Buffer;
	CSound m_Sound;
	CSound m_SE;
};
