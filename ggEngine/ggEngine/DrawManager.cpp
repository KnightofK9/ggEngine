#include "DrawManager.h"
#include "Group.h"
#include "Sprite.h"
#include "Texture.h"
namespace ggEngine {
	DrawManager::DrawManager(IDirect3DDevice9 *device)
	{
		this->device = device;
		this->textureMap["default"] = new Texture(this->device, "default.bmp");
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

	void DrawManager::CreateTexture(std::string textureKey, std::string textureFile){
		Texture *tex = new Texture(this->device ,textureFile);
		if (tex->GetTexture() == NULL){
			tex = new Texture(this->device, "default.bmp");
			Debug::Warning("No texture found with path " + textureFile);
		}
		else this->textureMap[textureKey] = tex;
	}

}