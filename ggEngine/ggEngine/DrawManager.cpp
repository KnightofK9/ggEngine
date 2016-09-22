#include "DrawManager.h"

namespace ggEngine {
	DrawManager::DrawManager(IDirect3DDevice9 *device)
	{
		this->device = device;
	/*	HRESULT result = D3DXCreateSprite(this->device, &this->spriteHandler);
		if (result != D3D_OK) 
		{
			this->spriteHandler = NULL;
			throw ERROR_CODE_FAIL_INIT_DRAW_MANAGER_ERROR_UNKNOW;
		}*/
		this->spriteTest = CreateSprite("default.bmp");
		this->spriteTest->SetScale(50, 30);
	}
	Sprite* DrawManager::CreateSprite(std::string fileSource){
		return new Sprite(this->device, fileSource);
	}
	DrawManager::~DrawManager()
	{
		Destroy();
	}

	void DrawManager::Destroy()
	{
		//if (this->spriteHandler != NULL) spriteHandler->Release();
	}

	void DrawManager::Render2D()
	{
		Update2D();
	}

	void DrawManager::Update2D()
	{
		
		this->spriteTest->Draw();
	}

}