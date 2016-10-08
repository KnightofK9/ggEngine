#pragma once
#include <d3d9.h>
#include <string>
class Helper {
public:
	static LPCWSTR StringToLPCWSTR(const std::string &s);
	static std::string WCharToString(const LPCWSTR s);
private:
	Helper() {}
};