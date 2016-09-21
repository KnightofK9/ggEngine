#include "DrawManager.h"

namespace ggEngine {
	DrawManager::DrawManager(IDirect3DDevice9 *device)
	{
		this->device = device;
		HRESULT result = D3DXCreateSprite(this->device, &this->spriteHandler);
		if (result != D3D_OK) 
		{
			this->spriteHandler = NULL;
			throw ERROR_CODE_FAIL_INIT_DRAW_MANAGER_ERROR_UNKNOW;
		}
	}

	DrawManager::~DrawManager()
	{
		Destroy();
	}

	void DrawManager::Destroy()
	{
		if (this->spriteHandler != NULL) spriteHandler->Release();
	}

	void DrawManager::Render2D()
	{
		if (this->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK) 
		{
			Update2D();
			spriteHandler->End();
		}
	}

	void DrawManager::Update2D()
	{
		//TO DO:Draw DrawObject here
	}

}