#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class Factory : public GGObject {
public:
	static GameObject* GetInstanceOf(std::string type);
};