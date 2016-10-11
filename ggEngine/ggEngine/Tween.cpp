#include "Tween.h"

ggEngine::Tween::Tween(TweenManager* tweenManager,double & val, double end, double duration, boost::function<double(double)> easingFunction)
{
	this->tweenManager = tweenManager;
	this->tweener = new claw::tween::single_tweener(val, end, duration, easingFunction);
	this->tweener->on_finished([this]() {
		this->CallFinish();
	});
	this->isAlive = true;
}

ggEngine::Tween::Tween(TweenManager* tweenManager, double init, double end, double duration, std::function<void(double)> update, boost::function<double(double)> easingFunction)
{
	this->tweenManager = tweenManager;
	this->tweener = new claw::tween::single_tweener(init, end, duration, update, easingFunction);
	this->tweener->on_finished([this]() {
		this->CallFinish();
	});
	this->isAlive = true;
}

ggEngine::Tween::~Tween()
{
	if (this->tweener != nullptr) {
		delete this->tweener;
		this->tweener = nullptr;
	}
}

void ggEngine::Tween::SetOnFinish(std::function<void()> onFinish)
{
	this->onFinish = onFinish;
}

bool ggEngine::Tween::IsPlaying()
{
	return this->isPlaying;
}

bool ggEngine::Tween::IsFinished()
{
	return this->tweener->is_finished();
}

void ggEngine::Tween::Destroy()
{
	this->isAlive = false;
	this->isPlaying = false;
}

void ggEngine::Tween::Start()
{
	this->isPlaying = true;
}

void ggEngine::Tween::Pause()
{
	this->isPlaying = false;
}

void ggEngine::Tween::CallFinish()
{
	this->isPlaying = false;
	if (this->onFinish != nullptr) onFinish();
}
