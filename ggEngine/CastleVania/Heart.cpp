#include "Heart.h"
#include "Simon.h"
#include "AudioManager.h"
#include "CVGame.h"
Heart::Heart(CVGame *cvgame, SpriteInfo * image): ItemBase(cvgame,image)
{
	//audio = cvGame->cvAdd->Audio("Resource//Test//sound.wav");
	this->moveX = (30);
	this->moveY = (0.05);
}

Heart::~Heart()
{
	if (loopMovingSin != nullptr) {
		loopMovingSin->Stop();
		loopMovingSin = nullptr;
	}
}

void Heart::Active()
{
	ItemBase::Active();
	if (loopMovingSin != nullptr) {
		loopMovingSin->Stop();
		loopMovingSin = nullptr;
	}
	//loopMovingSin = this->cvGame->add->LoopInfinity(0, [this]() {
	//	double y = this->position.y - this->startPosition.y;
	//	double increaseX = this->moveX*(sin(y*moveY));
	//	this->position.x = this->startPosition.x + increaseX;
	//});
}

void Heart::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->IncreaseHeartPoint(this->point);
	simon->audioManager->collectHeartSound->Play();
	Destroy();
}

//void Heart::SetPosition(Vector position, bool isRefresh)
//{
//	this->startPosition = position;
//	GameObject::SetPosition(position, isRefresh);
//}
