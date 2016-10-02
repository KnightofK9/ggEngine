#pragma once
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#define KEY_BUFFER_SIZE 1024

namespace ggEngine
{
	class Input
	{
	protected:
		LPDIRECTINPUT8 dInput;
		LPDIRECTINPUTDEVICE8 diKeyboard;
		LPDIRECTINPUTDEVICE8 diMouse;
		DIMOUSESTATE mouseState;
		LPDIDEVICEOBJECTDATA keyEvents;

	public:
		char keyStates[256]; // keyboard state buffer
		Input(HWND *hWnd);
		HWND *hWnd;
		~Input();
		/// Keyboard
		int InitKeyboard();
		void PollKeyboard();
		int KeyDown(int keyCode);

		/// Mouse
		int InitMouse();
		void PollMouse();
		int MouseButtonPress(int mouseButton);
		int GetMouseX() { return mouseState.lX; }
		int GetMouseY() { return mouseState.lY; }
	};
}