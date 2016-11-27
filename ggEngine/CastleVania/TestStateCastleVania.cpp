#include "TestStateCastleVania.h"

TestStateCastleVania::TestStateCastleVania(CVGame *game) :CVState(game)
{
}
TestStateCastleVania::~TestStateCastleVania()
{
	if (itemManager != nullptr) {
		delete itemManager;
		itemManager = nullptr;
	}
}
void TestStateCastleVania::Init() {

	this->itemManager = new ItemManager(cvgame);
}
void TestStateCastleVania::Preload() {
	Json jsonFile("State/TestState.json", true);
	for (auto& it : jsonFile["preloadList"].GetArray())
	{
		std::string type = it["type"].GetString();
		if (type == "PreTileSet") {
			std::string tileSetPath = it["tileSetPath"].GetString();
			std::string tileSetJsonPath = it["tileSetJsonPath"].GetString();
			this->cvPreload->TileSet(tileSetPath, tileSetJsonPath);
		}
	}
	this->cvPreload->FontGame();
	this->cvPreload->UIInfoPanel();
	this->cvPreload->CharSimon();
	this->itemManager->PreloadAllItem();
}
void TestStateCastleVania::Create()
{
	std::string tileMapJson = "";
	{
		Json state("State/TestState.json", true);
		for (auto& it : state["groupList"].GetArray())
		{
			std::string type = it["type"].GetString();
			if (type == "TileMap") {
				tileMapJson = Json::GetCharArrayFromValue(it);
			}
		}
	}
	tileMap = this->cvAdd->TileMap(tileMapJson, false);

	Group* group = this->cvAdd->Group();
	InfoPanel *infoPanel = this->cvAdd->UIInfoPanel(group);
	this->simon = this->cvAdd->CharSimon(100, GAME_HEIGHT-50, 16, infoPanel, group);
	this->simon->SetHealth(1);
	this->cvgame->simon = this->simon;
	this->itemManager->AddHeart(200, 100, group);
	this->itemManager->AddHeart(250, 100, group);
	this->itemManager->AddHeart(300, 100, group);
	this->itemManager->AddHeart(450, 100, group);
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
	std::list<Body*> bodyList = this->cvgame->physics->GetBodyList();
	for (auto it = bodyList.begin(); it != bodyList.end(); ++it) {
		(*it)->Render();
	}
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

