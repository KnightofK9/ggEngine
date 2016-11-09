#include "Game.h"
#include "Cache.h"
#include "Group.h"
#include "StateManager.h"
#include "State.h"
#include "Physics.h"
#include "Camera.h"
#include "EventManager.h"
#include "DXInput.h"
#include "Input.h"
#include "World.h"
#include "TweenManager.h"
#include "TimeBasedEventManager.h"
namespace ggEngine {
	Game::Game(HWND hWnd ,int width, int height, GameMode mode, PhysicsMode physicsMode, D3DCOLOR gameColor)
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
			timeBasedEventManager = new TimeBasedEventManager(this);
			d3dManager = new D3DManager(this,hWnd, width, height, gameColor, isWindowed);
			stateManager = new StateManager(this);
			camera = new Camera(this, width, height,0,0,true);
			drawManager = new DrawManager(this,camera);
			cache = new Cache(this);
			physics = new Physics(this, physicsMode);
			eventManager = new EventManager(this);
			tweenManager = new TweenManager(this);
			world = new World();
			input = new Input(&hWnd);
			g_debug.Init(this);

			stateManager->SetCache(cache);
			d3dManager->SetDrawManager(drawManager);
			d3dManager->SetStateManager(stateManager);

			input->InitKeyboard();
			input->InitMouse();

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
		this->maximizeProcessor = false;
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
			g_debug.Error("Failed to init D3DManager, D3DERR_INVALIDCALL: Invalid Call or Parameter!");
			break;
		case ERROR_CODE_D3DERR_NOTAVAILABLE:
			g_debug.Error("Failed to init D3DManager, D3DERR_NOTAVAILABLE: Parameter not supported!");
			break;
		case ERROR_CODE_D3DERR_OUTOFVIDEOMEMORY:
			g_debug.Error("Failed to init D3DManager, D3DERR_OUTOFVIDEOMEMORY: Out of Video Memory!");
			break;
		case ERROR_CODE_FAIL_INIT_DRAW_MANAGER_ERROR_UNKNOW:
			g_debug.Error("Failed to init draw manager. Error unknow.");
			break;
		default:
			g_debug.Error("Unknow error " + errorCode);
			break;
		}
	}

	void Game::GameRun()
	{
		//frameCountReal++;
		//if (realTimer.stopwatch(999)) {
		//	frameRateReal = frameCountReal;
		//	frameCountReal = 0;
		//}
		//logicTimer.updateDeltaTime();
		////
		//// Check for state
		////

		//stateManager->LateStart();

		////
		//// Update game logic here
		////
		//gameUpdate();
		//if (this->isRunning) this->stateManager->GetCurrentState()->PreRender();

		////
		//// Render go here
		////
		//this->d3dManager->update();
		//return;
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
			logicTimer.updateDeltaTime();
			//
			// Check for state
			//

			stateManager->LateStart();

			//
			// Update game logic here
			//
			gameUpdate();
			/*if(this->isRunning) this->stateManager->GetCurrentState()->PreRender();*/

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

	void Game::GameCustomRender()
	{
		g_debug.DebugToScreen(0, 0, std::to_string(frameRateReal));

	}

	void Game::gameUpdate()
	{
		//Debug::Log("Frame rate core " + std::to_string(frameRateCore));
		//Debug::Log(frameRateReal);
		//Debug::Log(std::to_string(logicTimer.getDeltaTime()));
		if (isRunning) {
			/*Handle input*/
			input->PollKeyboard();
			eventManager->DispatchKeyBoardEvent(input->keyStates);
			timeBasedEventManager->Update(logicTimer.getDeltaTimeInMilisecond());
			/*State update*/
			
			State *state = stateManager->GetCurrentState();
			state->Update();
			/*Group update*/
			RunGroupUpdate(world->GetGroupList());
			tweenManager->Update(logicTimer.getDeltaTimeInMilisecond());
			/*Physics update*/
			physics->UpdatePhysics();
		}
	}
	
	void Game::RunGroupUpdate(std::list<Group*> *groupList)
	{
		for (std::list<Group*>::iterator it = groupList->begin(); it != groupList->end();) {
			if ((*it)->IsAlive()) {
				std::list<Group*> *groupList = (*it)->GetGroupList();
				(*it)->Update();
				RunGroupUpdate(groupList);
				++it;
			}
			else {
				std::list<Group*>::iterator tempIt = it;
				++it;
				delete ((*tempIt));
				groupList->remove((*tempIt));
			}
		}
	}
	

}
