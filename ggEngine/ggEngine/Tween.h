#pragma once
#include "GGObject.h"
#include <functional>
//#include <claw/tween/single_tweener.hpp>
//#pragma comment(lib,"libclaw_tween.lib")

namespace ggEngine {
	class TweenManager;
	class Tween :public GGObject {
	public:
		Tween(TweenManager* tweenManager, float &val, double end, unsigned int duration, std::function<double(int, double, double, int)> easingFunction);
		~Tween();
		Tween* SetOnFinish(std::function<void()> onFinish);
		bool IsPlaying();
		bool IsFinished();
		void Destroy();
		double Update(double deltaTime);
		Tween* Start();
		Tween* Pause();
		bool IsAlive() { return this->isAlive; }
		//claw::tween::single_tweener* GetClawTweener() { return this->tweener; }
		Tween* CallFinish();
	private:
		//Tween(TweenManager* tweenManager, double init, double end, unsigned int duration, std::function<void(double)> update, std::function<double(double)> easingFunction);
		//claw::tween::single_tweener *tweener = nullptr;
		std::function<void()> onFinish = nullptr;
		TweenManager* tweenManager;
		std::function<double(double, double, double, double)> easingFunction;
		bool isPlaying;
		bool isAlive;
		bool isFinished;
		double startValue;
		double currentTime;
		float &val;
		double end;
		double duration;
		double changeInValue;
	};
}