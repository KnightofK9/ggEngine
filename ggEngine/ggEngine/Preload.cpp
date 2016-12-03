#include "Preload.h"
#include "Group.h"
#include "Sprite.h"
#include "Cache.h"
#include "Audio.h"
namespace ggEngine{
	Preload::Preload(Cache *cache){
		this->cache = cache;
	}
	void Preload::Font(std::string fontKey, std::string fontName, int fontSize, bool isItalic, int fontWeight)
	{
		this->cache->CreateFontToCache(fontKey, fontName, fontSize, isItalic, fontWeight);
	}
	void Preload::Font(std::string fontKey, std::string fontName, std::string fontPath, int fontSize, bool isItalic, int fontWeight)
	{
		this->cache->CreateFontFromFile(fontKey, fontName, fontPath, fontSize, isItalic, fontWeight);
	}
	void Preload::Texture(std::string textureKey, std::string texturePath){
		this->cache->CreateTexture(textureKey, texturePath);
	}
	void Preload::Atlas(std::string atlasName, std::string atlasPath, std::string atlasDefPath, AtlasDefType type)
	{
		switch (type) {
		case AtlasDefTypeXML:
			this->cache->CreateTextureFromAtlasXML(atlasName, atlasPath, atlasDefPath);
			break;
		case AtlasDefTypeJSON:
			break;
		}
	}
	void Preload::Audio(std::string audioKey, std::string audioPath){
		this->cache->CreateAudioInfoFromFile(audioKey, audioPath);
	}
	void Preload::TileSet(std::string tileSetPath, std::string tileSetJsonPath)
	{
		this->cache->CreateTextureFromTileSetJson(tileSetPath, tileSetJsonPath);
	}
}