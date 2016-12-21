#include "EnemyBase.h"
#include "Simon.h"
#include "CVGame.h"
#include "TileBrick.h"
EnemyBase::EnemyBase(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame):CVSpriteAnimation(cvGame,image, frameWidth,frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->tag = ObjectType_Enemy;
	cvGame->physics->AttachBodyTo(this);
	this->SetAnchor(0.5, 0);
	this->body->SetPhysicsMode(PhysicsMode_AABBSwept);
	this->body->CreateRectangleRigidBody(GetWidth(), GetHeight());
	//this->body->immoveable = false;
	this->events->onCheckingCollide = [this](GameObject* go, ColliderArg e) {
		return OnCheckingCollide(e);
	};
	this->events->onOverlap = [this](GameObject* go, ColliderArg e) {
		auto otherObject = e.colliderObject;
		Tag tag = otherObject->tag;
		switch (tag) {
		case ObjectType_LevelTwoBrick:
			OnBrickContact(dynamic_cast<TileBrick*>(otherObject), e);
		case ObjectType_Simon:
			OnSimonContact(dynamic_cast<Simon*>(otherObject), e);
			break;
		}
	};
	this->cvGame->eventManager->EnableEventUpdate(this, false);
	this->events->onUpdate = [this](GameObject*) {
		Update();
	};

	this->SetAlive(false);
	this->body->SetActive(false);
}

EnemyBase::~EnemyBase()
{
}


void EnemyBase::OnSimonContact(Simon * simon, ColliderArg e)
{
}

void EnemyBase::Active()
{

	this->SetAlive(true);
	this->body->SetActive(true);
}

bool EnemyBase::OnCheckingCollide(ColliderArg e)
{
	return false;
}
void EnemyBase::Update()
{
}
void EnemyBase::OnBrickContact(TileBrick *tileBrick, ColliderArg e)
{
}
void EnemyBase::ChangeFacingDirection(bool isLeft)
{
	this->isLeft = isLeft;
	if (isLeft) {
		this->SetScale(1, 1);
	}
	else {
		this->SetScale(-1, 1);
	}
}
