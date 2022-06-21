#include "Defines.h"
#include "Main.h"
#include "Controller.h"
#include <stdio.h>
#include <crtdbg.h>

// timeGetTime����̎g�p
#pragma comment(lib, "winmm.lib")

//--- �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//--- �G���g���|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//--- �ϐ��錾
	// �E�B���h�E�N���X����
	// �ݒ肷��\����
	WNDCLASSEX wcex;
	// �쐬�����E�B���h�E�̃n���h��
	HWND hWnd;
	MSG message;

	// �E�B���h�N���X���̐ݒ�
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.hInstance = hInstance;
	wcex.lpszClassName = "Class Name";
	wcex.lpfnWndProc = WndProc;
	wcex.style = CS_CLASSDC;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// �E�B���h�E�N���X���̓o�^
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Failed to RegisterClassEx", "Error", MB_OK);
		return 0;
	}

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		wcex.lpszClassName,
		"�^�C�g��",
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
	);

	// �E�B���h�E�̕\��
	ShowWindow(
		hWnd,
		nCmdShow
	);
	// �E�B���h�E�̒��g�����t���b�V��
	UpdateWindow(hWnd);

	// ����������
	Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	timeBeginPeriod(1);

	// FPS����̏�����
	int fpsCount = 0;
	DWORD countStartTime = timeGetTime();
	DWORD preExecTime = countStartTime;

	// �E�B���h�E�̊Ǘ�
	while (1)
	{
		if (PeekMessage(
			&message, NULL, 0, 0,
			PM_NOREMOVE))
		{
			if (!GetMessage(&message,
				NULL, 0, 0))
			{
				break;
			}
			else
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			// FPS�̐���
			DWORD nowTime = timeGetTime(); // ���ݎ���
			if (nowTime - countStartTime >= 1000)
			{
				char fpsText[20];
				sprintf(fpsText, "���[�����x�[�_�[");
				SetWindowText(hWnd, fpsText);

				countStartTime = nowTime;
				fpsCount = 0;
			}

			// �Q�[���̏���
			if (nowTime - preExecTime >= 1000 / 60)
			{

				Update();
				if (PAD->IsButtonsTrigger(XINPUT_GAMEPAD_BACK))
				{
					PostQuitMessage(0);
					DestroyWindow(hWnd);
				}
				Draw();
				fpsCount++;
				preExecTime = nowTime;
			}
		}
	}

	// �I������
	timeEndPeriod(1);
	Uninit();
	UnregisterClass(
		wcex.lpszClassName,
		hInstance
	);

	return 0;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		default: break;
		}
		break;
	}


	return DefWindowProc(hWnd, message, wParam, lParam);
}