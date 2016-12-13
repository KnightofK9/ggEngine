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
#include "Add.h"
#include <d3d9.h>
namespace ggEngine {
	TileMap::TileMap(Game *game) : Group(game)
	{

	}

	TileMap::~TileMap()
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
		this->tileSet = this->game->cache->GetTileMap(tileSetKey);
		numberOfCellPerRow = floor(this->width / this->tileWidth);
		numberOfCellPerColumn = floor(this->height / this->tileHeight);

		this->tileList.resize(this->tileSet->GetNumberOfCell());
		for (int i = 0; i < this->tileList.size(); i++) {
			tileList[i] = this->tileSet->GetTileAt(i);
		}


		this->tileMatrix.resize(numberOfCellPerColumn);
		for (auto it = this->tileMatrix.begin(); it != this->tileMatrix.end(); ++it) {
			(*it).resize(numberOfCellPerRow);
		}

	
		int indexY = 0;
		for (auto& itY : json["tileMatrix"].GetArray()) {
			int indexX = 0;
			for (auto& itX : itY.GetArray()) {
				this->tileMatrix[indexY][indexX] = itX.GetInt();
				indexX++;
			}
			
			indexY++;
		}
		RenderTileMapToTexture();

	}
	void TileMap::Draw()
	{
		Group::Draw();
		//Transform(this->spriteHandle);
		//Scale from 0 0
		/*Matrix mat;
		mat = Matrix::CreateTranslateMatrix(-this->GetWidth()*(this->GetAnchor().x), -this->GetHeight()*(this->GetAnchor().y));

		spriteHandle->SetTransform(&mat);


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

			if (x < 0) x = 0;
			if (y < 0) y = 0;
			if (xEnd >= numberOfCellPerRow) xEnd = numberOfCellPerRow - 1;
			if (yEnd >= numberOfCellPerColumn) yEnd = numberOfCellPerColumn - 1;

			DrawTileMap(x, y, xEnd, yEnd);

			spriteHandle->End();
		}*/
	}

	void TileMap::RenderTileMapToTexture()
	{
		this->game->cache->CreateEmptyTexture(this->name, this->width, this->height);
		SpriteInfo *spriteInfo = this->game->cache->GetSpriteInfo(this->name);
		Texture *texture = spriteInfo->GetTexture();
		this->drawManager->ChangeRenderTargetTo(texture);
		LPDIRECT3DDEVICE9 device = &this->game->GetD3DManager()->getDevice();
		device->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255,0,0,0), 1.0, 0);
		device->BeginScene();
		device->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0, 0);


		Matrix mat;
		mat = Matrix::CreateTranslateMatrix(0, 0);
		spriteHandle->SetTransform(&mat);
		if (spriteHandle->Begin(D3DXSPRITE_ALPHABLEND) == D3D_OK)
		{
			for (int yId = 0; yId < this->numberOfCellPerColumn; yId++) {
				for (int xId = 0; xId < this->numberOfCellPerRow; xId++) {
					tileList[tileMatrix[yId][xId]]->Draw(xId*tileWidth, yId*tileHeight);
				}
			}

			spriteHandle->End();
		}

		device->EndScene();
		this->drawManager->ResetRenderTarget();

		this->game->add->Sprite(0, 0, this->name, this);

	}

	void TileMap::DrawTileMap(int x, int y, int xEnd, int yEnd)
	{
		/*for (int yId = y; yId <= yEnd; yId++) {
			for (int xId = x; xId <= xEnd; xId++) {
				tileList[tileMatrix[yId][xId]]->Draw(xId*tileWidth, yId*tileHeight);
			}
		}*/
	}
	

	
}