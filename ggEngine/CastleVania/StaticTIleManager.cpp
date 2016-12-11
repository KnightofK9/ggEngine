#include "StaticTileManager.h"
#include "TextureConstant.h"
StaticTileManager::StaticTileManager(CVGame * cvGame) : ManagerBase(cvGame)
{

}

StaticTileManager::~StaticTileManager()
{
}

void StaticTileManager::PreloadAll()
{
	this->preload->Texture(TextureConstant::TILE_BRICK_TEXTURE, TextureConstant::TILE_BRICK_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::TILE_LADDER_DOWN_LEFT, TextureConstant::TILE_LADDER_DOWN_LEFT_PATH);
	this->preload->Texture(TextureConstant::TILE_LADDER_DOWN_RIGHT, TextureConstant::TILE_LADDER_DOWN_RIGHT_PATH);
	this->preload->Texture(TextureConstant::TILE_LADDER_UP_LEFT, TextureConstant::TILE_LADDER_UP_LEFT_PATH);
	this->preload->Texture(TextureConstant::TILE_LADDER_UP_RIGHT, TextureConstant::TILE_LADDER_UP_RIGHT_PATH);
}

TileBrick * StaticTileManager::AddTileBrick(double x, double y, Group * group)
{
	SpriteInfo* spriteInfo = this->cache->GetSpriteInfo(TextureConstant::TILE_BRICK_TEXTURE);
	TileBrick* go = new TileBrick(this->cvGame, spriteInfo);
	go->SetPosition(x, y);
	if (group != nullptr) {
		group->AddDrawObjectToList(go);
	}

	return go;
}

TileLadder * StaticTileManager::AddTileLadder(double x, double y,ObjectType ladderType, Group * group)
{
	std::string textureConstant = "";
	Tag tag = ladderType;
	switch (tag) {
	case ObjectType_LevelTwoLadderDownLeft:
		textureConstant = TextureConstant::TILE_LADDER_DOWN_LEFT;
		break;
	case ObjectType_LevelTwoLadderUpLeft:
		textureConstant = TextureConstant::TILE_LADDER_UP_LEFT;
		break;
	case ObjectType_LevelTwoLadderDownRight:
		textureConstant = TextureConstant::TILE_LADDER_DOWN_RIGHT;
		break;
	case ObjectType_LevelTwoLadderUpRight:
		textureConstant = TextureConstant::TILE_LADDER_UP_RIGHT;
		break;
	default:
		return nullptr;
	}
	SpriteInfo* spriteInfo = this->cache->GetSpriteInfo(textureConstant);
	TileLadder* go = new TileLadder(this->cvGame, spriteInfo);
	go->tag = tag;
	go->SetPosition(x, y);
	if (group != nullptr) {
		group->AddDrawObjectToList(go);
	}

	return go;
}
