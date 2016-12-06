#pragma once
#include "D3DManager.h"
#include "Timer.h"
#include "ConstantEnum.h"
#include "Debug.h"
#include "GGObject.h"
#include "DrawManager.h"
#include "IGetGroup.h"
namespace ggEngine {
	class TimeBasedEventManager;
	class TweenManager;
	class EventManager;
	class Camera;
	class Physics;
	class StateManager;
	class Cache;
	class Input;
	class World;
	class CameraEventManager;
	class MemoryManager;
	class Add;
	class Preload;
	class Game :public GGObject, public IGetGroup {
	public:
		Game(HWND hWnd, int width, int height, GameMode mode = GameMode_Windowed, PhysicsMode physicsMode = PhysicsMode_AABB,D3DCOLOR gameColor = D3DCOLOR_XRGB(0, 255, 255));
		virtual ~Game();
		void GameCustomRender();
		void GameRun();
		D3DManager *GetD3DManager() { return this->d3dManager; }
		DrawManager *GetDrawManager() { return this->drawManager; }
		std::list<Group*> *GetGroupList() { return &this->topGroupList; }
		Cache  *cache;
		StateManager *stateManager;
		Physics *physics;
		void SetRunning(bool isRunning) { this->isRunning = isRunning; }
		bool IsRunning() { return this->isRunning; }
		Timer logicTimer;
		EventManager *eventManager;
		long frameRateReal;
		long frameRateCore;
		Input* GetInput() { return this->input; }
		World *world;
		TweenManager *tweenManager;
		TimeBasedEventManager *timeBasedEventManager;
		CameraEventManager *cameraEventManager;
		MemoryManager *memoryManager;
		Camera *camera;
		HWND hWnd;
		Add* add;
		Preload *preload;
	protected:
		//
		// Private Method
		//
		void ErrorCheck(int errorCode);
		void gameUpdate();
		void RunGroupUpdate(std::list<Group*> *groupList);
		//
		// Private class instance
		//
		D3DManager *d3dManager;
		DrawManager *drawManager;
		Input *input;
		//
		// Private Field
		//
		bool isRunning;
		std::list<Group*> topGroupList;
		long frameCountCore; 
		long frameCountReal;
		Timer coreTimer;
		Timer realTimer;
		bool pauseMode;
		bool maximizeProcessor;
		Timer timeUpdate;


	};
}