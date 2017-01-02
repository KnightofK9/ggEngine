#include "TestStateCastleVania.h"
#include "StaticTIleManager.h"
#include "AudioManager.h"
#include "EnemyManager.h"
#include "AnimationManager.h"
#include "CVDebugDefine.h"
#include "CVMapManager.h"
TestStateCastleVania::TestStateCastleVania(CVGame *game) :CVState(game)
{
	this->cvMapManager = this->cvgame->cvMapManager;
}
TestStateCastleVania::~TestStateCastleVania()
{

}
void TestStateCastleVania::Init() {

	this->itemManager = this->cvgame->itemManager;
}
void TestStateCastleVania::Preload() {
	//Json jsonFile("State/TestState.json", true);
	//Json jsonFile("State/TestState.json", true);

	//for (auto& it : jsonFile["preloadList"].GetArray())
	//{
	//	std::string type = it["type"].GetString();
	//	if (type == "PreTileSet") {
	//		std::string tileSetPath = it["tileSetPath"].GetString();
	//		std::string tileSetJsonPath = it["tileSetJsonPath"].GetString();
	//		this->preload->TileSet(tileSetPath, tileSetJsonPath);
	//		continue;
	//	}
	//}
	this->preload->TileSet(TextureConstant::TILE_SET_LEVEL_2_TEXTURE_PATH, TextureConstant::TILE_SET_LEVEL_2_JSON_PATH);
	this->preload->TileSet(TextureConstant::TILE_SET_LEVEL_3_TEXTURE_PATH, TextureConstant::TILE_SET_LEVEL_3_JSON_PATH);
	this->cvPreload->FontGame();
	this->cvPreload->UIInfoPanel();
	this->cvPreload->CharSimon();
	this->itemManager->PreloadAllItem();
	this->cvgame->staticTileManager->PreloadAll();
	this->cvgame->enemyManager->PreloadAll();
	this->cvgame->animationManager->PreloadAll();
	this->cvgame->audioManager->PreloadAll();
	this->cvMapManager->PreloadAll();
}
void TestStateCastleVania::Create()
{
	//this->cvgame->camera->SetWidth(256);
	//this->cvgame->camera->SetHeight(176);
	this->cvgame->camera->SetScale(3, 3);
	this->cvgame->camera->SetPoint(0, 65);

	//std::string tileMapJson = "";
	
	/*tileMap = this->add->TileMap(tileMapJson.c_str(),this->game->world);
	tileMap->name = "StupidTileMap";*/
	Group* group = this->add->Group();
	group->name = "StupidGroup";

	goScreen = this->cvAdd->UIGameOverScreen(group);
	infoPanel = this->cvAdd->UIInfoPanel(goScreen, group);	


	this->simon = this->cvAdd->CharSimon(0, 0, 12, nullptr, nullptr, nullptr);
	this->simon->AddWhip();
	this->cvgame->simon = this->simon;
	this->cvgame->audioManager->level4Music->PlayLoop();

	
	/*{
		Json state0("State/TestState.json", true);
		Json state("State/level2-tilemap.json", true);
		Json state2("State/level3-tilemap.json", true);
		cvMap = this->cvAdd->LoadMap("State", state0.GetCharArray().c_str(), nullptr);
		cvMap1 = this->cvAdd->LoadMap("level-2",state.GetCharArray().c_str(),  nullptr);
		cvMap2 = this->cvAdd->LoadMap("level-3", state2.GetCharArray().c_str(), nullptr);
	}*/
	this->cvMapManager->LoadUI(goScreen, infoPanel);
	this->cvMapManager->StartMap("level-2");
	//SwitchToMap(cvMap);
	//SwitchToMap(cvMap2);


	//cvMap = cvMap1;

	infoPanel->CountDown(300, [this] {
		simon->isDied = true;
	})->Start();


}
void TestStateCastleVania::Update()
{
#ifdef DEBUG_ENABLE_SET_STAGE_BLOCK_KEY_CONTROL
	SAFE_BREAK_BEGIN
	auto input = this->cvgame->GetInput();
	if (input->KeyDown(DIK_F5)) {
		this->cvMapManager->StartMap("level-2");
		SAFE_BREAK
	}
	if (input->KeyDown(DIK_F6)) {
		this->cvMapManager->StartMap("level-3");
		SAFE_BREAK
	}

	if (input->KeyDown(DIK_F7)) {
		this->cvMapManager->StartMap("test-stage");
		SAFE_BREAK
	}
	SAFE_BREAK_END
#endif // DEBUG_ENABLE_SET_STAGE_BLOCK_KEY_CONTROL
}
void TestStateCastleVania::PreRender()
{
}
void TestStateCastleVania::Render()
{
	/*std::list<Body*> bodyList = this->cvgame->world->GetBodyList();
	for (auto it = bodyList.begin(); it != bodyList.end(); ++it) {
		(*it)->Render();
	}*/
}
void TestStateCastleVania::Pause()
{
}
void TestStateCastleVania::Resume()
{
}
void TestStateCastleVania::ShutDown()
{

}

void TestStateCastleVania::SwitchToMap(CVMap * cvMap)
{
	if (this->cvgame->simon->currentMap != nullptr) this->cvgame->simon->currentMap->DeActive();
	this->cvgame->animationManager->simonGroup = cvMap->simonGroup;
	cvMap->LoadSimon(infoPanel, goScreen, this->simon);
	cvMap->Active();
}

