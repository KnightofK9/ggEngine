#include "TweenBase.h"
namespace ggEngine {
	TweenBase::TweenBase(double duration,TweenManager * tweenManager)
	{
		this->tweenManager = tweenManager;
		this->isAlive = true;
		this->isFinished = false;
		this->isPlaying = false;
		this->duration = duration;
	}
	TweenBase* TweenBase::SetOnFinish(std::function<void()> onFinish)
	{
		this->onFinish = onFinish;
		return this;
	}

	bool TweenBase::IsPlaying()
	{
		return this->isPlaying;
	}

	bool TweenBase::IsFinished()
	{
		return this->isFinished;
	}

	bool TweenBase::IsLoop()
	{
		return this->isLoop;
	}

	void TweenBase::Destroy()
	{
		this->isPlaying = false;
		GGObject::Destroy();
	}

	double TweenBase::Update(double deltaTime)
	{
		currentTime += deltaTime;
		if (currentTime > duration) {
			this->isFinished = true;
			this->isPlaying = false;
			CallFinish();
		}
		return currentTime;
	}

	TweenBase* TweenBase::Start()
	{
		this->currentTime = 0;
		this->isPlaying = true;
		return this;
	}

	TweenBase* TweenBase::Pause()
	{
		this->isPlaying = false;
		return this;
	}
	TweenBase * TweenBase::Resume()
	{
		this->isPlaying = true;
		return this;
	}
	TweenBase * TweenBase::CallFinish()
	{
		if (this->onFinish != nullptr) onFinish();
		return this;
	}
	TweenBase * TweenBase::Stop()
	{
		this->isAlive = false;
		return this;
	}
	TweenBase * TweenBase::Restart()
	{
		this->currentTime = 0;
		this->isPlaying = true;
		this->isFinished = false;
		return this;
	}
	TweenBase * TweenBase::SetLoop(bool isLoop)
	{
		this->isLoop = isLoop;
		return this;
	}
	TweenBase * TweenBase::GetRevert()
	{
		return this;
	}
}
