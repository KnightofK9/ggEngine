#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "GGObject.h"
#include "ConstantEnum.h"
#pragma comment(lib,"d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
namespace ggEngine {
	class D3DManager :public GGObject{
	public:
		D3DManager(HWND window, int width, int height, D3DCOLOR backgroundColor, bool isWindowed);
		~D3DManager();
		void Destroy();
		void update();
		IDirect3DDevice9& getDevice() { return *d3ddv; }
		IDirect3D9 &getContext() { return *d3d; }
	protected:
		void errorCheck(HRESULT result, LPCTSTR debugInfo);
		void clearScene();
		IDirect3D9* d3d;
		IDirect3DDevice9* d3ddv;
		D3DPRESENT_PARAMETERS  d3dpp;
		D3DCOLOR backgroundColor;
		LPDIRECT3DSURFACE9 back_buffer = NULL;
		LPDIRECT3DSURFACE9 surface = NULL;
		int width;
		int height;
	};
}