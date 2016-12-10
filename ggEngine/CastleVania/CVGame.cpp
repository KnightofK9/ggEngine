#include "CVGame.h"
#include "CVAdd.h"
#include "CVPreload.h"
#include "ItemManager.h"
#include "WeaponManager.h"
#include "Factory.h"
#include "StaticTileManager.h"
CVGame::CVGame(HWND hWnd, int width, int height, GameMode mode, PhysicsMode physicsMode, D3DCOLOR gameColor) :Game(hWnd, width, height, mode, physicsMode, gameColor)
{
	this->cvPreload = new CVPreload(this);
	this->cvAdd = new CVAdd(this);
	this->itemManager = new ItemManager(this);
	this->weaponManager = new WeaponManager(this);
	this->staticTileManager = new StaticTileManager(this);
}

CVGame::~CVGame()
{
}

GameObject * CVGame::GetObjectInstance(const char * objectJson,Group *group)
{
	GameObject * go = Game::GetObjectInstance(objectJson);
	if (go != nullptr) {
		return go;
	}
	Json json(objectJson);
	double x, y, width, height;
	std::string type;
	type = json["type"].GetString();
	x = json["x"].GetDouble();
	y = json["y"].GetDouble();
	width = json["width"].GetDouble();
	height = json["height"].GetDouble();

	if (type == "TileBrick") {
		go = this->staticTileManager->AddTileBrick(x, y, group);
		return go;
	}
	if (type == "Simon") {
		go =  this->cvAdd->CharSimon(x, y, 16, nullptr, group);
		return go;
	}


	return go;

}
