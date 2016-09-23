#include "Game.h"
#include "Cache.h"
#include "Group.h"
#include "StateManager.h"
#include "State.h"
namespace ggEngine {
	Game::Game(HWND hWnd ,int width, int height, GameMode mode, D3DCOLOR gameColor)
	{
		bool isWindowed = false;
		isRunning = false;
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
			cache = new Cache(this);
			stateManager = new StateManager(this);
			drawManager = new DrawManager(this);
			d3dManager->SetDrawManager(drawManager);
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
		frameCountCore++;
		if (coreTimer.stopwatch(999)) {
			frameRateCore = frameCountCore;
			frameCountCore = 0;
		}
		if (!timeUpdate.stopwatch(MILISECOND_PER_UPDATE)) {
			if (!this->maximizeProcessor) {
				Sleep(1);
			}
		}
		else {
			frameCountReal++;
			if (realTimer.stopwatch(999)) {
				frameRateReal = frameCountReal;
				frameCountReal = 0;
			}
			//
			// Update game logic here
			//
			gameUpdate();
			//
			// Render go here
			//
			this->d3dManager->update();
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
		//Debug::Log(frameRateReal);
		if (isRunning) {
			State *state = stateManager->GetCurrentState();
			state->Update();
			RunGroupUpdate(state->GetGroupList());
		}
	}

	void Game::RunGroupUpdate(std::list<Group*> groupList)
	{
		for (std::list<Group*>::iterator it = groupList.begin(); it != groupList.end(); ++it) {
			std::list<Group*> groupList = (*it)->GetGroupList();
			(*it)->Update();
			RunGroupUpdate(groupList);
		}
	}

	

}
