#include "Medusa.h"
#include "CVGame.h"
#include "Simon.h"
#include "CVMap.h"
#include "CVBlock.h"
#include "ItemManager.h"
#include "AnimationManager.h"
#include "MedusaSkill.h"
#include "CVSpriteAnimation.h"
#include "TextureConstant.h"
Medusa::Medusa(CVGame * cvGame, SpriteInfo * image) : ShootingEnemyBase(cvGame,image,32,32,0,4,200)
{

	moveInterval = 1000;
	randomMinX = 40;
	randomMaxX = 200;
	minRandomPause = 400;
	maxRandomPause = 1200;
	timeOutToAwake = 2000;

	this->simonDetectRange = 1;

	SetBullet(new MedusaSkill(this->cvGame, this->cvGame->cache->GetSpriteInfo(TextureConstant::SKILL_BOSS_2_TEXTURE)));
	this->body->SetActive(false);
	this->CreateAnimation("move", 0, 3, true);
	this->fireInterval = 1000;
	this->simonDetectRange = 500;
	moveY = 30;
	moveX = 0.05;
	moveSpeed = 1;
	this->isAwake = false;



}

Medusa::~Medusa()
{
	if (this->currentTween != nullptr) {
		this->currentTween->Stop();
	}
}

void Medusa::Update()
{
	EnemyBase::Update();
	if (!this->isAwake) return;
	if (this->moveTimer.stopwatch(this->moveInterval)) {
		this->lastSimonPosition = this->simon->position;
	}

	if (this->isMoving) {
		double x = this->position.x - this->startPosition.x;
		double increaseY = this->moveY*(sin(x*moveX));
		this->position.y = this->startPosition.y + increaseY;
	}
	else {
		if (this->isPausingMoving) {
#ifdef DEBUG_FRAME
			this->pauseTimer -= DEFAULT_MS_PER_FRAME_FOR_ANIMATION;
#else // DEBUG_FRAME
			this->pauseTimer -= this->cvGame->logicTimer.getDeltaTimeInMilisecond();
#endif
			
			if (this->pauseTimer < 0) {
				this->pauseTimer = Helper::GetRamdomIntNumber(this->minRandomPause, this->maxRandomPause);
				this->isPausingMoving = false;
				MoveToNextPosition();
			}
		}
	}
}

void Medusa::Active()
{
	ShootingEnemyBase::Active();
	this->SetVisible(false);
	this->SetAlive(true);
	this->isMoving = false;
	this->isAwake = false;
	this->isPausingMoving = false;
	this->allowToDetectSimon = true;
}

void Medusa::Destroy()
{
	this->cvGame->animationManager->AddBossDeathAnimation(this->position.x, this->position.y);
	this->cvGame->itemManager->AddStuff(this->position.x, this->position.y, (Group*)this->cvGame->simon->currentMap->enemyGroup);
	CVSpriteAnimation::Destroy();
}

void Medusa::MoveToNextPosition()
{
	int randomMin = Helper::GetRamdomIntNumber(randomMinX, randomMaxX);
	double distance = this->position.x - this->lastSimonPosition.x;
	bool isSimonLeft = distance > 0;
	if (abs(distance) < randomMin) {
		if (isSimonLeft) {
			this->lastSimonPosition.x = this->position.x - randomMin;
		}
		else {
			this->lastSimonPosition.x = this->position.x + randomMin;
		}
	}
	auto block = this->simon->currentMap->GetCurrentBlock();
	if (this->lastSimonPosition.x - this->GetWidth()/2 < block->left) {
		this->lastSimonPosition.x = block->left + this->GetWidth() / 2;
	}
	else {
		if (this->lastSimonPosition.x + this->GetWidth() / 2 > block->right) {
			this->lastSimonPosition.x = block->right - this->GetWidth() / 2;
		}
	}
	this->bullet->Fire(isSimonLeft, this->position);

	MoveTo(this->lastSimonPosition);
}

void Medusa::MoveTo(Vector moveToPosition)
{
	if (this->currentTween == nullptr) {
		this->isMoving = true;
		double distance = abs(moveToPosition.x - this->position.x);
		this->currentTween = this->cvGame->add->Tween(this->position.x, moveToPosition.x,(distance/this->moveSpeed)*DEFAULT_MS_PER_FRAME_FOR_ANIMATION)
			->SetOnFinish([this]() {
			this->currentTween = nullptr;
			this->isMoving = false;
			this->isPausingMoving = true;
		})->Start();
	}
}

void Medusa::Awake()
{
	this->SetVisible(true);
	this->body->SetEnable(true);
	this->PlayAnimation("move");
	this->moveTimer.reset();
	this->isAwake = true;
	MoveTo(this->simon->position);
	this->simon->currentMap->OnEnterBossBlock();
}



void Medusa::OnSimonEnterRange(Simon * simon, bool isLeft)
{
	this->allowToDetectSimon = false;
	if (!this->isAwake) {
		this->cvGame->add->TimeOut(this->timeOutToAwake, [=]() {
			Awake();
		})->Start();

	}
}
