#include "AI7.h"
#include "TypeEnum.h"
AI7::AI7(CVGame * cvGame, SpriteInfo * spriteInfo) : TweenEnemyBase(cvGame, spriteInfo, 32, 64)
{
	this->name = "AI7";
	SetAnchor(0, 0);
	this->rigidBodyHeight = 10;
	this->body->SetHeight(this->rigidBodyHeight);
	this->body->rigidBody->SetAnchor(0, -6);
	this->body->immoveable = false;
	this->body->allowGravity = false;
	this->body->SetPhysicsMode(PhysicsMode_AABB);
	SetMoveY(GetHeight());
	SetSpeed(0.5);
	this->isRunning = true;
	//this->tag = ObjectType_AI7;
}

AI7::~AI7()
{
}
/*
*  Mean run up
*/
void AI7::RunLeft()
{
	this->isRunning = true;
	this->isRunUp = true;
}
/*
*  Mean run down
*/
void AI7::RunRight()
{
	this->isRunning = true;
	this->isRunUp = false;
}

void AI7::Update()
{
	if (this->isRunning) {
		if (this->position.y <= this->upLimitPosition.y + this->rigidBodyHeight) {
			RunRight();
		}
		else if (this->position.y >= this->spawnPosition.y) {
			RunLeft();
		}
		int modifier = 1;
		if (this->isRunUp) modifier = -1;
		this->position.y += modifier* this->speed;
	}
}

void AI7::Active()
{
	EnemyBase::Active();
}

void AI7::SetPosition(Vector position)
{
	GameObject::SetPosition(position);
	this->spawnPosition = position;
	this->upLimitPosition = spawnPosition;
	this->upLimitPosition.y -= this->moveY;
}

void AI7::Draw()
{
	if (!visible) return;
	Transform(spriteHandle);
	double drawMaskY = this->position.y - this->upLimitPosition.y ;
	drawMaskY = GetHeight() - drawMaskY;
	srcRect.top = drawMaskY;
	D3DXVECTOR3 position;
	position.x = 0;
	position.z = 0;
	position.y = drawMaskY;
	//if (!visible) return;
	if (spriteHandle->Begin(this->style) == D3D_OK)
	{
		color = (color & 0x00FFFFFF) | (opacity << 24);
		spriteHandle->Draw(this->GetImage()->GetTexture()->GetDxTexture(), &srcRect, NULL, &position, color);
		spriteHandle->End();
	}
}
