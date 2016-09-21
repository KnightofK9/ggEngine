#include "Game.h"
namespace ggEngine {
	Game::Game(HWND hWnd ,int width, int height, GameMode mode, D3DCOLOR gameColor)
	{
		bool isWindowed = false;
		switch (mode) {
		case GameMode_FullScreen:
			isWindowed = false;
			break;
		case GameMode_Windowed:
			isWindowed = true;
			break;
		default:
			break;
		}
		try {
			d3dManager = new D3DManager(hWnd, width, height, gameColor, isWindowed);
			//drawManager = new DrawManager();
		}
		catch (int errorCode) {
			ErrorCheck(errorCode);
		}
		this->hWnd = hWnd;
		//
		// Init default value
		//
		this->frameCountCore = 0;
		this->frameCountReal = 0;
		this->frameRateCore = 0;
		this->frameRateReal = 0;
		this->maximizeProcessor = true;
		this->pauseMode = false;
	}
	Game::~Game()
	{
		Destroy();
	}

	void Game::ErrorCheck(int errorCode)
	{
		switch (errorCode) {
		case ERROR_CODE_D3DERR_INVALIDCALL:
			Debug::Error("Failed to init D3DManager, D3DERR_INVALIDCALL: Invalid Call or Parameter!");
			break;
		case ERROR_CODE_D3DERR_NOTAVAILABLE:
			Debug::Error("Failed to init D3DManager, D3DERR_NOTAVAILABLE: Parameter not supported!");
			break;
		case ERROR_CODE_D3DERR_OUTOFVIDEOMEMORY:
			Debug::Error("Failed to init D3DManager, D3DERR_OUTOFVIDEOMEMORY: Out of Video Memory!");
			break;
		case ERROR_CODE_FAIL_INIT_DRAW_MANAGER_ERROR_UNKNOW:
			Debug::Error("Failed to init draw manager. Error unknow.");
			break;
		default:
			Debug::Error("Unknow error " + errorCode);
			break;
		}
	}

	void Game::GameRun()
	{
		frameCountReal++;
		if (realTimer.stopwatch(999)) {
			frameRateReal = frameCountReal;
			frameCountReal = 0;
		}
		//
		// Render go here
		//
		this->d3dManager->update();
		//
		// Update game logic here
		//
		if (!timeUpdate.stopwatch(MILISECOND_PER_UPDATE)) {
			if (!this->maximizeProcessor) {
				Sleep(1);
			}
		}
		else {
			frameCountCore++;
			if (coreTimer.stopwatch(999)) {
				frameRateCore = frameCountCore;
				frameCountCore = 0;
			}
			gameUpdate();
			
		}
	}

	void Game::Destroy()
	{
		d3dManager->Destroy();
		d3dManager = NULL;
	}

	void Game::gameUpdate()
	{
		//Debug::Log("Frame rate core " + frameRateCore);
		Debug::Log(frameRateReal);
	}

}
