#include "CVGame.h"
#include "CVAdd.h"
#include "CVPreload.h"
#include "ItemManager.h"
#include "WeaponManager.h"
#include "Factory.h"
#include "StaticTileManager.h"
#include "AnimationManager.h"
#include "CVCamera.h"
#include "EnemyManager.h"
CVGame::CVGame(HWND hWnd, int width, int height, GameMode mode, PhysicsMode physicsMode, D3DCOLOR gameColor) :Game(hWnd, width, height, mode, physicsMode, gameColor)
{
	
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
	if (type == "Skeleton") {
		go = this->enemyManager->AddSkeleton(x, y, group);
		return go;
	}
	if (type == "Boss") {
		go = this->enemyManager->AddMedusa(x, y, group);
		return go;
	}
	if (type == "BonePillar") {
		go = this->enemyManager->AddBonePillar(x, y, group);
		return go;
	}
	if (type == "Ghost") {
		go = this->enemyManager->AddGhost(x, y, group);
		return go;
	}
	if (type == "AI7") {
		go = this->enemyManager->AddAI7(x, y, group);
		return go;
	}
	if (type == "AI6") {
		go = this->enemyManager->AddAI6(x, y, json["width"].GetDouble(), group);
		return go;
	}
	if (type == "BatEnemy") {
		go = this->enemyManager->AddBatEnemy(x, y, group);
		return go;
	}
	if (type == "MedusaHead") {
		go = this->enemyManager->AddMedusaHead(x, y, group);
		return go;
	}
	if (type == "AxeKnight") {
		go = this->enemyManager->AddAxeKnight(x, y, group);
		return go;
	}
	if (type == "BreakableTileBrick") {
		go = this->itemManager->AddBreakableTileBrick(x, y, group);
		return go;
	}
	if (type == "Random") {
		go = this->itemManager->AddHeart(x, y, group);
		return go;
	}
	if (type == "Door") {
		go = this->staticTileManager->AddDoor(x, y, group);
		return go;
	}

	if (type == "TileBrick") {
		width = json["width"].GetDouble();
		height = json["height"].GetDouble();
		go = this->staticTileManager->AddTileBrick(x, y,width,height, group);
		return go;
	}
	if (type == "TileLadderDownLeft") {
		go = this->staticTileManager->AddTileLadder(x, y, ObjectType_LadderDownLeft , group);
		return go;
	}
	if (type == "TileLadderDownRight") {
		go = this->staticTileManager->AddTileLadder(x, y, ObjectType_LadderDownRight, group);
		return go;
	}
	if (type == "TileLadderUpLeft") {
		go = this->staticTileManager->AddTileLadder(x, y, ObjectType_LadderUpLeft, group);
		return go;
	}
	if (type == "TileLadderUpRight") {
		go = this->staticTileManager->AddTileLadder(x, y, ObjectType_LadderUpRight, group);
		return go;
	}
	if (type == "Simon") {
		go = this->cvAdd->CharSimon(x, y, CharacterConstant::SIMON_MAX_HEALTH , nullptr, nullptr, group);
		return go;
	}
	if (type == "BigHeart") {
		go = this->itemManager->AddHeartLarger(x, y, group);
		return go;
	}
	if (type == "Heart") {
		go = this->itemManager->AddHeart(x, y, group);
		return go;
	}
	if (type == "HolyWater") {
		go = this->itemManager->AddHolyWater(x, y, group);
		return go;
	}
	if (type == "InvincibilityPotion") {
		go = this->itemManager->AddInvinPotion(x, y, group);
		return go;
	}
	if (type == "MoneyBag100") {
		go = this->itemManager->AddMoneyBag100(x, y, group);
		return go;
	}
	if (type == "MoneyBag400") {
		go = this->itemManager->AddMoneyBag400(x, y, group);
		return go;
	}
	if (type == "MoneyBag700") {
		go = this->itemManager->AddMoneyBag700(x, y, group);
		return go;
	}
	if (type == "PotRoast") {
		go = this->itemManager->AddPotRoast(x, y, group);
		return go;
	}
	if (type == "StopWatch") {
		go = this->itemManager->AddStopWatch(x, y, group);
		return go;
	}
	if (type == "TripleShot") {
		go = this->itemManager->AddTripleShot(x, y, group);
		return go;
	}
	if (type == "WhipUpgrade") {
		go = this->itemManager->AddWhipUpgrade(x, y, group);
		return go;
	}
	if (type == "Axe") {
		go = this->itemManager->AddAxe(x, y, group);
		return go;
	}
	if (type == "Boomerang") {
		go = this->itemManager->AddBoomerang(x, y, group);
		return go;
	}
	if (type == "Cross") {
		go = this->itemManager->AddCross(x, y, group);
		return go;
	}
	if (type == "Dagger") {
		go = this->itemManager->AddDagger(x, y, group);
		return go;
	}
	if (type == "DoubleShot") {
		go = this->itemManager->AddDoubleShot(x, y, group);
		return go;
	}


	///Contans.js is missing some items in below:
	if (type == "FireCandle") {
		std::string dropType = Json::GetCharArrayFromValue(json["extraInfo"]["dropType"]);
		auto candle = this->itemManager->AddFireCandle(x, y, group);
		candle->SetDropItem(dropType);
		go = candle;
		return go;
	}
	if (type == "Crown") {
		go = this->itemManager->AddCrown(x, y, group);
		return go;
	}
	if (type == "Stuff") {
		go = this->itemManager->AddStuff(x, y, group);
		return go;
	}
	if (type == "MoneyBag1000") {
		go = this->itemManager->AddMoneyBag1000(x, y, group);
		return go;
	}
}

void CVGame::LoadComponent()
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
		timeBasedEventManager = new TimeBasedEventManager(this);
		d3dManager = new D3DManager(this, hWnd, width, height, gameColor, isWindowed);
		stateManager = new StateManager(this);
		camera = new CVCamera(this, width, height, 0, 0, true);
		drawManager = new DrawManager(this, camera);
		cache = new Cache(this);
		physics = new Physics(this, physicsMode);
		eventManager = new EventManager(this);
		tweenManager = new ggEngine::TweenManager(this);
		cameraEventManager = new CameraEventManager(this);
		memoryManager = new MemoryManager(this);
		world = new World(this);
		input = new Input(&hWnd);
		add = new Add(this);
		preload = new Preload(cache);

		g_debug.Init(this);




		stateManager->SetCache(cache);
		d3dManager->SetDrawManager(drawManager);
		d3dManager->SetStateManager(stateManager);

		input->InitKeyboard();
		input->InitMouse();


		this->cvPreload = new CVPreload(this);
		this->cvAdd = new CVAdd(this);
		this->itemManager = new ItemManager(this);
		this->weaponManager = new WeaponManager(this);
		this->staticTileManager = new StaticTileManager(this);
		this->animationManager = new AnimationManager(this);
		this->enemyManager = new EnemyManager(this);


	}
	catch (int errorCode) {
		ErrorCheck(errorCode);
	}
}
