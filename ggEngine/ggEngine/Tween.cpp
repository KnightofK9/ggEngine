#include "Tween.h"
ggEngine::Tween::Tween(TweenManager* tweenManager, float &val, double end, unsigned int duration, std::function<double(int, double, double, int)> easingFunction) : val(val), TweenBase(duration, tweenManager)
{
	this->end = end;
	this->easingFunction = easingFunction;
	this->startValue = (double)val;
	this->changeInValue = end - val;
	this->currentTime = 0;
}
//Not ready to use yet
ggEngine::Tween::Tween(TweenManager* tweenManager, float init, double end, unsigned int duration, std::function<void(double)> onUpdate, std::function<double(int, double, double, int)> easingFunction) :val(currentValue) , TweenBase(duration, tweenManager)
{
	this->end = end;
	this->easingFunction = easingFunction;
	this->startValue = (double)init;
	this->changeInValue = end - init;
	this->currentTime = 0;
	this->onUpdate = onUpdate;
}

ggEngine::Tween::~Tween()
{
	
}


double ggEngine::Tween::Update(double deltaTime)
{
	this->val = easingFunction(this->currentTime, this->startValue, this->changeInValue, this->duration);
	TweenBase::Update(deltaTime);
	if (this->onUpdate != nullptr) {
		onUpdate(val);
	}
	return this->val;
}


ggEngine::TweenBase* ggEngine::Tween::CallFinish()
{
	this->isPlaying = false;
	this->isFinished = true;
	this->val = end;
	if (this->onFinish != nullptr) onFinish();
	return this;
}
