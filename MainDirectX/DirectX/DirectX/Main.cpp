#include "Window.h"
//Field
Window *window;
//Method declarations
void cleanup();
void quitWithError(LPCTSTR error);
void programLoop();
LRESULT CALLBACK messageHandler(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
int main() {
	try {
		window = new Window(messageHandler, TEXT("Tutorial 1 - My Crappy Window!"), 100, 100, 600, 600);
	}
	catch (LPCTSTR error) {
		quitWithError(error);
	}

	window->show();
	programLoop();
	cleanup();

	return EXIT_SUCCESS;
}
void cleanup() {
	if (window != NULL) { delete window; window = NULL; }
}
void quitWithError(LPCTSTR error) {
	HWND parentWindow = NULL;
	if (window != NULL) parentWindow = window->getHandle();
	MessageBox(parentWindow, error, TEXT("Runtime Error!"), MB_OK | MB_ICONERROR);

	cleanup();

	exit(EXIT_FAILURE);
}

void programLoop() {
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); 

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
