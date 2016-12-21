#include "EnemyBase.h"
#include "Simon.h"
#include "CVGame.h"
EnemyBase::EnemyBase(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame):CVSpriteAnimation(cvGame,image, frameWidth,frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->tag = ObjectType_Enemy;
	cvGame->physics->AttachBodyTo(this);
	this->body->SetPhysicsMode(PhysicsMode_AABBSwept);
	this->body->CreateRectangleRigidBody(GetWidth(), GetHeight());
	this->events->onCheckingCollide = [this](GameObject* go, ColliderArg e) {
		return OnCheckingCollide(e);
	};
	this->events->onOverlap = [this](GameObject* go, ColliderArg e) {
		auto otherObject = e.colliderObject;
		Tag tag = otherObject->tag;
		switch (tag) {
		case ObjectType_Simon:
			OnSimonContact(dynamic_cast<Simon*>(otherObject), e);
			break;
		}
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
	auto otherObject = e.colliderObject;
	Tag tag = otherObject->tag;
	switch (tag) {
	case ObjectType_LevelTwoBrick:
		if (e.blockDirection.up) return true;
		return false;
	default:
		return false;
	}
	return false;
}
