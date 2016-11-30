#include "Tween.h"
ggEngine::Tween::Tween(TweenManager* tweenManager, float &val, double end, unsigned int duration, std::function<double(int, double, double, int)> easingFunction) : val(val)
{
	this->end = end;
	this->duration = duration;
	this->tweenManager = tweenManager;
	this->isAlive = true;
	this->isFinished = false;
	this->isPlaying = false;
	this->easingFunction = easingFunction;
	this->startValue = (double)val;
	this->changeInValue = end - val;
	this->currentTime = 0;
}
//Not ready to use yet
ggEngine::Tween::Tween(TweenManager* tweenManager, float init, double end, unsigned int duration, std::function<void(double)> onUpdate, std::function<double(int, double, double, int)> easingFunction) :val(currentValue)
{
	this->end = end;
	this->duration = duration;
	this->tweenManager = tweenManager;
	this->isAlive = true;
	this->isFinished = false;
	this->isPlaying = false;
	this->easingFunction = easingFunction;
	this->startValue = (double)init;
	this->changeInValue = end - init;
	this->currentTime = 0;
	this->onUpdate = onUpdate;
}

ggEngine::Tween::~Tween()
{
	
}

ggEngine::Tween* ggEngine::Tween::SetOnFinish(std::function<void()> onFinish)
{
	this->onFinish = onFinish;
	return this;
}

bool ggEngine::Tween::IsPlaying()
{
	return this->isPlaying;
}

bool ggEngine::Tween::IsFinished()
{
	return this->isFinished;
}

void ggEngine::Tween::Destroy()
{
	this->isPlaying = false;
	GGObject::Destroy();
}

double ggEngine::Tween::Update(double deltaTime)
{
	this->val = easingFunction(this->currentTime, this->startValue, this->changeInValue, this->duration);
	currentTime += deltaTime;
	if (currentTime > duration) {
		this->isFinished = true;
		this->isPlaying = false;
		CallFinish();
	}
	if (this->onUpdate != nullptr) {
		onUpdate(val);
	}
	return this->val;
}

ggEngine::Tween* ggEngine::Tween::Start()
{
	this->currentTime = 0;
	this->isPlaying = true;
	return this;
}

ggEngine::Tween* ggEngine::Tween::Pause()
{
	this->isPlaying = false;
	return this;
}

ggEngine::Tween* ggEngine::Tween::CallFinish()
{
	this->isPlaying = false;
	this->isFinished = true;
	this->val = end;
	if (this->onFinish != nullptr) onFinish();
	return this;
}
