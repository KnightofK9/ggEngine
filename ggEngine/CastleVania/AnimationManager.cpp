#include "AnimationManager.h"
#include "TextureConstant.h"
#include "Simon.h"
#include "CVMap.h"

AnimationManager::AnimationManager(CVGame * cvGame) : ManagerBase(cvGame)
{

}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::PreloadAll()
{
	this->preload->Texture(TextureConstant::ANIMATION_BOSS_DEATH_TEXTURE, TextureConstant::ANIMATION_BOSS_DEATH_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_ENEMY_DEATH_TEXTURE, TextureConstant::ANIMATION_ENEMY_DEATH_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_HIT_TEXTURE, TextureConstant::ANIMATION_HIT_TEXTURE_PATH);
	this->preload->Texture(TextureConstant::ANIMATION_BREAKING_WALL_TEXTURE, TextureConstant::ANIMATION_BREAKING_WALL_TEXTURE_PATH);

}

CVSpriteAnimation * AnimationManager::AddEnemyDeathAnimation(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_ENEMY_DEATH_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 8, 15, 0, 3, 100);
	anim->CreateAnimation("enemyDeath", 0, 2, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (this->simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}
	anim->PlayAnimation("enemyDeath");
	return anim;
}

CVSpriteAnimation * AnimationManager::AddBossDeathAnimation(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_BOSS_DEATH_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 24, 31, 0, 3, 100);
	anim->CreateAnimation("bossDeath", {0, 1, 2, 0, 1, 2}, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}

	anim->PlayAnimation("bossDeath");
	return anim;
}

CVSpriteAnimation * AnimationManager::AddHitAnimation(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_HIT_TEXTURE);
	CVSpriteAnimation *anim = new CVSpriteAnimation(this->cvGame, inf, 8, 10, 0, 1, 100);
	anim->CreateAnimation("hit", 0, 0, false)->SetOnCompleted([anim](Animator*) {
		anim->Destroy();
	});
	anim->SetPosition(Vector(x, y));
	if (simonGroup != nullptr) {
		simonGroup->AddDrawObjectToList(anim);
	}
	anim->SetAnchor(0.8, 0.8);
	anim->PlayAnimation("hit");

	//this->cvGame->physics->EnablePhysics(anim);
	//anim->body->CreateRectangleRigidBody(anim->GetWidth(), anim->GetHeight());
	//anim->body->allowGravity = false;
	//anim->body->SetActive(false);

	return anim;
}

CVSprite ** AnimationManager::AddBreakingWallAnimation(double x, double y)
{
	SpriteInfo* inf = this->cache->GetSpriteInfo(TextureConstant::ANIMATION_BREAKING_WALL_TEXTURE);
	CVSprite**bricks = new CVSprite*[4];
	for (int i = 0; i < 4; i++) {
		bricks[i] = new CVSprite(this->cvGame, inf);
		CVSprite *br = bricks[i];

		this->cvGame->physics->EnablePhysics(br);
		br->body->CreateRectangleRigidBody(br->GetWidth(), br->GetHeight());
		br->body->SetEnable(false);
		br->body->allowGravity = true;
		br->SetPosition(Vector(x, y));
		br->body->rigidBody->SetAnchor(0.5, 0.5);
		br->body->SetActive(false);
		//this->cvGame->eventManager->EnableCameraEvent(br);

		//br->events->onOutOfCamera = [br](GameObject *go, EventArg e){
		//	br->Destroy();
		//};

		if (simonGroup != nullptr) {
			simonGroup->AddDrawObjectToList(br);
		}
	}
	bricks[0]->body->AddForce(12, Vector(1, 2));
	bricks[1]->body->AddForce(15, Vector(-1, 1.5));
	bricks[2]->body->AddForce(17, Vector(1, 0.5));
	bricks[3]->body->AddForce(13, Vector(-1, 0.5));
	return bricks;
}
