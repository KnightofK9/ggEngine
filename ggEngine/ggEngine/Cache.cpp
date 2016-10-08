#include "Cache.h"
#include "Texture.h"
#include "Game.h"
#include "SpriteInfo.h"
#include "XML.h"
#include <vector>
namespace ggEngine {
	SpriteInfo* Cache::GetSpriteInfo(std::string key) {
		std::map<std::string, SpriteInfo*>::iterator it = this->spriteInfoMap.find(key);
		SpriteInfo* inf;
		if (it != this->spriteInfoMap.end())
		{
			inf = it->second;
		}
		else {
			Debug::Warning("No texture found with key " + key);
			return defaultSpriteInfo;
		}
		return inf;
	}
	bool Cache::SetValueIfNotExists(std::string key,SpriteInfo * inf)
	{
		std::map<std::string, SpriteInfo*>::iterator it = spriteInfoMap.find(key);
		if (it != spriteInfoMap.end() && (it->second)!=NULL)
		{
			Debug::Warning("Sprite with key " + key + " has exists!");
			return false;
		}
		spriteInfoMap[key] = inf;
		return true;
	}
	Cache::Cache(Game * game)
	{
		this->game = game;
		this->device = &game->GetD3DManager()->getDevice();
		Texture* defaultTexture = new Texture(this->device, "default.bmp");
		defaultSpriteInfo = new SpriteInfo(defaultTexture);
	}
	Cache::~Cache()
	{
		Destroy();
	}
	void Cache::Destroy()
	{
		ClearAll();
		delete defaultSpriteInfo;
	}
	void Cache::ClearAll()
	{
		for (std::map<std::string, SpriteInfo*>::iterator it = this->spriteInfoMap.begin(); it != this->spriteInfoMap.end(); ++it) {
			delete (it->second);
		};
		this->spriteInfoMap.clear();
	}
	bool Cache::CreateTexture(std::string key, std::string textureFile, D3DCOLOR transColor) {
		Texture *tex = new Texture(this->device, textureFile,transColor);
		if (tex->GetDxTexture() == NULL) {
			Debug::Warning("No texture found with path " + textureFile);
			return false;
		}
		SetValueIfNotExists(key, new SpriteInfo(tex));
		return true;
	}
	bool Cache::CreateTextureFromAtlasXML(std::string atlasName, std::string atlatPath, std::string atlasDefPath, D3DCOLOR transColor)
	{
		Texture *atlas = new Texture(this->device, atlatPath, transColor);
		if (atlas->GetDxTexture() == NULL) {
			Debug::Warning("No atlas found with path " + atlatPath);
			return false;
		}
		XML xml("Resource/sprites.xml");
		if (xml.IsLoaded()) {
			bool isAllLoadSucceed = false;
			std::vector<AtlasSpriteInfo> spriteList = xml.GetSpriteList();
			for (std::vector<AtlasSpriteInfo>::iterator it = spriteList.begin(); it != spriteList.end(); ++it) {
				isAllLoadSucceed = SetValueIfNotExists(it->name, new SpriteInfo(atlas,it->x,it->y,it->width,it->height)) || isAllLoadSucceed;
			}
			if (!isAllLoadSucceed) {
				Debug::Warning("All key has been created, atlas load failed.");
				atlas->Destroy();
				return false;
			}
			return true;
		}
		else return false;
	}
}
