#pragma once
#include <dinput.h>

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#define KEY_BUFFER_SIZE (int)1024

namespace ggEngine
{
	class Input
	{
	public:
		Input();
		Input(HWND hWnd, int screenWidth, int screenHeight);
		~Input();
		bool Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight);
		void ShutDown();
		bool Frame();

		void GetMouseLocation(int & mouseX, int & mouseY);

	private:
		HWND hWnd;
		LPDIRECTINPUT8 directInput;
		LPDIRECTINPUTDEVICE8 keyboard;
		LPDIRECTINPUTDEVICE8 mouse;

		char keyboardState[256];
		DIMOUSESTATE mouseState;
		int mouseX, mouseY;
		int screenWidth, screenHeight;

		DIDEVICEOBJECTDATA keyEvents[KEY_BUFFER_SIZE]; // Buffered keyboard data

		bool ReadKeyboard();
		bool ReadMouse();
		void ProcessInput();

		virtual void OnKeyDown(int keyCode);
		virtual void OnKeyUp(int keyCode);
	};

}