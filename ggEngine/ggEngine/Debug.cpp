#include "Debug.h"
#include "Game.h"
#include "Cache.h"
namespace ggEngine {
	Debug g_debug;
	Debug::Debug()
	{
	}
	void Debug::Init(Game * game)
	{
		Debug::game = game;
		Debug::defaultFont = new Font(game->GetDrawManager(), "Arial", 24, false, FW_BOLD);
	}
	Debug::~Debug()
	{
		if (Debug::defaultFont != NULL) {
			delete Debug::defaultFont;
			Debug::defaultFont = NULL;
		}
	}
	void Debug::Log(GGTEXT message)
	{
		std::wcout << message << "\n";
	}
	void Debug::Log(std::string message)
	{
		std::cout << message << "\n";
	}
	void Debug::Log(std::wstring message)
	{
		std::wcout << message << "\n";
	}
	void Debug::Log(int number)
	{
		std::cout << number << "\n";
	}

	void Debug::Warning(GGTEXT message)
	{
		std::wcout << message << "\n";
	}
	void Debug::Warning(std::string message)
	{
		std::cout << message << "\n";
	}
	void Debug::Warning(std::wstring message)
	{
		std::wcout << message << "\n";
	}
	void Debug::Warning(int number)
	{
		std::cout << number << "\n";
	}
	void Debug::Error(std::string message)
	{
		std::cout << message << "\n";
	}
	void Debug::Error(std::wstring message)
	{
		std::wcout << message << "\n";
	}
	void Debug::DebugToScreen(double x, double y, std::string text)
	{
		Debug::defaultFont->Draw(x, y, text);
	}
	DWORD Debug::GetDtMs()
	{
		return game->logicTimer.getDeltaTimeInMilisecond();
	}
}
