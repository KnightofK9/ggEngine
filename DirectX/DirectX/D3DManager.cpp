#include "D3DManager.h"
D3DManager::D3DManager(HWND hWnd, int width, int height, D3DCOLOR backgroundColor) {
	this->width = width;
	this->height = height;
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	this->backgroundColor = backgroundColor;
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	//d3dpp.Windowed = TRUE;
	//d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.Windowed = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferWidth = width;

	HRESULT result = d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);
	errorCheck(result, TEXT("D3DManager Constructor: Failed to create device!"));
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer);
	result = d3ddv->CreateOffscreenPlainSurface(
		100,
		100,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);
	errorCheck(result, TEXT("D3DManager Constructor: Failed to create off screen plain surface!"));

}

D3DManager::~D3DManager() {
	if (d3d != NULL) { d3d->Release(); d3d = NULL; }
	if (d3ddv != NULL) { d3ddv->Release(); d3ddv = NULL; }
}

void D3DManager::errorCheck(HRESULT result, LPCTSTR debugInfo) {
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

void D3DManager::update()
{
	clearScene();
	if (d3ddv->BeginScene()) {

		createRandomRect();

		//Draw Scene
		/*d3dpp.Windowed = FALSE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferHeight = 600;
		d3dpp.BackBufferWidth = 800;*/


		d3ddv->EndScene();
	}

	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void D3DManager::clearScene()
{
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, backgroundColor, 1.0f, 0);
}

void D3DManager::createRandomRect()
{
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;

	d3ddv->ColorFill(surface, NULL, D3DCOLOR_XRGB(r, g, b));

	RECT rect;

	rect.left = rand() % (width / 2);
	rect.top = rand() % (height / 2);
	rect.right = rect.left + rand() % (width / 2);
	rect.bottom = rect.top + rand() % (height / 2);
	d3ddv->StretchRect(
		surface,			// from 
		NULL,				// which portion?
		back_buffer,			// to 
		&rect,				// which portion?
		D3DTEXF_NONE);

	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;

	d3ddv->ColorFill(surface, NULL, D3DCOLOR_XRGB(r, g, b));

}
