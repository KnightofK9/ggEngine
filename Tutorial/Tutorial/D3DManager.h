#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
class D3DManager {
public:
	//*** Constructor/Destructor ***
	D3DManager(HWND window, int width, int height);
	~D3DManager();

	//*** Accessors/Modifiers ***
	IDirect3DDevice9& getDevice() { return *device; }

	//*** Methods ***
	// This method returns if there's no errors, and throws an exception if there is.
	void errorCheck(HRESULT result, LPCTSTR debugInfo);

protected:
	//*** Fields ***
	IDirect3D9* context;
	IDirect3DDevice9* device;
	D3DPRESENT_PARAMETERS parameters;
};