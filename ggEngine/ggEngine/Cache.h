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
	class TileMapInfo;
	class Cache:public GGObject {
	public:
		Cache(Game* game);
		~Cache();
		void Destroy();
		void ClearAll();
		bool CreateTexture(std::string key, std::string textureName, D3DCOLOR transColor = D3DCOLOR_RGBA(0, 0, 0, 255));
		bool CreateTextureFromAtlasXML(std::string atlasName, std::string atlatPath, std::string atlasDefPath, D3DCOLOR transColor = D3DCOLOR_RGBA(0, 0, 0, 255));
		bool CreateFontToCache(std::string fontKey, std::string fontName, int fontSize, bool isItalic, int fontWeight);
		bool CreateAudioFromFile(std::string audioKey, std::string audioPath);
		bool CreateTextureFromTileMapJson(std::string tileMapPath, std::string jsonPath, D3DCOLOR transColor = D3DCOLOR_RGBA(0, 0, 0, 255));
		SpriteInfo* GetSpriteInfo(std::string key);
		SpriteInfo* GetDefaultSpriteInfo() {return this->defaultSpriteInfo;}
		Font* GetFont(std::string key);
		TileMapInfo* GetTileMap(std::string key);
	private:
		bool SetValueIfNotExists(std::string key, SpriteInfo* inf);
		std::map<std::string, Font*> fontMap;
		std::map<std::string, SpriteInfo*> spriteInfoMap;
		std::map<std::string, Texture*> atlasMap;
		std::map<std::string, TileMapInfo*> tileMapMap;
		//Create a map hold info to the dx audio
		SpriteInfo* defaultSpriteInfo;
		Font* defaultFont;
		Game *game;
		LPDIRECT3DDEVICE9 device;
	};
}