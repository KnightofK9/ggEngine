#pragma once
#include <Windows.h>
#include "ConstantEnum.h"
	class Window {
	public:
		Window(WNDPROC messageHandler, GGTEXT title, int x, int y, int width, int height);
		~Window();

		HWND getHandle() { return window; }
		void show() { ShowWindow(window, SW_SHOWDEFAULT); }
	private:
		WNDCLASS windowClass;
		HWND window;
	};
