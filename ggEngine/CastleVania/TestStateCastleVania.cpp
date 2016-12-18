#include "TestStateCastleVania.h"
#include "StaticTIleManager.h"
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

		cvMap = this->cvAdd->LoadMap(state.GetCharArray().c_str(),  this->cvgame->world);


		/*for (auto& it : state["groupList"].GetArray())
		{
			std::string type = it["type"].GetString();
			if (type == "TileMap") {
				tileMapJson = Json::GetCharArrayFromValue(it);
				break;
			}
		}*/
	}

	cvMap->LoadSimon(infoPanel, goScreen, this->simon);
	//infoPanel->CountDown(infoPanel->GetTime(), [this] {
	//	simon->Death();
	//})->Start();

	
	/*this->itemManager->AddHeart(200, 100, group);
	this->itemManager->AddCandle(250, 800, group);
	this->itemManager->AddWhipUpgrade(300, 100, group);
	this->itemManager->AddHeart(450, 100, group);
	this->itemManager->AddMoneyBag1000(150, 100, group);
	this->itemManager->AddStuff(180, 100, group);
	this->itemManager->AddDagger(230, 100, group);
	this->itemManager->AddInvinPotion(400, 100, group);
	this->itemManager->AddPotRoast(280, 100, group);
	this->itemManager->AddDoubleShot(260, 100, group);
	this->itemManager->AddTripleShot(170, 100, group);*/

	

	//cath event when player lose health or gain health
	//this->simon->healthSignal.connect(boost::bind(&InfoPanel::SetPlayerHealth, infoPanel, _1));
	//Group *b = this->cvAdd->Group();
	//HealthBar *healthBar = this->cvAdd->UIPlayerHealthBar(100, 100, group);
	/*ggEngine::Sprite* emptyHealthBar = this->cvAdd->Sprite(0, 0, TextureConstant::EMPTY_HEALTH_TEXTURE, b);
	ggEngine::Sprite* healthBar = this->cvAdd->Sprite(0, 0, TextureConstant::FULL_HEALTH_PLAYER_TEXTURE, b);*/
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

