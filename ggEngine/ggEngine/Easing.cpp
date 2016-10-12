#include "Easing.h"
#include "ConstantEnum.h"
namespace ggEngine{
	const std::function<double(double, double, double, double)>  Easing::linearTween = [](double t, double b, double c, double d) {
		return c*t / d + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInQuad = [](double t, double b, double c, double d) {
		t /= d;
		return c*t*t + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeOutQuad = [](double t, double b, double c, double d) {
		t /= d;
		return -c * t*(t - 2) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInOutQuad = [](double t, double b, double c, double d) {
		t /= d / 2;
		if (t < 1) return c / 2 * t*t + b;
		t--;
		return -c / 2 * (t*(t - 2) - 1) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInCubic = [](double t, double b, double c, double d) {
		t /= d;
		return c*t*t*t + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeOutCubic = [](double t, double b, double c, double d) {
		t /= d;
		t--;
		return c*(t*t*t + 1) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInOutCubic = [](double t, double b, double c, double d) {
		t /= d / 2;
		if (t < 1) return c / 2 * t*t*t + b;
		t -= 2;
		return c / 2 * (t*t*t + 2) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInQuart = [](double t, double b, double c, double d) {
		t /= d;
		return c*t*t*t*t + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeOutQuart = [](double t, double b, double c, double d) {
		t /= d;
		t--;
		return -c * (t*t*t*t - 1) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInOutQuart = [](double t, double b, double c, double d) {
		t /= d / 2;
		if (t < 1) return c / 2 * t*t*t*t + b;
		t -= 2;
		return -c / 2 * (t*t*t*t - 2) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInQudouble = [](double t, double b, double c, double d) {
		t /= d;
		return c*t*t*t*t*t + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeOutQudouble = [](double t, double b, double c, double d) {
		t /= d;
		t--;
		return c*(t*t*t*t*t + 1) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInOutQudouble = [](double t, double b, double c, double d) {
		t /= d / 2;
		if (t < 1) return c / 2 * t*t*t*t*t + b;
		t -= 2;
		return c / 2 * (t*t*t*t*t + 2) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInSine = [](double t, double b, double c, double d) {
		return -c * cos(t / d * ( MATH_PI/ 2)) + c + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeOutSine = [](double t, double b, double c, double d) {
		return c * sin(t / d * (MATH_PI / 2)) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInOutSine = [](double t, double b, double c, double d) {
		return -c / 2 * (cos(MATH_PI*t / d) - 1) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInExpo = [](double t, double b, double c, double d) {
		return c * pow(2, 10 * (t / d - 1)) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeOutExpo = [](double t, double b, double c, double d) {
		return c * (-pow(2, -10 * t / d) + 1) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInOutExpo = [](double t, double b, double c, double d) {
		t /= d / 2;
		if (t < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
		t--;
		return c / 2 * (-pow(2, -10 * t) + 2) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInCirc = [](double t, double b, double c, double d) {
		t /= d;
		return -c * (sqrt(1 - t*t) - 1) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeOutCirc = [](double t, double b, double c, double d) {
		t /= d;
		t--;
		return c * sqrt(1 - t*t) + b;
	};
	const std::function<double(double, double, double, double)>  Easing::easeInOutCirc = [](double t, double b, double c, double d) {
		t /= d / 2;
		if (t < 1) return -c / 2 * (sqrt(1 - t*t) - 1) + b;
		t -= 2;
		return c / 2 * (sqrt(1 - t*t) + 1) + b;
	};
}