#pragma once
#include <msxml.h>
#include "GGObject.h"
#include <string>
#include "Font.h"
namespace ggEngine{
	enum AtlasDefType{ AtlasDefTypeXML, AtlasDefTypeJSON };
	class Sprite;
	class Group;
	class Cache;
	class Audio;
	class Preload :public GGObject  {
	public:
		Preload(Cache *cache);
		void Font(std::string fontKey, std::string fontName, int fontSize, bool isItalic, int fontWeight = FW_NORMAL);
		void Font(std::string fontKey, std::string fontName, std::string fontPath , int fontSize, bool isItalic, int fontWeight = FW_NORMAL);
		void Texture(std::string textureKey, std::string texturePath);
		void Atlas(std::string atlasName, std::string atlasPath, std::string atlasDefPath, AtlasDefType type = AtlasDefTypeXML);
		void Audio(std::string audioKey, std::string audioPath);
		void TileSet(std::string tileSetPath, std::string tileSetJsonPath);
	private:
		Cache *cache;
	};
}