#include "Simon.h"

Simon::Simon(DrawManager * drawManager, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame) : CharacterBase(drawManager, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->tag = ObjectType_Simon;
	this->health = 16;
	this->isGrounding = true;
}

Simon::~Simon()
{
}

void Simon::SetHealth(int heath)
{
	this->health = health;
}

void Simon::Idle()
{
	this->PlayAnimation("idle");
	this->body->velocity.x = 0;
}

void Simon::MoveLeft()
{
	this->PlayAnimation("move");
	this->SetScale(1, 1);
	this->body->velocity.x = -CharacterConstant::SIMON_MOVE_FORCE;
}

void Simon::MoveRight()
{
	this->PlayAnimation("move");
	this->SetScale(-1, 1);
	this->body->velocity.x = CharacterConstant::SIMON_MOVE_FORCE;
}

void Simon::Jump()
{
	if (isGrounding)
	{
		this->PlayAnimation("kneel");
		this->body->velocity.y = -CharacterConstant::SIMON_JUMP_FORCE;
		//isGrounding = false;
	}
}

void Simon::Kneel()
{
	this->PlayAnimation("kneel");
	this->body->velocity.x = 0;
}

void Simon::ClimbUp()
{
	this->PlayAnimation("climbUp");
}

void Simon::ClimbDown()
{
	this->PlayAnimation("climbDown");
}

void Simon::Hurt()
{
	this->PlayAnimation("hurt");
}

void Simon::Death()
{
	this->PlayAnimation("death");
	this->body->velocity.x = 0;
}

void Simon::StandAttack()
{
	this->PlayAnimation("standAttack");
	this->body->velocity.x = 0;
}

void Simon::KneelAttack()
{
	this->PlayAnimation("kneelAttack");
	this->body->velocity.x = 0;
}

void Simon::ClimbDownAttack()
{
	this->PlayAnimation("climbDownAttack");
}

void Simon::ClimbUpAttack()
{
	this->PlayAnimation("climbUpAttack");
}

void Simon::LoseHealth(int health)
{
	this->health -= health;
	infoPanel->SetPlayerHealth(this->health);
}

void Simon::GainHealth(int health)
{
	this->health += health;
	infoPanel->SetPlayerHealth(this->health);
}
