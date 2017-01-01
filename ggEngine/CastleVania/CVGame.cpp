#include "CVGame.h"
#include "CVAdd.h"
#include "CVPreload.h"
#include "ItemManager.h"
#include "WeaponManager.h"
#include "Factory.h"
#include "StaticTileManager.h"
#include "AnimationManager.h"
#include "AudioManager.h"
#include "CVCamera.h"
#include "EnemyManager.h"
#include "CVDebugDefine.h"
CVGame::CVGame(HWND hWnd, int width, int height, GameMode mode, PhysicsMode physicsMode, D3DCOLOR gameColor) :Game(hWnd, width, height, mode, physicsMode, gameColor)
{
	
}

CVGame::~CVGame()
{
	if (this->audioManager) {
		delete this->audioManager;
		this->audioManager = NULL;
	}
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
	SAFE_BREAK_BEGIN
	if (type == "TileBrick") {
		width = json["width"].GetDouble();
		height = json["height"].GetDouble();
		go = this->staticTileManager->AddTileBrick(x, y, width, height, group);
		SAFE_BREAK
	}
	if (type == "BreakableTileBrick") {
		go = this->itemManager->AddBreakableTileBrick(x, y, group);
		SAFE_BREAK
	}
	if (type == "Random") {
		go = this->itemManager->AddHeart(x, y, group);
		SAFE_BREAK
	}
	if (type == "Door") {
		go = this->staticTileManager->AddDoor(x, y, group);
		SAFE_BREAK
	}

	if (type == "TileLadderDownLeft") {
		go = this->staticTileManager->AddTileLadder(x, y, ObjectType_LadderDownLeft , group);
		SAFE_BREAK
	}
	if (type == "TileLadderDownRight") {
		go = this->staticTileManager->AddTileLadder(x, y, ObjectType_LadderDownRight, group);
		SAFE_BREAK
	}
	if (type == "TileLadderUpLeft") {
		go = this->staticTileManager->AddTileLadder(x, y, ObjectType_LadderUpLeft, group);
		SAFE_BREAK
	}
	if (type == "TileLadderUpRight") {
		go = this->staticTileManager->AddTileLadder(x, y, ObjectType_LadderUpRight, group);
		SAFE_BREAK
	}
	if (type == "Simon") {
		go = this->cvAdd->CharSimon(x, y, CharacterConstant::SIMON_MAX_HEALTH , nullptr, nullptr, group);
		SAFE_BREAK
	}
	if (type == "BigHeart") {
		go = this->itemManager->AddHeartLarger(x, y, group);
		SAFE_BREAK
	}
	if (type == "Heart") {
		go = this->itemManager->AddHeart(x, y, group);
		SAFE_BREAK
	}
	if (type == "HolyWater") {
		go = this->itemManager->AddHolyWater(x, y, group);
		SAFE_BREAK
	}
	if (type == "InvincibilityPotion") {
		go = this->itemManager->AddInvinPotion(x, y, group);
		SAFE_BREAK
	}
	if (type == "MoneyBag100") {
		go = this->itemManager->AddMoneyBag100(x, y, group);
		SAFE_BREAK
	}
	if (type == "MoneyBag400") {
		go = this->itemManager->AddMoneyBag400(x, y, group);
		SAFE_BREAK
	}
	if (type == "MoneyBag700") {
		go = this->itemManager->AddMoneyBag700(x, y, group);
		SAFE_BREAK
	}
	if (type == "PotRoast") {
		go = this->itemManager->AddPotRoast(x, y, group);
		SAFE_BREAK
	}
	if (type == "StopWatch") {
		go = this->itemManager->AddStopWatch(x, y, group);
		SAFE_BREAK
	}
	if (type == "TripleShot") {
		go = this->itemManager->AddTripleShot(x, y, group);
		SAFE_BREAK
	}
	if (type == "WhipUpgrade") {
		go = this->itemManager->AddWhipUpgrade(x, y, group);
		SAFE_BREAK
	}
	if (type == "Axe") {
		go = this->itemManager->AddAxe(x, y, group);
		SAFE_BREAK
	}
	if (type == "Boomerang") {
		go = this->itemManager->AddBoomerang(x, y, group);
		SAFE_BREAK
	}
	if (type == "Cross") {
		go = this->itemManager->AddCross(x, y, group);
		SAFE_BREAK
	}
	if (type == "Dagger") {
		go = this->itemManager->AddDagger(x, y, group);
		SAFE_BREAK
	}
	if (type == "DoubleShot") {
		go = this->itemManager->AddDoubleShot(x, y, group);
		SAFE_BREAK
	}

	///Contans.js is missing some items in below:
	if (type == "FireCandle") {
		std::string dropType = Json::GetCharArrayFromValue(json["extraInfo"]["dropType"]);
		auto candle = this->itemManager->AddFireCandle(x, y, group);
		candle->SetDropItem(dropType);
		go = candle;
		SAFE_BREAK
	}
	if (type == "Crown") {
		go = this->itemManager->AddCrown(x, y, group);
		SAFE_BREAK
	}
	if (type == "Stuff") {
		go = this->itemManager->AddStuff(x, y, group);
		SAFE_BREAK
	}
	if (type == "MoneyBag1000") {
		go = this->itemManager->AddMoneyBag1000(x, y, group);
		SAFE_BREAK
	}
	if (type == "Raven") {
		go = this->enemyManager->AddRaven(x, y, group);
		SAFE_BREAK
	}
	if (type == "Skeleton") {
		go = this->enemyManager->AddSkeleton(x, y, group);
		SAFE_BREAK
	}
	if (type == "Boss") {
		go = this->enemyManager->AddMedusa(x, y, group);
		SAFE_BREAK
	}
	if (type == "BonePillar") {
		go = this->enemyManager->AddBonePillar(x, y, group);
		SAFE_BREAK
	}
	if (type == "Ghost") {
		go = this->enemyManager->AddGhost(x, y, group);
		SAFE_BREAK
	}
	if (type == "AI7") {
		go = this->enemyManager->AddAI7(x, y, group);
		SAFE_BREAK
	}
	if (type == "AI6") {
		go = this->enemyManager->AddAI6(x, y, json["width"].GetDouble(), group);
		SAFE_BREAK
	}
	if (type == "BatEnemy") {
		go = this->enemyManager->AddBatEnemy(x, y, group);
		SAFE_BREAK
	}
	if (type == "MedusaHead") {
		go = this->enemyManager->AddMedusaHead(x, y, group);
		SAFE_BREAK
	}
	if (type == "AxeKnight") {
		go = this->enemyManager->AddAxeKnight(x, y, group);
		SAFE_BREAK
	}
	if (type == "Monkey") {
		go = this->enemyManager->AddMonkey(x, y, group);
		SAFE_BREAK
	}
	if (type == "Boss3") {
		go = this->enemyManager->AddBoss3(x, y, group, json["extraInfo"]["info"].GetInt());
		SAFE_BREAK
	}
	SAFE_BREAK_END
	go->name = type;
	return go;
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
		this->audioManager = new AudioManager(this);


	}
	catch (int errorCode) {
		ErrorCheck(errorCode);
	}
}
