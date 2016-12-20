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
	this->preload->Texture(TextureConstant::DOOR_TEXTURE, TextureConstant::DOOR_TEXTURE_PATH);
	//this->preload->Texture(TextureConstant::TILE_LADDER_DOWN_LEFT, TextureConstant::TILE_LADDER_DOWN_LEFT_PATH);
	//this->preload->Texture(TextureConstant::TILE_LADDER_DOWN_RIGHT, TextureConstant::TILE_LADDER_DOWN_RIGHT_PATH);
	//this->preload->Texture(TextureConstant::TILE_LADDER_UP_LEFT, TextureConstant::TILE_LADDER_UP_LEFT_PATH);
	//this->preload->Texture(TextureConstant::TILE_LADDER_UP_RIGHT, TextureConstant::TILE_LADDER_UP_RIGHT_PATH);
}

Door * StaticTileManager::AddDoor(double x, double y, Group * group)
{
	SpriteInfo* spriteInfo = this->cache->GetSpriteInfo(TextureConstant::DOOR_TEXTURE);
	Door* go = new Door(this->cvGame, spriteInfo);
	go->SetPosition(x, y);
	if (group != nullptr) {
		group->AddDrawObjectToList(go);
	}

	return go;
}

TileBrick * StaticTileManager::AddTileBrick(double x, double y,double width, double height, Group * group)
{
	SpriteInfo* spriteInfo = this->cache->GetSpriteInfo(TextureConstant::TILE_BRICK_TEXTURE);
	TileBrick* go = new TileBrick(this->cvGame, spriteInfo);
	go->body->SetWidth(width);
	go->body->SetHeight(height);
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
	case ObjectType_LadderDownLeft:
		textureConstant = TextureConstant::TILE_LADDER_DOWN_LEFT;
		break;
	case ObjectType_LadderUpLeft:
		textureConstant = TextureConstant::TILE_LADDER_UP_LEFT;
		break;
	case ObjectType_LadderDownRight:
		textureConstant = TextureConstant::TILE_LADDER_DOWN_RIGHT;
		break;
	case ObjectType_LadderUpRight:
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
	go->SetWidth(16);
	go->SetHeight(16);
	go->body->SetWidth(16);
	go->body->SetHeight(16);
	return go;
}
