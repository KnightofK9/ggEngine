#include "CVSpriteAnimation.h"
#include "CVGame.h"
CVSpriteAnimation::CVSpriteAnimation(CVGame *cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame) :SpriteAnimation(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->cvGame = cvGame;
}

CVSpriteAnimation::~CVSpriteAnimation()
{
}

TimeBasedEventInfo* CVSpriteAnimation::FlickeringAnimation(int delay, int duration, std::function<void()> onFinish)
{
	this->onFinishFlicker = onFinish;
	int numberOfLoop = duration / delay;
	this->flickeringAnim = this->cvGame->add->Loop(delay, numberOfLoop, [this] {
		this->SetVisible(!this->IsVisible());
		if (this->flickeringAnim->numberOfLoops <= 1)
			this->onFinishFlicker();
	});
	return this->flickeringAnim;
}

TimeBasedEventInfo* CVSpriteAnimation::FlickeringChangeColorAnimation(int delay, int duration, std::function<void()> onFinish)
{
	this->onFinishFlickerChangeColor = onFinish;
	int numberOfLoop = duration / delay;
	this->flickeringChangeColorAnim = this->cvGame->add->Loop(delay, numberOfLoop, [this] {
		switch (this->rgbKey) {
		case 1:
			this->SetColorTint(255, 102, 102);
			this->rgbKey++;
			break;

		case 2:
			this->SetColorTint(255, 165, 0);
			this->rgbKey++;
			break;

		case 3:
			this->SetColorTint(243, 250, 253);
			this->rgbKey++;
			break;

		case 4:
			this->SetColorTint(255, 255, 255);
			this->rgbKey++;
			break;

		case 5:
			this->SetColorTint(74, 1, 238);
			this->rgbKey = 1;
			break;
		}

		if (this->flickeringChangeColorAnim->numberOfLoops <= 1) {
			this->SetColorTint(255, 255, 255);
			this->onFinishFlickerChangeColor();
		}
	});
	return this->flickeringChangeColorAnim;
}

TimeBasedEventInfo* CVSpriteAnimation::FlickeringChangeColorAnimationInfinity(int delay)
{
	return this->cvGame->add->LoopInfinity(delay, [this] {
		switch (this->rgbKey) {
		case 1:
			this->SetColorTint(255, 102, 102);
			this->rgbKey++;
			break;

		case 2:
			this->SetColorTint(255, 165, 0);
			this->rgbKey++;
			break;

		case 3:
			this->SetColorTint(243, 250, 253);
			this->rgbKey++;
			break;

		case 4:
			this->SetColorTint(255, 255, 255);
			this->rgbKey++;
			break;

		case 5:
			this->SetColorTint(74, 1, 238);
			this->rgbKey = 1;
			break;
		}
	});
}

