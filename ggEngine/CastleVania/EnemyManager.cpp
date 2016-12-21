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
	this->preload->Texture(TextureConstant::BONE_PILLAR_TEXTURE, TextureConstant::BONE_PILLAR_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::BAT_ENEMY_TEXTURE, TextureConstant::BAT_ENEMY_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::GHOST_TEXTURE, TextureConstant::GHOST_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::BOSS_TEXTURE, TextureConstant::BOSS_TEXTURE_PATH);
}

AxeKnight* EnemyManager::AddAxeKnight(double x, double y, Group * group)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::AXE_KNIGHT_TEXTURE);
	AxeKnight *go = new AxeKnight(this->cvGame, inf);
	go->SetPosition(x, y);
	//go->SetAlive(true);
	go->Active();
	if (group != nullptr) {
		group->AddDrawObjectToList(go);
	}
	return go;
}
