#pragma once
#include <string>
namespace ggEngine {
	class IValuable {
	public:
		virtual std::string GetValue() = 0;
	};
}