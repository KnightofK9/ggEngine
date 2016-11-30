#pragma once
#include "GGObject.h"
namespace ggEngine {
	class ComponentBase : public GGObject {
	public:
		virtual void Update(double dt) = 0;
		virtual void Reset() = 0;
	};
}