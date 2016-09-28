#pragma once
#include <dinput.h>
#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button] & 0x80)
namespace ggEngine
{
	extern LPDIRECTINPUT8 dInput;
	extern LPDIRECTINPUTDEVICE8 diKeyboard;
	extern LPDIRECTINPUTDEVICE8 diMouse;
	extern DIMOUSESTATE mouseState;

	int InitDXInput(HWND);
	void ShutDown();

	/// Keyboard
	//void PollKeyBoard();
	int IsKeyDown(int keyCode);

	/// Mouse
	void Poll();
	int IsMouseButtonPress(int mouseButton);
	int GetMouseX();
	int GetMouseY();

}
