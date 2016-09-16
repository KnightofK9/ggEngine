#pragma once
#include "Window.h"
#include "D3DManager.h"
#include "DriverInfoManager.h"
#include "Scene.h"
#include <d3d9.h>
#include <string>
#include <map>
class Game {
public:
	Game(HWND hWnd, int width, int height,D3DCOLOR backgroundColor);
	~Game();
	void GameRun();
	void showDriverInfo();
	Scene *addScene(std::string sceneName);
	Group *addGroup();
	void StartScene(std::string sceneName);
private:
	HWND hWnd;
	std::map<std::string,Scene> sceneList;
	D3DManager *d3dManager;
	DriverInfoManager *driverInfoManager;
	Scene *scene;
};