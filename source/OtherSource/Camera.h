//=======================================================================
// Camera.h
//-----------------------------------------------------------------------
// �쐬�� : �������, ��������
//-----------------------------------------------------------------------
// �X�V����
//	2020/11/18	���Ɠ��̂���������
//			19	�V���O���g��
//			2X	���R�ɑ���ł���悤�ɕύX
//			28	���s���e
//	2020/12/02	�����ɃQ�[���p�b�h�E�X�e�B�b�N�ɂ��J����������\�ɁB(����
//			03  �v���C���[�̔w��Ɏ��_���ړ�����@�\�������B
//			04	late��move��position���w�b�_�[�ɒǉ�
//				���X�^�[�g���ɃJ�����̎��_�����Z�b�g����悤�Ɏ����BReset�֐�����
//			
//=======================================================================
#pragma once

//--- �C���N���[�h
#include <DirectXMath.h>
#include "Object.h"
#include "Transform.h"
#include "State/CameraState.h"

//--- �}�N��
#define CAMERA	(Camera::GetInstance())

//--- �N���X
class Camera
{
public:
	inline static Camera* GetInstance()
	{
		static Camera instance;
		return &instance;
	}

	void Init();
	void Uninit();
	void Update();

	void Bind(bool Parallel = false);

	void SetObject(Object*);

	DirectX::XMMATRIX m_ViewMatrix;

	// XZ����ł̊p�x(0����-Z�̈ʒu)
	float m_xzAngle;

	Float3 m_Position;
	Float3 m_LatePosition;
	Float3 m_Look;
	Float3 m_LateLook;
	Float3 m_Up;

	float m_Angle;
	float m_Near;
	float m_Far;

	// Y����ł̊p�x
	float m_yAngle;
	// ���S����̋���
	float m_radius;

	Object* m_pTarget;

	CameraState *m_State;

	DirectX::XMMATRIX TransWVP(DirectX::XMMATRIX);

private:


	Camera() {}
	~Camera() {}
};
