#include "Input.h"

namespace ggEngine
{
	Input::Input()
	{
		directInput = 0;
		keyboard = 0;
		mouse = 0;
	}

	Input::Input(HWND hWnd, int screenWidth, int screenHeight)
	{
		HRESULT result;
		this->hWnd = hWnd;
		this->screenHeight = screenHeight;
		this->screenWidth = screenWidth;

		mouseX = mouseY = 0;

		result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL);
		if (FAILED(result))
		{
			return;
		}

		// Init Keyboard
		result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
		if (FAILED(result))
		{
			return;
		}
		result = keyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(result))
		{
			return;
		}
		result = keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(result))
		{
			return;
		}
		result = keyboard->Acquire();
		if (FAILED(result))
		{
			return;
		}

		// Init mouse
		result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
		if (FAILED(result))
		{
			return;
		}
		result = mouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(result))
		{
			return;
		}
		result = mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result))
		{
			false;
		}
		result = mouse->Acquire();
		if (FAILED(result))
		{
			return;
		}
	}

	Input::~Input()
	{
		if (!directInput)
		{
			directInput->Release();
			directInput = NULL;
		}
		if (!keyboard)
		{
			keyboard->Unacquire();
			keyboard->Release();
			keyboard = NULL;
		}
		if (!mouse)
		{
			mouse->Unacquire();
			mouse->Release();
			mouse = NULL;
		}
	}

	bool Input::Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight)
	{
		HRESULT result;
		this->screenHeight = screenHeight;
		this->screenWidth = screenWidth;

		mouseX = mouseY = 0;

		result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL);
		if (FAILED(result))
		{
			return false;
		}

		// Init Keyboard
		result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
		if (FAILED(result))
		{
			return false;
		}
		result = keyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(result))
		{
			return false;
		}
		result = keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(result))
		{
			return false;
		}
		result = keyboard->Acquire();
		if (FAILED(result))
		{
			return false;
		}

		// Init mouse
		result = directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
		if (FAILED(result))
		{
			return false;
		}
		result = mouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(result))
		{
			return false;
		}
		result = mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result))
		{
			false;
		}
		result = mouse->Acquire();
		if (FAILED(result))
		{
			return false;
		}
		return true;
	}

	void Input::ShutDown()
	{
		
	}

	bool Input::Frame()
	{
		bool result;

		// Read current state of keyboard
		result = ReadKeyboard();
		if (!result)
		{
			return false;
		}

		// Read current state of mouse
		result = ReadMouse();
		if (!result)
		{
			return false;
		}

		ProcessInput();
		return true;
	}

	bool Input::ReadKeyboard()
	{
		HRESULT result;
		result = keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);
		if (FAILED(result))
		{
			// if lost focus, try to get control back
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				keyboard->Acquire();
			}
		}
		if (keyboardState[DIK_ESCAPE])
		{
			PostMessage(hWnd, WM_QUIT, 0, 0);
		}

		DWORD dwElements = KEY_BUFFER_SIZE;
		result = keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
		// Scan through all data, check if the key is pressed or released
		for (DWORD i = 0; i < dwElements; i++)
		{
			int keyCode = keyEvents[i].dwOfs;
			int keyState = keyEvents[i].dwData;
			if ((keyState & 0x80) > 0)
				OnKeyDown(keyCode);
			else
				OnKeyUp(keyCode);
		}
		return true;
	}

	bool Input::ReadMouse()
	{
		HRESULT result;
		result = mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
		if (FAILED(result))
		{
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				mouse->Acquire();
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	void Input::ProcessInput()
	{
		// update mouse location
		mouseX += mouseState.lX;
		mouseY += mouseState.lY;

		if (mouseX < 0) { mouseX = 0; }
		if (mouseY < 0) { mouseY = 0; }

		if (mouseX > screenWidth) { mouseX = screenWidth; }
		if (mouseY > screenHeight) { mouseY = screenHeight; }
	}

	void Input::OnKeyDown(int keyCode){	}

	void Input::OnKeyUp(int keyCode){ }

	void Input::GetMouseLocation(int & mouseX, int & mouseY)
	{
		mouseX = this->mouseX;
		mouseY = this->mouseY;
	}
}