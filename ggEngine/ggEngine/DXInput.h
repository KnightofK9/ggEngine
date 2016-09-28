#pragma once
#include <dinput.h>
#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button] & 0x80)
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
	int KeyDown(int keyCode);
	//void OnKeyDown(int keyCode);
	//void OnkeyUp(int keyCode);

	/// Mouse
	void Poll();
	int MouseButtonPress(int mouseButton);
	int GetMouseX();
	int GetMouseY();

}
