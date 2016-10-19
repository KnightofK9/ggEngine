#pragma once
#include <string>
#include "Json.h"
namespace ggEngine {
	class IJsonable {
	public:
		virtual void CreateJson(std::string location) = 0;
		virtual void ParseJson(std::string location) = 0;
	};
}