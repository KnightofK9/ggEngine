#include "Window.h"
#include "D3DManager.h"
#include "CustomVertexFormats.h" // So we can use our new vertex format.
//*** Fields ***
Window* window; // Our crappy little window.
D3DManager* d3dManager; // Our new Direct3D manager, which we'll use on the window.
TransformedColouredVertex vertices[] = {
		{ 300.0f, 75.0f, 0.0f, 1.0f, 0xffff0000 },
		{ 525.0f, 525.0f, 0.0f, 1.0f, 0xff00ff00 },
		{ 75.0f, 525.0f, 0.0f, 1.0f, 0xff0000ff }
};
//*** Method Declarations ***
void cleanup();
void quitWithError(LPCTSTR error);
void programLoop();
// This method will prepare for drawing, and when ready call the render method.
void prepareForDrawing();

// This method will draw our triangle for us.
void render();

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
	// One more important step: Direct3D needs to know what vertex format we've chosen.
	d3dManager->getDevice().SetFVF(vertices[0].FORMAT);


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
		else prepareForDrawing();
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

// -------------------------------------------------
/* prepareForDrawing */
// This will clear the background, and prepare for drawing the scene.
// -------------------------------------------------
void prepareForDrawing() {
	d3dManager->getDevice().Clear(
		// DWORD Count - Number of rectangles to clear.
		0,
		// const D3DRECT* pRects - The rectangles to clear.
		NULL,
		// DWORD Flags - Special flags to use when clearing.
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		// D3DCOLOR Color - The colour to clear the target back buffer to.
		0x00000000,
		// float Z - What value to clear the zbuffer to.
		1.0f,
		// DWORD Stencil - What value to clear the stencil buffer to.
		0);
	d3dManager->getDevice().BeginScene();
	render();
	d3dManager->getDevice().EndScene();
	d3dManager->getDevice().Present(NULL, NULL, NULL, NULL);
}


// -------------------------------------------------
/* render */
// This will render the scene.
// -------------------------------------------------
void render() {
	d3dManager->getDevice().DrawPrimitiveUP(
		// D3DPRIMITIVETYPE PrimitiveType - What primitive type to use.
		D3DPT_TRIANGLELIST,
		// UINT PrimitiveCount - How many primitives to draw.
		1,
		// const void* pVertexStreamZeroData - The vertices to use to draw this primitive.
		vertices,
		// UINT VertexStreamZeroStride - How large, in bytes, a single vertex is.
		vertices[0].STRIDE_SIZE);
}