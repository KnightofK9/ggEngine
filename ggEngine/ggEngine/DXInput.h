#pragma once
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

namespace ggEngine
{
	extern LPDIRECTINPUT8 dInput;
	extern LPDIRECTINPUTDEVICE8 diKeyboard;
	extern LPDIRECTINPUTDEVICE8 diMouse;
	extern DIMOUSESTATE mouseState;
	extern LPDIDEVICEOBJECTDATA keyEvents;
	int InitDXInput(HWND hWnd);
	void ShutDown();

	/// Keyboard
	int InitKeyboard(HWND hWnd);
	void PollKeyboard();
	int KeyDown(int keyCode);

	/// Mouse
	int InitMouse(HWND hWnd);
	void PollMouse();
	int MouseButtonPress(int mouseButton);
	int GetMouseX();
	int GetMouseY();
}
