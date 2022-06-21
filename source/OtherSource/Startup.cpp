#include "Defines.h"
#include "Main.h"
#include "Controller.h"
#include <stdio.h>
#include <crtdbg.h>

// timeGetTime周りの使用
#pragma comment(lib, "winmm.lib")

//--- プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//--- エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//--- 変数宣言
	// ウィンドウクラス情報を
	// 設定する構造体
	WNDCLASSEX wcex;
	// 作成したウィンドウのハンドル
	HWND hWnd;
	MSG message;

	// ウィンドクラス情報の設定
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

	// ウィンドウクラス情報の登録
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Failed to RegisterClassEx", "Error", MB_OK);
		return 0;
	}

	// ウィンドウの作成
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		wcex.lpszClassName,
		"タイトル",
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
	);

	// ウィンドウの表示
	ShowWindow(
		hWnd,
		nCmdShow
	);
	// ウィンドウの中身をリフレッシュ
	UpdateWindow(hWnd);

	// 初期化処理
	Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	timeBeginPeriod(1);

	// FPS制御の初期化
	int fpsCount = 0;
	DWORD countStartTime = timeGetTime();
	DWORD preExecTime = countStartTime;

	// ウィンドウの管理
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
			// FPSの制御
			DWORD nowTime = timeGetTime(); // 現在時刻
			if (nowTime - countStartTime >= 1000)
			{
				char fpsText[20];
				sprintf(fpsText, "ローリンベーダー");
				SetWindowText(hWnd, fpsText);

				countStartTime = nowTime;
				fpsCount = 0;
			}

			// ゲームの処理
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

	// 終了処理
	timeEndPeriod(1);
	Uninit();
	UnregisterClass(
		wcex.lpszClassName,
		hInstance
	);

	return 0;
}

// ウィンドウプロシージャ
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