#pragma once
#include "GGObject.h"
#include <functional>
#include "TweenManager.h"
class TweenManager;
namespace ggEngine {
	class TweenBase : public GGObject {
	public:
		TweenBase(double duration, TweenManager *tweenManager);
		virtual TweenBase* SetOnFinish(std::function<void()> onFinish);
		virtual TweenBase* Start();
		virtual TweenBase* Pause();
		virtual TweenBase* Resume();
		virtual TweenBase* CallFinish();
		virtual TweenBase* Stop();

		//TO DO
		virtual TweenBase* Reset();
		virtual TweenBase* GetRevert();
		bool IsPlaying();
		bool IsFinished();

		void Destroy();
		virtual double Update(double deltaTime);
		bool IsAlive() { return this->isAlive; }
		double duration;
	protected:
		double currentTime;
		bool isPlaying;
		bool isAlive;
		bool isFinished;
		TweenManager* tweenManager;

		std::function<void()> onFinish = nullptr;
	};
}