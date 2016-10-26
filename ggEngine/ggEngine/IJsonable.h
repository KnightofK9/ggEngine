#pragma once
#include <string>
#include "Json.h"
namespace ggEngine {
	class IJsonable {
	public:
		void SaveJsonTo(std::string location);
		void ParseJsonFrom(std::string location);
		virtual void ParseJson(std::string jsonChar) = 0;
		virtual std::string CreateJson() = 0;
	};
}