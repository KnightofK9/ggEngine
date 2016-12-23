#include "TestStateCastleVania.h"
#include "StaticTIleManager.h"
#include "EnemyManager.h"
TestStateCastleVania::TestStateCastleVania(CVGame *game) :CVState(game)
{
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

	GameOverScreen *goScreen = this->cvAdd->UIGameOverScreen(group);
	InfoPanel *infoPanel = this->cvAdd->UIInfoPanel(goScreen, group);	


	this->simon = this->cvAdd->CharSimon(0, 0, 12, nullptr, nullptr, nullptr);
	this->simon->AddWhip();
	this->cvgame->simon = this->simon;

	{
		//Json state("State/TestState.json", true);
		Json state("State/level2-tilemap.json", true);
		//Json state("State/level3-tilemap.json", true);
		cvMap1 = this->cvAdd->LoadMap(state.GetCharArray().c_str(),  this->cvgame->world);
		//Json state2("State/level3-tilemap.json", true);
		//cvMap1 = this->cvAdd->LoadMap(state.GetCharArray().c_str(), this->cvgame->world);

	
	}
	//cvMap = cvMap1;
	cvMap1->LoadSimon(infoPanel, goScreen, this->simon);
	//infoPanel->CountDown(infoPanel->GetTime(), [this] {
	//	simon->Death();
	//})->Start();


}
void TestStateCastleVania::Update()
{

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

