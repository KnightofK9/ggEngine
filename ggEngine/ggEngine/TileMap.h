#pragma once
#include "Group.h"
#include "GameObject.h"
#include <vector>
namespace ggEngine {
	class Game;
	class TileSet;
	class Tile;
	class TileMap : public Group{
	public:
		TileMap(Game *game);
		void BuildTileMap(const char * jsonChar);
		virtual ~TileMap();

		void Draw() override;
	private:
		void DrawTileMap(int x, int y, int xEnd, int yEnd);
		int tileWidth;
		int tileHeight;
		std::vector<std::vector<int>> tileMatrix;
		std::vector<Tile*> tileList;
		TileSet *tileSet = nullptr;

		DWORD style = D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE;
	};
}