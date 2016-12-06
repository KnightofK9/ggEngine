#include "TileMap.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "QuadNode.h"
#include "SpriteInfo.h"
#include "AnimationTile.h"
#include "SingleTile.h"
#include "Camera.h"
#include "Physics.h"
#include "TileSet.h"
#include "Cache.h"
#include "Debug.h"
#include "Game.h"
#include "TileSet.h"
#include "Tile.h"
namespace ggEngine {
	TileMap::TileMap(Game *game) : Group(game)
	{

	}
	void TileMap::BuildTileMap(const char * jsonChar)
	{
		Json json(jsonChar);

		this->name = json["name"].GetString();
		this->width = json["width"].GetDouble();
		this->height = json["height"].GetDouble();
		this->tileWidth = json["tileWidth"].GetDouble();
		this->tileHeight = json["tileHeight"].GetDouble();
		std::string tileSetKey = "";
		for (auto& it : json["tileSetList"].GetArray()) {
			tileSetKey = it.GetString();
		}
		int numberOfCellPerRow = floor(this->width / this->tileWidth);
		int numberOfCellPerColumn = floor(this->height / this->tileHeight);

		this->tileList.resize(this->tileSet->GetNumberOfCell());
		for (int i = 0; i < this->tileList.size(); i++) {
			tileList[i] = this->tileSet->GetTileAt(i);
		}


		this->tileMatrix.resize(numberOfCellPerColumn);
		for (auto it = this->tileMatrix.begin(); it != this->tileMatrix.end(); ++it) {
			(*it).resize(numberOfCellPerRow);
		}

		this->tileSet = this->game->cache->GetTileMap(tileSetKey);
		int indexY = 0;
		for (auto& itY : json["tileMatrix"].GetArray()) {
			int indexX = 0;
			for (auto& itX : itY.GetArray()) {
				this->tileMatrix[indexY][indexX] = itX.GetInt();
				indexX++;
			}
			
			indexY++;
		}

	}
	TileMap::~TileMap()
	{
	
	}

	void TileMap::Draw()
	{
		Transform(this->spriteHandle);
		if (spriteHandle->Begin(style) == D3D_OK)
		{
			int x, y, xEnd, yEnd;
			Rect r = this->game->camera->GetNormalRect();
			x = floor(r.left / this->tileWidth);
			y = floor(r.top / this->tileHeight);
			xEnd = round(r.right / this->tileWidth);
			yEnd = round(r.bottom / this->tileHeight);


			x +=  floor(this->basePositionObject->worldPosition.x);
			y += floor(this->basePositionObject->worldPosition.x);
			xEnd += round(this->basePositionObject->worldPosition.y);
			yEnd += round(this->basePositionObject->worldPosition.y);

			DrawTileMap(x, y, xEnd, yEnd);

			spriteHandle->End();
		}
	}

	void TileMap::DrawTileMap(int x, int y, int xEnd, int yEnd)
	{
		for (int yId = y; yId <= yEnd; yId++) {
			for (int xId = x; xId <= xEnd; xId++) {
				tileList[tileMatrix[yId][xId]]->Draw(xId*tileWidth, yId*tileHeight);
			}
		}
	}
	

	
}