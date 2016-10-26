#include "Window.h"
#include <iostream>
#include "MyStackWalker.h"
namespace ggEngine {
	LONG WINAPI MyFilter(EXCEPTION_POINTERS * pExp/*ExceptionInfo*/)
	{
		std::cout << "An uncaught exception was detected!\n";
		MyStackWalker sw;
		sw.ShowCallstack(GetCurrentThread(), pExp->ContextRecord);
		return EXCEPTION_EXECUTE_HANDLER;
	}
	Window::Window(WNDPROC messageHandler, GGTEXT title, int x, int y, int width, int height)
	{
		windowClass.style = NULL;
		windowClass.lpfnWndProc = messageHandler;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.hIcon = NULL;
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground = (HBRUSH)BLACK_BRUSH;
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

		SetUnhandledExceptionFilter(MyFilter);
	}

	Window::~Window()
	{
		UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		if (window != NULL) { DestroyWindow(window); window = NULL; }
	}
}