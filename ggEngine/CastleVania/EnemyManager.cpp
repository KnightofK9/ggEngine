#include "EnemyManager.h"
#include "TextureConstant.h"
EnemyManager::EnemyManager(CVGame * cvGame) : ManagerBase(cvGame)
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::PreloadAll()
{
	this->preload->Texture(TextureConstant::AXE_KNIGHT_TEXTURE, TextureConstant::AXE_KNIGHT_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::MEDUSA_HEAD_TEXTURE, TextureConstant::MEDUSA_HEAD_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::BONE_PILLAR_TEXTURE, TextureConstant::BONE_PILLAR_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::BAT_ENEMY_TEXTURE, TextureConstant::BAT_ENEMY_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::GHOST_TEXTURE, TextureConstant::GHOST_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::BOSS_TEXTURE, TextureConstant::BOSS_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::AI6_TEXTURE, TextureConstant::AI6_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::AI7_TEXTURE, TextureConstant::AI7_TEXTURE_PATH);
}

AxeKnight* EnemyManager::AddAxeKnight(double x, double y, Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::AXE_KNIGHT_TEXTURE);
	AxeKnight *go = new AxeKnight(this->cvGame, inf);
	go->SetPosition(Vector(x, y));
	go->Active();
	if (group != nullptr) {
		group->AddDrawObjectToList(go);
	}
	return go;
}

Medusa * EnemyManager::AddMedusa(double x, double y, Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::MEDUSA_HEAD_TEXTURE);
	Medusa *go = new Medusa(this->cvGame, inf);
	go->SetPosition(Vector(x, y));
	go->Active();
	if (group != nullptr) {
		group->AddDrawObjectToList(go);
	}
	return go;
}

BatEnemy * EnemyManager::AddBatEnemy(double x, double y, Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::BAT_ENEMY_TEXTURE);
	BatEnemy *go = new BatEnemy(this->cvGame, inf);
	go->SetPosition(Vector(x, y));
	go->Active();
	if (group != nullptr) {
		group->AddDrawObjectToList(go);
	}
	return go;
}

Ghost * EnemyManager::AddGhost(double x, double y, Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::GHOST_TEXTURE);
	Ghost *go = new Ghost(this->cvGame, inf);
	go->SetPosition(Vector(x, y));
	go->Active();
	if (group != nullptr) {
		group->AddDrawObjectToList(go);
	}
	return go;
}

AI6 * EnemyManager::AddAI6(double x, double y, double moveWidth, Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::AI6_TEXTURE);
	AI6 *go = new AI6(this->cvGame, inf);
	go->SetPosition(Vector(x, y));
	go->Active();
	go->SetMoveWidth(moveWidth);
	if (group != nullptr) {
		group->AddDrawObjectToList(go);
	}
	return go;
}

AI7 * EnemyManager::AddAI7(double x, double y,  Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::AI7_TEXTURE);
	AI7 *go = new AI7(this->cvGame, inf);
	go->SetPosition(Vector(x, y));
	go->Active();
	if (group != nullptr) {
		group->AddDrawObjectToList(go);
	}
	return go;
}
