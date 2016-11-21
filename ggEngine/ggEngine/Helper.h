#pragma once
#include <d3d9.h>
#include <string>
#include "GameObject.h"
namespace ggEngine {
	class Group;
	class Helper {
	public:
		static LPCWSTR StringToLPCWSTR(const std::string &s);
		static std::string WCharToString(const LPCWSTR s);
		static RECT intersectRectAndGroup(RECT &srcRect,GameObject *go, Group *group);
	private:
		Helper() {}
	};
}
