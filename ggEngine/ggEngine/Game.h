#pragma once
#include "D3DManager.h"
#include "Timer.h"
#include "ConstantEnum.h"
#include "Debug.h"
#include "GGObject.h"
#include "DrawManager.h"
namespace ggEngine {
	class Game :public GGObject {
	public:
		Game(HWND hWnd, int width, int height, GameMode mode = GameMode_Windowed, D3DCOLOR gameColor = D3DCOLOR_XRGB(0, 255, 255));
		~Game();
		void Destroy();
		void GameRun();
		D3DManager *GetD3DManager() { return this->d3dManager; }
		DrawManager *GetDrawManager() { return this->drawManager; }
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