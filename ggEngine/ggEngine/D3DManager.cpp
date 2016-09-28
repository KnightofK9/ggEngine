#include "D3DManager.h"
#include <iostream>
#include "State.h"
namespace ggEngine {
	D3DManager::D3DManager(HWND hWnd, int width, int height, D3DCOLOR backgroundColor, bool isWindowed) {
		this->width = width;
		this->height = height;
		d3d = Direct3DCreate9(D3D_SDK_VERSION);
		this->backgroundColor = backgroundColor;
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		//d3dpp.Windowed = TRUE;
		//d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		if(isWindowed) d3dpp.Windowed = TRUE;
		else d3dpp.Windowed = FALSE;
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
		this->drawManager = NULL;

	}

	D3DManager::~D3DManager() 
	{
		Destroy();
	}

	void D3DManager::Destroy()
	{
		if (d3d != NULL) { d3d->Release(); d3d = NULL; }
		if (d3ddv != NULL) { d3ddv->Release(); d3ddv = NULL; }
	}

	void D3DManager::errorCheck(HRESULT result, LPCTSTR debugInfo) {
		if (result == D3D_OK) return;
		int errorCode = ERROR_CODE_UNKNOWN;
		if (result == D3DERR_INVALIDCALL) errorCode = ERROR_CODE_D3DERR_INVALIDCALL;
		else if (result == D3DERR_NOTAVAILABLE) errorCode = ERROR_CODE_D3DERR_NOTAVAILABLE;
		else if (result == D3DERR_OUTOFVIDEOMEMORY) errorCode = ERROR_CODE_D3DERR_OUTOFVIDEOMEMORY;
		throw errorCode;
	}

	void D3DManager::clearScene()
	{
		d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, backgroundColor, 1.0f, 0);
	}

	void D3DManager::update()
	{
		clearScene();
		
		d3ddv->BeginScene();
		this->stateManager->GetCurrentState()->PreRender();
		drawManager->Render2D();
		this->stateManager->GetCurrentState()->Render();
		d3ddv->EndScene();
		
		d3ddv->Present(NULL, NULL, NULL, NULL);
	}



}