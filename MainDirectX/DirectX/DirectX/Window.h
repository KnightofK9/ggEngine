#pragma once
#include <Windows.h>
class Window {
public:
	Window(WNDPROC messageHandler, LPCTSTR title, int x, int y, int width, int height);
	~Window();

	HWND getHandle() { return window; }
	void show() { ShowWindow(window, SW_SHOWDEFAULT); }
private:
	WNDCLASS windowClass;
	HWND window;
};