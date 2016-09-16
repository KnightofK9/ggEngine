#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
class D3DManager {
public:
	D3DManager(HWND window, int width, int height, D3DCOLOR backgroundColor);
	~D3DManager();

	IDirect3DDevice9& getDevice() { return *d3ddv; }
	IDirect3D9 &getContext() { return *d3d; }
	void errorCheck(HRESULT result, LPCTSTR debugInfo);
	void update();
	void clearScene();
	void createRandomRect();
protected:
	IDirect3D9* d3d;
	IDirect3DDevice9* d3ddv;
	D3DPRESENT_PARAMETERS  d3dpp;
	D3DCOLOR backgroundColor;
	LPDIRECT3DSURFACE9 back_buffer = NULL;
	LPDIRECT3DSURFACE9 surface = NULL;
	int width;
	int height;
};