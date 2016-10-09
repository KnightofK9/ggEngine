#pragma once
#include "GGObject.h"
#include <map>
#include <string>
#include <d3d9.h>
namespace ggEngine {
	class Font;
	class Texture;
	class SpriteInfo;
	class Game;
	class Cache:public GGObject {
	public:
		Cache(Game* game);
		~Cache();
		void Destroy();
		void ClearAll();
		bool CreateTexture(std::string key, std::string textureName, D3DCOLOR transColor = D3DCOLOR_RGBA(0, 0, 0, 255));
		bool CreateTextureFromAtlasXML(std::string atlasName, std::string atlatPath, std::string atlasDefPath, D3DCOLOR transColor = D3DCOLOR_RGBA(0, 0, 0, 255));
		bool CreateFontToCache(std::string fontKey, std::string fontName, int fontSize, bool isItalic, int fontWeight);
		SpriteInfo* GetSpriteInfo(std::string key);
		Font* GetFont(std::string key);
	private:
		bool SetValueIfNotExists(std::string key, SpriteInfo* inf);
		std::map<std::string, Font*> fontMap;
		std::map<std::string, SpriteInfo*> spriteInfoMap;
		std::map<std::string, Texture*> atlasMap;
		SpriteInfo* defaultSpriteInfo;
		Font* defaultFont;
		Game *game;
		LPDIRECT3DDEVICE9 device;
	};
}