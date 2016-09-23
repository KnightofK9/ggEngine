#include "Window.h"

	Window::Window(WNDPROC messageHandler, GGTEXT title, int x, int y, int width, int height)
	{
		windowClass.style = NULL;
		windowClass.lpfnWndProc = messageHandler;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.hIcon = NULL;
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = title;
		RegisterClass(&windowClass);
		window = CreateWindow(
			windowClass.lpszClassName,
			title,
			//WS_OVERLAPPEDWINDOW,
			WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			x, y,
			width, height,
			GetDesktopWindow(),
			NULL,
			windowClass.hInstance,
			NULL);
		if (window == NULL) throw(TEXT("Window Constructor: Failed to creat a new window!"));
	}

	Window::~Window()
	{
		UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		if (window != NULL) { DestroyWindow(window);window = NULL; }
	}
