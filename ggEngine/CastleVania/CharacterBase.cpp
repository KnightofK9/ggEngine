#include "CharacterBase.h"

CharacterBase::CharacterBase(CVGame *cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame):CVSpriteAnimation(cvGame,image,frameWidth,frameHeight,defaultFrame,numberOfFrame,msPerFrame)
{

}

CharacterBase::~CharacterBase()
{
}

void CharacterBase::MoveLeft()
{
}

void CharacterBase::MoveRight()
{
}

void CharacterBase::ChangeFacingDirection(bool isLeft)
{
	this->isLeft = isLeft;
	if (isLeft) {
		this->SetScale(1, 1);
	}
	else {
		this->SetScale(-1, 1);
	}
}
