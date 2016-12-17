#pragma once
#include "GGObject.h"
#include <string>
namespace ggEngine {
	class Block : public GGObject {
	public:
		Block(double x, double y, double width, double height, std::string name);
	private:
	};
}