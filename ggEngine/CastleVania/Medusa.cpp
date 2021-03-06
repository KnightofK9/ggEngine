#include "Medusa.h"
#include "CVGame.h"
#include "Simon.h"
#include "CVMap.h"
#include "CVBlock.h"
#include "ItemManager.h"
#include "AnimationManager.h"
#include "MedusaSkill.h"
#include "EnemyGroup.h"
#include "CVSpriteAnimation.h"
#include "TextureConstant.h"
#include "AudioManager.h"
#include "Simon.h"
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
	this->simonDetectRange = 100;
	moveY = 30;
	moveX = 0.05;
	moveSpeed = 1;
	this->isAwake = false;

	this->allowToDetectSimon = false;
	this->body->SetEnable(false);
	this->awakingTimeOut = nullptr;

	this->maxHealth = 16;
	this->damage = 1.0f;
	this->point = 3000;

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
	if (this->awakingTimeOut != nullptr) {
		this->awakingTimeOut->Stop();
		this->awakingTimeOut = nullptr;
	}
	this->body->SetEnable(true);
	this->SetVisible(false);
	this->SetAlive(true);
	this->isMoving = false;
	this->isAwake = false;
	this->isPausingMoving = false;
}

void Medusa::Kill()
{
	this->cvGame->animationManager->AddBossDeathAnimation(this->position.x, this->position.y);
	//this->cvGame->itemManager->AddStuff(GAME_WIDTH/2, GAME_HEIGHT/2, this->cvGame->simon->currentMap->enemyGroup);
	ShootingEnemyBase::Kill();
}

int Medusa::LoseHealth(int health)
{
	if (this->awakingTimeOut == nullptr && !this->isAwake) {
		this->awakingTimeOut = this->cvGame->add->TimeOut(this->timeOutToAwake, [=]() {
			Awake();
			this->awakingTimeOut = nullptr;
		})->Start();
	}
	if (!this->isAwake) {
		return 0;
	}
	return ShootingEnemyBase::LoseHealth(health);
}

void Medusa::Death()
{
	ShootingEnemyBase::Death();
	auto go = this->cvGame->itemManager->AddStuff(this->position.x, this->position.y, this->parentGroup);
	go->Active();
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
	Rect r = this->cvGame->camera->GetNormalRect();
	if (this->lastSimonPosition.x <= r.left) {
		this->lastSimonPosition.x = r.left + this->GetWidth();
	}
	else {
		if (this->lastSimonPosition.x >= r.right) {
			this->lastSimonPosition.x = r.right - this->GetWidth() ;
		}
	}
	g_debug.Log("Simon last position " + std::to_string(lastSimonPosition.x));
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
	this->PlayAnimation("move");
	this->moveTimer.reset();
	this->isAwake = true;
	MoveTo(this->simon->position);
	this->simon->currentMap->OnEnterBossBlock(this);
	this->cvGame->audioManager->PauseAllMusic();
	this->cvGame->audioManager->bossBattleMusic->PlayLoop();
}



void Medusa::OnSimonEnterRange(Simon * simon, bool isLeft)
{
	this->allowToDetectSimon = false;
	//if (!this->isAwake) {
	//	this->cvGame->add->TimeOut(this->timeOutToAwake, [=]() {
	//		Awake();
	//	})->Start();

	//}
}
