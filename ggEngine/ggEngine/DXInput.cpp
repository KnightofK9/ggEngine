#include "DXInput.h"
#include "Debug.h"
#include <string>
#define KEY_BUFFER_SIZE 1024

namespace ggEngine
{
	LPDIRECTINPUT8 dInput;
	LPDIRECTINPUTDEVICE8 diKeyboard;
	LPDIRECTINPUTDEVICE8 diMouse;
	DIMOUSESTATE mouseState;

	char keyStates[256]; // keyboard state buffer

	int InitDXInput(HWND hWnd)
	{
		HRESULT result = DirectInput8Create
		(
			GetModuleHandle(NULL),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&dInput,
			NULL
		);

		if (FAILED(result))
			return 0;

		// Init Keyboard
		result = dInput->CreateDevice(GUID_SysKeyboard, &diKeyboard, NULL);
		if (FAILED(result))
			return 0;
		result = diKeyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(result))
			return 0;
		result = diKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(result))
			return 0;
		result = diKeyboard->Acquire();
		if (FAILED(result))
			return 0;

		// Init mouse
		result = dInput->CreateDevice(GUID_SysMouse, &diMouse, NULL);
		if (FAILED(result))
			return 0;
		result = diMouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(result))
			return 0;
		result = diMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result))
			return 0;
		result = diMouse->Acquire();
		if (FAILED(result))
			return 0;

		return 1;
	}

	int KeyDown(int keyCode)
	{
		int keyDown = keyStates[keyCode] & 0x80;
		if (keyDown != 0)
			Debug::Log("Virtual key code: " + std::to_string(keyDown));

		return keyStates[keyCode] & 0x80;
	}

	int GetMouseX() { return mouseState.lX; }
	int GetMouseY() { return mouseState.lY; }

	int MouseButtonPress(int mousebutton)
	{
		int button = mouseState.rgbButtons[mousebutton] & 0x80;
		if (button != 0)
		{
			Debug::Log("Mouse button is pressed");
			Debug::Log("Virtual mouse state: " + std::to_string(button));
			Debug::Log(std::to_string(GetMouseX()) + ", " + std::to_string(GetMouseY()));
		}

		return mouseState.rgbButtons[mousebutton] & 0x80;
	}

	void Poll()
	{
		HRESULT result;
		/// Poll keyboard
		result = diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
		if (FAILED(result))
		{
			diKeyboard->Acquire();
			diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
		}

		/// Poll mouse
		result = diMouse->GetDeviceState(sizeof(mouseState), (LPVOID)& mouseState);
		if (FAILED(result))
		{
			diMouse->Acquire();
			diMouse->GetDeviceState(sizeof(mouseState), (LPVOID)& mouseState);
		}
	}

	//void PollKeyboard(HWND hWnd)
	//{
	//	HRESULT result;
	//	/// Poll keyboard
	//	result = diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
	//	if (FAILED(result))
	//	{
	//		diKeyboard->Acquire();
	//		diKeyboard->GetDeviceState(sizeof(keyStates), (LPVOID)& keyStates);
	//	}
	//	if (IsKeyDown(DIK_ESCAPE))
	//	{
	//		PostMessage(hWnd, WM_QUIT, 0, 0);
	//	}

	//	DWORD dwElements = KEY_BUFFER_SIZE;
	//	result = diKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);

	//	// Scan through all data, check if the key is pressed or released
	//	/*for (DWORD i = 0; i < dwElements; i++)
	//	{
	//		int KeyCode = keyEvents[i].dwOfs;
	//		int KeyState = _KeyEvents[i].dwData;
	//		if ((KeyState & 0x80) > 0)
	//			OnKeyDown(KeyCode);
	//		else
	//			OnKeyUp(KeyCode);*/
	//}

	void ShutDown()
	{
		if (diKeyboard != NULL)
		{
			diKeyboard->Unacquire();
			diKeyboard->Release();
			diKeyboard = NULL;
		}
		if (diMouse != NULL)
		{
			diMouse->Unacquire();
			diMouse->Release();
			diMouse = NULL;
		}
	}
}