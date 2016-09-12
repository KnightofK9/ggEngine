#include "Window.h"
#include "D3DManager.h"
//*** Fields ***
Window* window; // Our crappy little window.
D3DManager* d3dManager; // Our new Direct3D manager, which we'll use on the window.
//*** Method Declarations ***
void cleanup();
void quitWithError(LPCTSTR error);
void programLoop();
LRESULT CALLBACK messageHandler(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

// -------------------------------------------------
/* Main Method */
// -------------------------------------------------
int main() {
	try {
		window = new Window(messageHandler, TEXT("Tutorial 1 - My Crappy Window!"), 100, 100, 600, 600);
		// Okay, now that the window is ready, we can create a direct3D manager.
		d3dManager = new D3DManager(window->getHandle(), 600, 600);
	}
	catch (LPCTSTR error) {
		// If there was an error, we'll call our quitWithError method to show the error,
		// cleanup gracefully, then quit.
		quitWithError(error);
	}

	// Show the window, then begin the program loop.
	window->show();
	programLoop();

	// Once that method returns, we know we're done. So cleanup before we exit.
	cleanup();

	// To state a successful run of the program, we return EXIT_SUCCESS.
	return EXIT_SUCCESS;
}

// -------------------------------------------------
/* cleanup */
// Clear all references in memory before we quit.
// -------------------------------------------------
void cleanup() {
	if (window != NULL) { delete window; window = NULL; }
	if (d3dManager != NULL) { delete d3dManager; d3dManager = NULL; }
}
// -------------------------------------------------
/* quitWithError */
// Shows an error message that was caught, cleans up, and quits the program.
// -------------------------------------------------
void quitWithError(LPCTSTR error) {
	// We'll use MessageBox to show the error to the screen.
	HWND parentWindow = NULL;
	if (window != NULL) parentWindow = window->getHandle();
	MessageBox(parentWindow, error, TEXT("Runtime Error!"), MB_OK | MB_ICONERROR);

	// Even though we're quitting on a failure, that's no reason to avoid cleaning up after
	// ourselves.
	cleanup();

	// Finally, force an exit with the Failure exit code.
	exit(EXIT_FAILURE);
}
// -------------------------------------------------
/* programLoop */
// This is what the program will do in idle time.
// -------------------------------------------------
void programLoop() {
	// So, let's process those messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); // Just incase there's something there.

	// Basically, we loop as long as we don't get the QUIT message.
	while (msg.message != WM_QUIT) {
		// Are there any messages waiting to be processed?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Translate it and send it off for processing.
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
//-----------------------------------------------------------------------------
/* messageHandler */
// This will manage incoming messages from the window.
//-----------------------------------------------------------------------------
LRESULT CALLBACK messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return 0;
	}

	// If we don't catch it, let the default message handler get it. That's this function.
	return DefWindowProc(hwnd, msg, wParam, lParam);
}