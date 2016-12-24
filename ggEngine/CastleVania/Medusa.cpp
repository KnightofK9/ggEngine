#include "Medusa.h"
#include "CVGame.h"
Medusa::Medusa(CVGame * cvGame, SpriteInfo * image) : ShootingEnemyBase(cvGame,image,32,32,0,4,200)
{
	this->body->SetActive(false);
	this->CreateAnimation("move", 0, 3, true);
	this->SetVisible(false);
	this->allowToDetectSimon = true;
	this->fireInterval = 1000;
}

Medusa::~Medusa()
{
}

void Medusa::Update()
{
	//ShootingEnemyBase::Update();
}

void Medusa::Active()
{
	this->SetAlive(true);
}

void Medusa::Awake()
{
	this->SetVisible(true);
	this->body->SetEnable(true);
	this->PlayAnimation("move");
}

void Medusa::RunLeft()
{
}

void Medusa::RunRight()
{
}

void Medusa::OnSimonEnterRange(Simon * simon, bool isLeft)
{
	this->allowToDetectSimon = false;
	this->simon = simon;
	this->cvGame->add->TimeOut(this->timeOutToAwake, [=]() {
		Awake();
	})->Start();
}
