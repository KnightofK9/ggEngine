#include "CVGame.h"
#include "CVAdd.h"
#include "CVPreload.h"
#include "ItemManager.h"
#include "WeaponManager.h"
CVGame::CVGame(HWND hWnd, int width, int height, GameMode mode, PhysicsMode physicsMode, D3DCOLOR gameColor) :Game(hWnd, width, height, mode, physicsMode, gameColor)
{
	this->cvPreload = new CVPreload(this);
	this->cvAdd = new CVAdd(this);
	this->itemManager = new ItemManager(this);
	this->weaponManager = new WeaponManager(this);
}

CVGame::~CVGame()
{
}
