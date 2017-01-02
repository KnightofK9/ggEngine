#include "MedusaHead.h"
#include "CVGame.h"
#include "CVMap.h"
#include "Simon.h"
#include "EnemyGroup.h"
MedusaHead::MedusaHead(CVGame * cvGame, SpriteInfo * spriteInfo) : TweenEnemyBase(cvGame,spriteInfo,16,16,0,2,400)
{
	this->name = "MedusaHead";
	this->CreateAnimation("move", { 0,1 }, true);
	this->CreateAnimation("idle", 0, 0, false);
	SetMoveY(30);
	SetMoveX(0.05);
	SetSpeed(1);

	this->maxHealth = 1;
	this->damage = 2;
	this->point = 300;
	this->fireTimer = 2000;
	this->simonDetectRange = GAME_WIDTH / (2.0*this->cvGame->camera->GetScale().x);
	this->body->SetEnable(false);
	this->body->SetActive(true);
	SetBullet(false);
	this->allowToDetectSimon = true;
	this->events->onOutOfCamera = [this](GameObject*, EventArg) {
		if (IsBullet()) {
			Destroy();
		}
	};
}

MedusaHead::~MedusaHead()
{
}

void MedusaHead::RunLeft()
{
	TweenEnemyBase::RunLeft();
	this->PlayAnimation("move");
}

void MedusaHead::RunRight()
{
	TweenEnemyBase::RunRight();
	this->PlayAnimation("move");
}

void MedusaHead::Update()
{
	if (this->isBullet) {
		TweenEnemyBase::Update();
	}
	else {
		EnemyBase::Update();
	}
}

void MedusaHead::OnSimonEnterRange(Simon * simon, bool isLeft)
{
	//TweenEnemyBase::OnSimonEnterRange(simon, isLeft);
	//this->allowToDetectSimon = false; 
	if (this->shootTimer.stopwatch(fireTimer)) {
		Fire(isLeft, this->position);
	}
}

void MedusaHead::Active()
{
	TweenEnemyBase::Active();
	//this->allowToDetectSimon = true;
	this->body->SetEnable(true);
}

void MedusaHead::Fire(bool isLeft,Vector firePosition)
{
	//g_debug.Log("Firing medusa head!");
	//return;
	auto meduasaHead = this->cvGame->enemyManager->AddMedusaHead(firePosition.x, firePosition.y, this->simon->currentMap->enemyGroup);
	meduasaHead->SetBullet(true);
	meduasaHead->SetPosition(firePosition, true);
	meduasaHead->Active();
	if (isLeft) meduasaHead->RunLeft();
	else meduasaHead->RunRight();
}

void MedusaHead::Kill()
{
	if (IsBullet()) {
		Destroy();
		return;
	}
	this->SetAlive(false);
}

void MedusaHead::SetBullet(bool isBullet)
{
	this->isBullet = isBullet;
	this->allowToDetectSimon = !isBullet;
	this->alive = !isBullet;
	this->visible = isBullet;
}

bool MedusaHead::IsBullet()
{
	return this->isBullet;
}

