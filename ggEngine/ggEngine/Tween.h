#pragma once
#include "TweenBase.h"
#include <functional>
//#include <claw/tween/single_tweener.hpp>
//#pragma comment(lib,"libclaw_tween.lib")

namespace ggEngine {
	class TweenManager;
	class Tween :public TweenBase {
	public:
		Tween(TweenManager* tweenManager, float &val, double end, unsigned int duration, std::function<double(int, double, double, int)> easingFunction);
		Tween(TweenManager* tweenManager, float init, double end, unsigned int duration, std::function<void(double)> onUpdate, std::function<double(int, double, double, int)> easingFunction);
		virtual ~Tween();
		double Update(double dt) override;
		TweenBase* CallFinish() override;
	
		//claw::tween::single_tweener* GetClawTweener() { return this->tweener; }
	private:
		//claw::tween::single_tweener *tweener = nullptr;

		std::function<void(double)> onUpdate = nullptr;
		double startValue;
		float &val;
		double end;
		double changeInValue;
		float currentValue = 0;
		std::function<double(double, double, double, double)> easingFunction;
	};
}