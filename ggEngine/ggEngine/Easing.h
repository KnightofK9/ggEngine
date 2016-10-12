#pragma once
#include <functional>
namespace ggEngine {
	class Easing {
	public:
		static const std::function<double(double, double, double, double)> linearTween;
		static const std::function<double(double, double, double, double)> easeInQuad;
		static const std::function<double(double, double, double, double)> easeOutQuad;
		static const std::function<double(double, double, double, double)> easeInOutQuad;
		static const std::function<double(double, double, double, double)> easeInCubic;
		static const std::function<double(double, double, double, double)> easeOutCubic;
		static const std::function<double(double, double, double, double)> easeInOutCubic;
		static const std::function<double(double, double, double, double)> easeInQuart;
		static const std::function<double(double, double, double, double)> easeOutQuart;
		static const std::function<double(double, double, double, double)> easeInOutQuart;
		static const std::function<double(double, double, double, double)> easeInQudouble;
		static const std::function<double(double, double, double, double)> easeOutQudouble;
		static const std::function<double(double, double, double, double)> easeInOutQudouble;
		static const std::function<double(double, double, double, double)> easeInSine;
		static const std::function<double(double, double, double, double)> easeOutSine;
		static const std::function<double(double, double, double, double)> easeInOutSine;
		static const std::function<double(double, double, double, double)> easeInExpo;
		static const std::function<double(double, double, double, double)> easeOutExpo;
		static const std::function<double(double, double, double, double)> easeInOutExpo;
		static const std::function<double(double, double, double, double)> easeInCirc;
		static const std::function<double(double, double, double, double)> easeOutCirc;
		static const std::function<double(double, double, double, double)> easeInOutCirc;
		
		//static double linearTween(double currentTimeInMili, double startValue, double changeInValue, double durationInMili) {
		//	return changeInValue*currentTimeInMili / durationInMili + startValue;
		//};
	};
}