#pragma once
#include <string>
#include "Json.h"
namespace ggEngine {
	class IJsonable {
	public:
		void SaveJsonTo(std::string location);
		void ParseJson(std::string location);
		virtual void ParseJson(const char* jsonChar) = 0;
		virtual const char* CreateJson() = 0;
	};
}