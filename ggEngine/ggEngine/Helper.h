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
		static RECT intersectRectAndGroup(RECT &srcRect, GameObject *go, Group *group);
		static string IntToString(const int &number, int numCharWidth);
		static int GetRamdomIntNumber(int min = 0, int max = 1000);
	private:
		Helper() {}
	};
}
