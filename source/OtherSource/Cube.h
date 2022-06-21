//=======================================================================
// Cube.h
//-----------------------------------------------------------------------
// �쐬�� : �������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/16	���Ɠ��̂��R���|�[�l���g��
//			22	Transform���O����G���悤�ɕύX
//		 12/10	�e�N�X�`���\���悤�ɂ���			
//
//=======================================================================
#pragma once

//--- �C���N���[�h
#include "Object.h"
#include "DrawBuffer.h"

class Cube : public Component
{
public:
	Cube() {}
	~Cube() {}

	void Init() override;

	void Draw() override;
	void Draw(bool Line);

	void SetTexture(const char* FileName);

	Transform* m_Transform;

private:

	DrawBuffer m_Buffer;
	ID3D11ShaderResourceView* m_pTexture;
};
