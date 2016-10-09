#include "Cache.h"
#include "Texture.h"
#include "Game.h"
#include "SpriteInfo.h"
#include "XML.h"
#include <vector>
#include "Debug.h"
namespace ggEngine {
	SpriteInfo* Cache::GetSpriteInfo(std::string key) {
		std::map<std::string, SpriteInfo*>::iterator it = this->spriteInfoMap.find(key);
		SpriteInfo* inf;
		if (it != this->spriteInfoMap.end())
		{
			inf = it->second;
		}
		else {
			g_debug.Warning("No texture found with key " + key);
			return defaultSpriteInfo;
		}
		return inf;
	}
	Font * Cache::GetFont(std::string key)
	{
		std::map<std::string, Font*>::iterator it = this->fontMap.find(key);
		Font* font;
		if (it != this->fontMap.end())
		{
			font = it->second;
		}
		else {
			g_debug.Warning("No font found with key " + key);
			return defaultFont;
		}
		return font;
	}
	bool Cache::SetValueIfNotExists(std::string key,SpriteInfo * inf)
	{
		std::map<std::string, SpriteInfo*>::iterator it = spriteInfoMap.find(key);
		if (it != spriteInfoMap.end() && (it->second)!=NULL)
		{
			g_debug.Warning("Sprite with key " + key + " has exists!");
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
		defaultFont = new Font(game->GetDrawManager(), "Arial", 25, false);
	}
	Cache::~Cache()
	{
		Destroy();
	}
	void Cache::Destroy()
	{
		ClearAll();
		delete defaultSpriteInfo;
		delete defaultFont;
	}
	void Cache::ClearAll()
	{
		for (std::map<std::string, SpriteInfo*>::iterator it = this->spriteInfoMap.begin(); it != this->spriteInfoMap.end(); ++it) {
			delete (it->second);
		};

		this->spriteInfoMap.clear();
		for (std::map<std::string, Font*>::iterator it = this->fontMap.begin(); it != this->fontMap.end(); ++it) {
			delete (it->second);
		};
		this->fontMap.clear();
		this->atlasMap.clear();
	}
	bool Cache::CreateTexture(std::string key, std::string textureFile, D3DCOLOR transColor) {
		Texture *tex = new Texture(this->device, textureFile,transColor);
		if (tex->GetDxTexture() == NULL) {
			g_debug.Warning("No texture found with path " + textureFile);
			return false;
		}
		SetValueIfNotExists(key, new SpriteInfo(tex));
		return true;
	}
	bool Cache::CreateTextureFromAtlasXML(std::string atlasName, std::string atlatPath, std::string atlasDefPath, D3DCOLOR transColor)
	{
		std::map<std::string, Texture*>::iterator it = atlasMap.find(atlasName);
		if (it != atlasMap.end() && (it->second) != NULL)
		{
			g_debug.Warning("Atlas "+ atlasName +" has been loaded already!");
			return false;
		}
		Texture *atlas = new Texture(this->device, atlatPath, transColor);
		if (atlas->GetDxTexture() == NULL) {
			g_debug.Warning("No atlas found with path " + atlatPath);
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
				g_debug.Warning("All key has been created, atlas load failed.");
				atlas->Destroy();
				return false;
			}
			atlasMap[atlasName] = atlas;
			return true;
		}
		else return false;
	}
	bool Cache::CreateFontToCache(std::string fontKey, std::string fontName, int fontSize, bool isItalic, int fontWeight)
	{
		std::map<std::string, Font*>::iterator it = fontMap.find(fontName);
		if (it != fontMap.end() && (it->second) != NULL)
		{
			g_debug.Warning("Font " + fontKey + " has been loaded already!");
			return false;
		}
		Font* font = new Font(game->GetDrawManager(), fontName, fontSize, isItalic, fontWeight);
		if (font->GetDxFont() == NULL) {
			g_debug.Warning("Initialize font " + fontName + " failed.");
			return false;
		}
		fontMap[fontKey] = font;
		return true;
	}
}
