#pragma once
#include "D3DManager.h"
#include "Timer.h"
#include "ConstantEnum.h"
#include "Debug.h"
#include "GGObject.h"
#include "DrawManager.h"
#include "IGetGroup.h"
namespace ggEngine {
	class Add;
	class Preload;
	class Cache;
	class Game :public GGObject, public IGetGroup {
	public:
		Game(HWND hWnd, int width, int height, GameMode mode = GameMode_Windowed, D3DCOLOR gameColor = D3DCOLOR_XRGB(0, 255, 255));
		~Game();
		void Destroy();
		void GameRun();
		D3DManager *GetD3DManager() { return this->d3dManager; }
		DrawManager *GetDrawManager() { return this->drawManager; }
		std::list<Group*> *GetGroupList() { return &this->topGroupList; }
		Cache  *cache;
		Add *add;
		Preload *preload;
	private:
		//
		// Private Method
		//
		void ErrorCheck(int errorCode);
		void gameUpdate();
		//
		// Private class instance
		//
		D3DManager *d3dManager;
		DrawManager *drawManager;
		//
		// Private Field
		//
		HWND hWnd;
		std::list<Group*> topGroupList;
		long frameCountCore; 
		long frameRateCore;
		long frameCountReal;
		long frameRateReal;
		Timer coreTimer;
		Timer realTimer;
		bool pauseMode;
		bool maximizeProcessor;
		Timer timeUpdate;


	};
}