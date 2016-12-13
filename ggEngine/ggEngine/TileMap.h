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
		virtual ~TileMap();

		void BuildTileMap(const char * jsonChar);

		void Draw() override;
	private:
		void RenderTileMapToTexture();
		void DrawTileMap(int x, int y, int xEnd, int yEnd);
		int tileWidth;
		int tileHeight;
		std::vector<std::vector<int>> tileMatrix;
		std::vector<Tile*> tileList;
		TileSet *tileSet = nullptr;
		int numberOfCellPerRow;
		int numberOfCellPerColumn;
		DWORD style = D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE;
	};
}