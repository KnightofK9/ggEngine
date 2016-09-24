#include "Cache.h"
#include "Texture.h"
#include "Game.h"
namespace ggEngine {
	Texture* Cache::GetTexture(std::string textureKey) {
		std::map<std::string, Texture*>::iterator it = this->textureMap.find(textureKey);
		Texture* tex;
		if (it != this->textureMap.end())
		{
			tex = it->second;
		}
		else {
			Debug::Warning("No texture found with key " + textureKey);
			return this->textureMap["default"];
		}
		return tex;
	}
	Cache::Cache(Game * game)
	{
		this->game = game;
		this->device = &game->GetD3DManager()->getDevice();
		this->textureMap["default"] = new Texture(this->device, "default.bmp");
	}
	Cache::~Cache()
	{
	}
	void Cache::Destroy()
	{
	}
	void Cache::ClearAll()
	{
	}
	bool Cache::CreateTexture(std::string textureKey, std::string textureFile, D3DCOLOR transColor) {
		Texture *tex = new Texture(this->device, textureFile,transColor);
		if (tex->GetTexture() == NULL) {
			Debug::Warning("No texture found with path " + textureFile);
			return false;
		}
		else this->textureMap[textureKey] = tex;
		return true;
	}
}
