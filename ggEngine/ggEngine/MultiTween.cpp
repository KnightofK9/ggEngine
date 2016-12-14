#include "MultiTween.h"
#include "TweenManager.h"
namespace ggEngine {
	MultiTween::MultiTween(std::list<TweenBase*> tweenList, TweenManager * tweenManager) : TweenBase (0,tweenManager)
	{
		this->tweenList = tweenList;
		for (TweenBase* tween : this->tweenList) {
			if (tween->duration > this->duration) {
				this->duration = tween->duration;
			}
		}
	}

	MultiTween::~MultiTween()
	{
		for (TweenBase* tween : this->tweenList) {
			delete tween;
		}
	}
	TweenBase * MultiTween::Start()
	{
		TweenBase::Start();
		for (TweenBase* tween : this->tweenList) {
			tween->Start();
		}
		return this;
	}
	double MultiTween::Update(double dt)
	{
		for (TweenBase* tween : this->tweenList) {
			if (tween->IsAlive()) {
				if (tween->IsPlaying()) {
					tween->Update(dt);
				}
			}
		}
		TweenBase::Update(dt);
		return this->duration;
	}

}
