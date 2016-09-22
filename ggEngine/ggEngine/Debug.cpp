#include "Debug.h"
namespace ggEngine {
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
}
