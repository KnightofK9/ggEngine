#pragma once
#include <iostream>
#include <string>
#include "ConstantEnum.h"
#include "Text.h"
namespace ggEngine {
	class Game;
	class Debug {
	public:
		Debug();
		void Init(Game *game);
		virtual ~Debug();
		void Log(GGTEXT message);
		void Log(std::string message);
		void Log(std::wstring message);
		void Log(int number);
		void Warning(GGTEXT message);
		void Warning(std::string message);
		void Warning(std::wstring message);
		void Warning(int number);
		void Error(std::string message);
		void Error(std::wstring message);
		void DebugToScreen(double x, double y,std::string text);
		DWORD GetDtMs();
	private:
		Font *defaultFont;
		Game* game;
	};
	extern Debug g_debug;
}