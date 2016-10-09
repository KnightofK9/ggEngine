#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "GGObject.h"
#include "ConstantEnum.h"
#include "DrawManager.h"
#include "StateManager.h"
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
namespace ggEngine {
	class Game;
	class D3DManager :public GGObject{
	public:
		D3DManager(Game *game, HWND window, int width, int height, D3DCOLOR backgroundColor, bool isWindowed);
		~D3DManager();
		void Destroy();
		void update();
		IDirect3DDevice9& getDevice() { return *d3ddv; }
		IDirect3D9 &getContext() { return *d3d; }
		void SetDrawManager(DrawManager *drawManager){ this->drawManager = drawManager; }
		void SetStateManager(StateManager *stateManager) { this->stateManager = stateManager; }
	protected:
		void errorCheck(HRESULT result, LPCTSTR debugInfo);
		void clearScene();
		StateManager *stateManager;
		IDirect3D9* d3d;
		IDirect3DDevice9* d3ddv;
		D3DPRESENT_PARAMETERS  d3dpp;
		D3DCOLOR backgroundColor;
		LPDIRECT3DSURFACE9 back_buffer = NULL;
		LPDIRECT3DSURFACE9 surface = NULL;
		int width;
		int height;
		DrawManager *drawManager;
		Game *game;
	};
}