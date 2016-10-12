#include "Easing.h"
namespace ggEngine{
	const std::function<double(int, double, double, int)>  Easing::linearTween = [](int currentTimeInMili, double startValue, double changeInValue, int durationInMili) {
		return changeInValue*currentTimeInMili / durationInMili + startValue;
	};
}