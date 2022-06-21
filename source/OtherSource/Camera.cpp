//--- �C���N���[�h
#include "Camera.h"
#include "Shader.h"
#include "Defines.h"
#include "SceneManager.h"

#include "Keyboard.h"
#include "Controller.h"
#include "Control.h"
#include "State/SelectSceneState.h"

//==================================================
// ������
//==================================================
void Camera::Init()
{
	m_State = SelectSceneState::GetInstance();
	m_State->Init(this);
}

//==================================================
// �I��
//==================================================
void Camera::Uninit()
{
}

//==================================================
// �X�V
//==================================================
void Camera::Update()
{
	m_State->Update(this);
}

//==================================================
// �J�����Z�b�g
//--------------------------------------------------
// ����		: true�ŕ��s���e(�f�t�H���g��false)
//==================================================
void Camera::Bind(bool Parallel)
{
	// ���e���@
	if (Parallel)	// ���s
	{
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(0, 0, -1, 0),
			DirectX::XMVectorSet(0, 0, 0, 0),
			DirectX::XMVectorSet(0, 1, 0, 0));
		SHADER->SetView(m_ViewMatrix);

		SHADER->SetProjection(
			DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, m_Near, m_Far));

		GET_DX->SetRenderTarget(false);
	}
	else			// ����
	{
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_LatePosition.x, m_LatePosition.y, m_LatePosition.z, 0),
			DirectX::XMVectorSet(m_LateLook.x, m_LateLook.y, m_LateLook.z, 0),
			DirectX::XMVectorSet(m_Up.x, m_Up.y, m_Up.z, 0));
		SHADER->SetView(m_ViewMatrix);

		SHADER->SetProjection(
			DirectX::XMMatrixPerspectiveFovLH(m_Angle * 3.141592f / 180.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, m_Near, m_Far));

		// �J�����̍��W���V�F�[�_�ɐݒ�
		SHADER->SetPSCameraPos(m_Position.DXFloat3());

		GET_DX->SetRenderTarget(true);
	}
}

//==================================================
// �ǐՑΏۓo�^
//--------------------------------------------------
// ���� 	: �I�u�W�F�N�g�̃A�h���X
//==================================================
void Camera::SetObject(Object *pObj)
{
	m_pTarget = pObj;
}

//==================================================
// �s��ϊ��@�i��ʏ�̍s��Ɂj
//--------------------------------------------------
// ���� 	: �s��
// �߂�l	: �s��
//==================================================
DirectX::XMMATRIX Camera::TransWVP(DirectX::XMMATRIX matrix)
{
	DirectX::XMMATRIX WVP = matrix;

	WVP *= m_ViewMatrix;
	WVP *= DirectX::XMMatrixPerspectiveFovLH(
		m_Angle * 3.141592f / 180.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, m_Near, m_Far);

	DirectX::XMFLOAT4X4 wvp;
	DirectX::XMStoreFloat4x4(&wvp, WVP);

	wvp._41 /= wvp._43;
	wvp._42 /= wvp._43;
	wvp._43 /= wvp._43;

	WVP = DirectX::XMLoadFloat4x4(&wvp);

	float w = SCREEN_WIDTH / 2;
	float h = SCREEN_HEIGHT / 2;
	WVP *= DirectX::XMMATRIX(
		w, 0, 0, w,
		0, h, 0, h,
		0, 0, 1, 0,
		0, 0, 0, 1);

	return WVP;
}

