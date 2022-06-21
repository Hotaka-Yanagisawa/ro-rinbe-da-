//--- �C���N���[�h
#include "Main.h"
#include "DirectX.h"
#include "Shader.h"
#include "Defines.h"
#include "FBX/FBXLoader.h"
#include "SceneManager.h"
#include "Keyboard.h"
#include "Controller.h"
#include "MySound.h"

HRESULT ErrorBox(HRESULT hr, const char* message)
{
	MessageBox(NULL, message, "Error", MB_OK);
	return hr;
}

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	// fbxsdk�̏�����
	ggfbx::Initialize();
	// DirectX
	hr = GET_DX->Init(hWnd, width, height);
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to DirectX."); }
	// �T�E���h
	hr = CSound::InitSound();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Sound."); }
	// �L�[�{�[�h
	hr = InitKeyboard();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Keyboard."); }
	// �V�F�[�_
	hr = SHADER->Init();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Shader."); }
	TEXTURE->Init();

	// �����V�[��
	SceneManager::GetInstance()->Init(SCENE::TITLE);

	return hr;
}

void Uninit()
{
	SceneManager::GetInstance()->Uninit();

	TEXTURE->Uninit();
	SHADER->Uninit();
	UninitKeyboard();
	CSound::UninitSound();
	GET_DX->Uninit();
	ggfbx::Terminate();
}

void Update()
{
	UpdateKeyboard();
	PAD->Update();

	SceneManager::GetInstance()->Update();
}

void Draw()
{
	CDirectX* pDX = GET_DX;
	if (pDX->IsStandby()) return;

	pDX->SetViewport(0);
	pDX->ClearRenderTarget();

	SHADER->Bind(VS_WORLD, PS_LAMBERT);
	CAMERA->Bind();

	SceneManager::GetInstance()->Draw();

	DrawKeyboard();

	pDX->DrawBuffer();
}
