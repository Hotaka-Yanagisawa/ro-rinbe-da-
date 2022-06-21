//--- �C���N���[�h
#include "Light.h"
#include "Main.h"
#include "Shader.h"
#include "Keyboard.h"

//==================================================
// ������
//==================================================
void Light::Init()
{
	m_Position = { 200, 200, -200 };

	m_ViewMatrix = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 0),
		DirectX::XMVectorSet(0, 0, 0, 0),
		DirectX::XMVectorSet(0, 1, 0, 0));
}

//==================================================
// �X�V
//==================================================
void Light::Update()
{
	//static float rad;
	//rad += 1.0f / 180.0f * 3.1415f;
	//m_Position.x = sin(rad) * 200.0f;
	//m_Position.z = cos(rad) * 200.0f;

	//SHADER->SetLightDir(DirectX::XMFLOAT4(-m_Position.x, -m_Position.y, -m_Position.z, 0));
}

//==================================================
// �r���[�s���Ԃ�
//==================================================
DirectX::XMMATRIX Light::GetView()
{
	return DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 0),
		DirectX::XMVectorSet(0, 0, 0, 0),
		DirectX::XMVectorSet(0, 1, 0, 0));
}
