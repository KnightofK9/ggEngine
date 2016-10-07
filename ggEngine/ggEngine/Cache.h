#pragma once
#include "GGObject.h"
#include <map>
#include <string>
#include <d3d9.h>
namespace ggEngine {
	class Texture;
	class Game;
	class Cache:public GGObject {
	public:
		Cache(Game* game);
		~Cache();
		void Destroy();
		void ClearAll();
		bool CreateTexture(std::string textureKey, std::string textureName, D3DCOLOR transColor = D3DCOLOR_RGBA(0, 0, 0, 255));
		bool CreateTextureFromAtlasXML(std::string atlasName, std::string atlatPath, std::string atlasDefPath, D3DCOLOR transColor = D3DCOLOR_RGBA(0, 0, 0, 255));
		Texture* GetTexture(std::string textureKey);
	private:
		std::map<std::string, Texture*> textureMap;
		std::map<std::string, Texture*> atlasMap;
		Texture* defaultTexture;
		Game *game;
		LPDIRECT3DDEVICE9 device;
	};
}