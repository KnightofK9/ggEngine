#pragma once
#include <iostream>
#include <string>
#include "ConstantEnum.h"
#include "Text.h"
namespace ggEngine {
	class Game;
	class Debug {
	public:
		static void Log(GGTEXT message);
		static void Log(std::string message);
		static void Log(std::wstring message);
		static void Log(int number);
		static void Warning(GGTEXT message);
		static void Warning(std::string message);
		static void Warning(std::wstring message);
		static void Warning(int number);
		static void Error(std::string message);
		static void Error(std::wstring message);
		static void DebugToScreen(Game *game, float x, float y, std::string text);
	private:
		Debug() {}
	};
}