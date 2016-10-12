#pragma once
#include <functional>
namespace ggEngine {
	class Easing {
	public:
	/*	static const std::function<double(int, double, double, int)> linearTween = [](int currentTimeInMili, double startValue, double changeInValue, int durationInMili) {
			return changeInValue*currentTimeInMili / durationInMili + startValue;
		};*/
		static double linearTween(int currentTimeInMili, double startValue, double changeInValue, int durationInMili) {
			return changeInValue*currentTimeInMili / durationInMili + startValue;
		};
	};
}