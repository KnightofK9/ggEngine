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
	class TileSet;
	class AudioInfo;
	class Cache:public GGObject {
	public:
		Cache(Game* game);
		virtual ~Cache();
		void ClearAll();
		bool CreateEmptyTexture(std::string key, int textureWidth, int textureHeight);
		bool CreateTexture(std::string key, std::string textureName, D3DCOLOR transColor = D3DCOLOR_RGBA(0, 0, 0, 255));
		bool CreateTextureFromAtlasXML(std::string atlasName, std::string atlatPath, std::string atlasDefPath, D3DCOLOR transColor = D3DCOLOR_RGBA(0, 0, 0, 255));
		bool CreateFontToCache(std::string fontKey, std::string fontName, int fontSize, bool isItalic, int fontWeight);
		bool CreateFontFromFile(std::string fontKey, std::string fontName, std::string fontPath, int fontSize, bool isItalic, int fontWeight);
		bool CreateAudioInfoFromFile(std::string audioKey, std::string audioPath);
		bool CreateTextureFromTileSetJson(std::string tileMapPath, std::string jsonPath, D3DCOLOR transColor = D3DCOLOR_RGBA(0, 0, 0, 255));
		SpriteInfo* GetSpriteInfo(std::string key);
		SpriteInfo* GetDefaultSpriteInfo() {return this->defaultSpriteInfo;}
		Font* GetFont(std::string key);
		AudioInfo* GetAudioInfo(std::string key);
		TileSet* GetTileMap(std::string key);
	private:
		bool SetValueIfNotExists(std::string key, SpriteInfo* inf);
		std::map<std::string, Font*> fontMap;
		std::map<std::string, SpriteInfo*> spriteInfoMap;
		std::map<std::string, Texture*> atlasMap;
		std::map<std::string, TileSet*> tileSetMap;
		std::map<std::string, AudioInfo*> audioInfoMap;
		//Create a map hold info to the dx audio
		SpriteInfo* defaultSpriteInfo;
		Font* defaultFont;
		AudioInfo *defaultAudioInfo;
		Game *game;
		LPDIRECT3DDEVICE9 device;
	};
}