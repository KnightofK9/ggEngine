#pragma once
#include <d3d9.h>
#include <string>
class Helper {
public:
	static LPCWSTR StringToLPCWSTR(const std::string &s);
private:
	Helper() {}
};