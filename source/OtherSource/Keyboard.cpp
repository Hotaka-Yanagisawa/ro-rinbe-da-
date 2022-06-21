#include "Keyboard.h"

const int KEYTABLE_SIZE = 256;
const int KEY_REPEAT_TICK = 3;
const int KEY_REPEAT_WAIT = 25;

BYTE g_key[KEYTABLE_SIZE];
BYTE g_oldKey[KEYTABLE_SIZE];
BYTE g_repeatCount[KEYTABLE_SIZE];
BYTE g_force[KEYTABLE_SIZE];

HRESULT InitKeyboard()
{
	ZeroMemory(g_key, KEYTABLE_SIZE);
	ZeroMemory(g_oldKey, KEYTABLE_SIZE);
	ZeroMemory(g_repeatCount, KEYTABLE_SIZE);
	memset(g_force, 255, KEYTABLE_SIZE);
	return S_OK;
}
void UninitKeyboard()
{
}
void UpdateKeyboard()
{
	// ①メッセージに投げられた時の情報
	//SHORT key = GetKeyState(VK_RETURN);

	// ②関数呼び出し時の押し情報
	//key = GetAsyncKeyState(VK_RETURN);

	// ③関数呼び出し時の全情報
	memcpy(g_oldKey, g_key, sizeof(g_key));
	GetKeyboardState(g_key);
	for (int i = 0; i < KEYTABLE_SIZE; ++i)
	{
		if (g_force[i] != 255)
		{
			g_key[i] = g_force[i];
			g_force[i] = 255;
		}

		if (IsKeyPress(i))
		{
			if (g_repeatCount[i] <= KEY_REPEAT_WAIT)
			{
				++g_repeatCount[i];
			}
			else
			{
				g_repeatCount[i] -= KEY_REPEAT_TICK;
			}
		}
		else
		{
			g_repeatCount[i] = 0;
		}
	}
}
void DrawKeyboard()
{
}

void InstantForceInput(int nKey, bool bPress)
{
	g_force[nKey] = bPress ? 0x80 : 0;
}

bool IsKeyPress(int nKey)
{
	return g_key[nKey] & 0x80;
}
bool IsKeyTrigger(int nKey)
{
	return (g_key[nKey] ^ g_oldKey[nKey]) & g_key[nKey] & 0x80;
}
bool IsKeyRelease(int nKey)
{
	return (g_key[nKey] ^ g_oldKey[nKey]) & g_oldKey[nKey] & 0x80;
}
bool IsKeyRepeat(int nKey)
{
	return g_repeatCount[nKey] == 1 || g_repeatCount[nKey] >= KEY_REPEAT_WAIT;
}