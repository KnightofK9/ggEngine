#include "Monkey.h"
#include "Simon.h"
Monkey::Monkey(CVGame * cvGame, SpriteInfo * image) : EnemyBase(cvGame, image, 16, 16, 0, 2, 200)
{
	CreateAnimation("move", 0, 1, true);
	this->body->SetActive(true);
	this->body->allowGravity = true;

	this->jumpForce  = 3;
	this->highJumpForce = 3;
	this->jumpDirection = Vector(1,-1);
	this->highJumpDirection = Vector(0.3,-1);
	this->isGrounding = false;
	this->distanceUntilToJumpHigh = 25;

}

Monkey::~Monkey()
{
}

void Monkey::Active()
{
	EnemyBase::Active();
	this->PlayAnimation("move");
}

void Monkey::Update()
{
	EnemyBase::Update();
	if (isGrounding) {
		Vector simonPosition = this->simon->position;
		double distance = this->position.x - simonPosition.x;
		bool isLeft = distance > 0;
		bool isHighJump = distance < this->distanceUntilToJumpHigh;
		Jump(isLeft, isHighJump);
	}

	this->isGrounding = false;
}

bool Monkey::OnCheckingCollide(ColliderArg e)
{
	Tag tag = e.colliderObject->tag;
	switch (tag) {
	case ObjectType_LevelTwoBrick:
		if (e.blockDirection.down) {
			this->isGrounding = true;
			return true;
		}
		if (e.blockDirection.left || e.blockDirection.right) {
			return true;
		}
		break;
	}
	return false;
}

void Monkey::Jump(bool isLeft, bool isHighJump)
{
	int modifier = 1;
	if (isLeft) {
		modifier = -1;
	}
	ChangeFacingDirection(isLeft);
	double force = isHighJump ? this->highJumpForce : this->jumpForce;
	Vector direction = isHighJump ? this->highJumpDirection : this->jumpDirection;
	direction = direction * Vector(modifier,1);
	this->body->SetForce(force, direction);
}
