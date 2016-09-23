#include "DrawManager.h"
#include "Group.h"
#include "Sprite.h"
#include "Texture.h"
namespace ggEngine {
	DrawManager::DrawManager(IDirect3DDevice9 *device)
	{
		this->device = device;
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
		
	}

	void DrawManager::Render2D()
	{
		Update2D();
	}

	void DrawManager::Update2D()
	{
	}

}