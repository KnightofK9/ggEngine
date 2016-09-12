#include "D3DManager.h"
// -------------------------------------------------
/* Constructor */
// -------------------------------------------------
D3DManager::D3DManager(HWND window, int width, int height) {
	// So let's start by initializing the direct3D context.
	context = Direct3DCreate9(D3D_SDK_VERSION);

	// Was it successful?
	if (context == NULL) throw(TEXT("D3DManager Constructor: Failed to create a Direct3D Context!"));
	// UINT BackBufferWidth & BackBufferHeight - The size of the drawing area.
	parameters.BackBufferWidth = width;
	parameters.BackBufferHeight = height;
	// D3DFORMAT BackBufferFormat - The colour format of the back buffer.
	parameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	// UINT BackBufferCount - The number of back buffers to use.
	parameters.BackBufferCount = 1;
	// D3DMULTISAMPLE_TYPE MultiSampleType - Sets the degree of anti-aliasing.
	parameters.MultiSampleType = D3DMULTISAMPLE_NONE;

	// DWORD MultiSampleQuality - The quality of anti-aliasing.
	parameters.MultiSampleQuality = 0;

	// D3DSWAPEFFECT SwapEffect - How D3D will deal with buffer swapping.
	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// HWND hDeviceWindow - What window to tie this device to
	parameters.hDeviceWindow = window;
	// BOOL Windowed - Whether to run in Windowed, or Full Screen mode.
	parameters.Windowed = true;

	// BOOL EnableAutoDepthStencil - Enable depth management.
	parameters.EnableAutoDepthStencil = true;

	// D3DFORMAT AutoDepthStencilFormat - What format to store depth info in.
	parameters.AutoDepthStencilFormat = D3DFMT_D16;
	// DWORD Flags - Extra settings and flags to control.
	parameters.Flags = NULL;
	// UINT FullScreen_RefreshRateInHz - The refresh rate to use when in full screen.
	parameters.FullScreen_RefreshRateInHz = 0;

	// UINT PresentationInterval - How often to redraw the screen.
	parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	HRESULT result = context->CreateDevice(
		// UINT adapter - Which adapter device to use.
		D3DADAPTER_DEFAULT,
		// D3DDEVTYPE DeviceType - What device to use to draw Direct3D.
		D3DDEVTYPE_HAL,
		// HWND hFocusWindow - The window to tie this device to.
		window,
		// DWORD BehaviourFlags - Extra flags and options you can use.
		D3DCREATE_MIXED_VERTEXPROCESSING,
		// D3DPRESENT_PARAMETERS* pPresentationParameters - Pointer to the Presentation Parameters to use.
		&parameters,
		// IDirect3DDevice9** ppReturnedDeviceInterface - Pointer to a Device pointer, used to return the new device.
		&device);
	// Now, our saved HRESULT will tell us if there are any problems.
	errorCheck(result, TEXT("D3DManager Constructor: Failed to create device!"));
}

D3DManager::~D3DManager() {
	// We just release the device and context we've set up, and set the pointers to null for good measure.
	if (device != NULL) { device->Release(); device = NULL; }
	if (context != NULL) { context->Release(); context = NULL; }
}

// -------------------------------------------------
/* public errorCheck */
// Checks the supplied HRESULT for any Direct3D errors, and throws an exception if one is found.
// -------------------------------------------------
void D3DManager::errorCheck(HRESULT result, LPCTSTR debugInfo) {
	// D3D_OK is the only accepted HRESULT. Everything else is a failure.
	if (result == D3D_OK) return;

	LPTSTR text;
	if (result == D3DERR_INVALIDCALL) text = TEXT("D3DERR_INVALIDCALL: Invalid Call or Parameter!");
	else if (result == D3DERR_NOTAVAILABLE) text = TEXT("D3DERR_NOTAVAILABLE: Parameter not supported!");
	else if (result == D3DERR_OUTOFVIDEOMEMORY) text = TEXT("D3DERR_OUTOFVIDEOMEMORY: Out of Video Memory!");
	else {
		text = new TCHAR[128];
		wsprintf(text, TEXT("Unknown Error: %X"), result);
	}

	LPTSTR error = new TCHAR[256];
	wsprintf(error, TEXT("%s\r\n%s"), debugInfo, text);
	throw(error);
}