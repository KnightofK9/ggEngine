#pragma once
#include "IJsonable.h"
#include <string>
namespace ggEngine {
	class Texture;
	class SpriteInfo;
	class Tile;
	class Game;
	class TileSet : public IJsonable {
	public:
		TileSet(Game * game,Texture *texture);
		virtual ~TileSet();
		SpriteInfo* GetTileSetAt(int id) { return this->tileInfoList[id]; }
		Tile* GetTileAt(int id);
		// Inherited via IJsonable
		virtual void ParseJson(std::string jsonChar) override;
		virtual std::string CreateJson() override;
		int GetNumberOfCell() { return this->numberOfCell; }
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
		Game *game;
		std::string id;
	};
}