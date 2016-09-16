#include "Game.h"
#include <iostream>
Game::Game(HWND hWnd, int width, int height, D3DCOLOR backgroundColor)
{
	d3dManager = new D3DManager(hWnd, width, height, backgroundColor);
	driverInfoManager = new DriverInfoManager(d3dManager->getContext());
	this->hWnd = hWnd;
	Scene *blankScene = new Scene();
	scene = blankScene;
}

Game::~Game()
{
	delete d3dManager;
	d3dManager = NULL;
	delete driverInfoManager;
	driverInfoManager = NULL;
}

void Game::GameRun()
{
	d3dManager->update();

}

void Game::showDriverInfo()
{
	D3DADAPTER_IDENTIFIER9 ident = driverInfoManager->getIdentifier();
	std::wcout << ident.Description << "\n"<<ident.DeviceName<<"\n"<<ident.Driver;
}

Scene *Game::addScene(std::string sceneName)
{
	sceneList[sceneName] = Scene();
	return &sceneList[sceneName];
}

Group *Game::addGroup()
{
	Group* g = new Group();
	return g;
}

void Game::StartScene(std::string sceneName)
{
	scene = &sceneList[sceneName];
}


