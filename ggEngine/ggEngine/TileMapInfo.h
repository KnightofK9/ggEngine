#pragma once
#include "IJsonable.h"
#include <string>
namespace ggEngine {
	class Texture;
	class SpriteInfo;
	class TileMapInfo : public IJsonable {
	public:
		TileMapInfo(Texture *texture);
		~TileMapInfo();
		void Destroy();
		SpriteInfo* GetTileMapInfoAt(int id) { return this->tileInfoList[id]; }
		// Inherited via IJsonable
		virtual void ParseJson(std::string jsonChar) override;
		virtual std::string CreateJson() override;
	private:
		Texture *texture;
		std::vector<SpriteInfo*> tileInfoList;
		int width;
		int height;
		int tileWidth;
		int tileHeight;
		int numberOfCell;
		int numberOfCellPerRow;
		int numberOfCellPerColumn;
		std::string id;
	};
}