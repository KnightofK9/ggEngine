#include "StaticTileManager.h"
#include "TextureConstant.h"
StaticTileManager::StaticTileManager(CVGame * cvGame) : ManagerBase(cvGame)
{

}

StaticTileManager::~StaticTileManager()
{
}

TileBrick * StaticTileManager::AddTileBrick(double x, double y, Group * group)
{
	SpriteInfo* spriteInfo = this->cache->GetTileMap(TextureConstant::TILE_SET_LEVEL_2_TEXTURE)->GetTileSetAt(TextureConstant::TILE_BRICK_TEXTURE_KEY);
	TileBrick* tileBrick = new TileBrick(this->cvGame, spriteInfo);
	tileBrick->SetPosition(x, y);
	if (group != nullptr) {
		group->AddDrawObjectToList(tileBrick);
	}

	return tileBrick;
}
