#include "TestStateCastleVania.h"

TestStateCastleVania::TestStateCastleVania(CVGame *game) :CVState(game)
{
}
TestStateCastleVania::~TestStateCastleVania()
{
}
void TestStateCastleVania::Init() {

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
	this->simon = this->cvAdd->CharSimon(400, 400, group);


	this->cvAdd->UIInfoPanel(group);
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

