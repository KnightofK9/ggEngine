#include "CVState.h"

CVState::CVState(CVGame * game):State(game,false)
{
	this->cvgame = game;
	Load();
}

CVState::CVState(CVGame * game, std::string statePath):State(game)
{
	this->cvgame = game;
	Json state(statePath, true);
	this->json = state.GetCharArray();
	Load();
}

CVState::~CVState()
{
	if (cvAdd != nullptr) {
		delete cvAdd;
		cvAdd = nullptr;
	}
	if (cvPreload != nullptr) {
		delete cvPreload;
		cvPreload = nullptr;
	}
}

void CVState::Init()
{
}

void CVState::Preload()
{
	Json jsonFile(this->json);
	for (auto& it : jsonFile["preloadList"].GetArray())
	{
		std::string type = it["type"].GetString();
		if (type == "PreTileSet") {
			std::string tileSetPath = it["tileSetPath"].GetString();
			std::string tileSetJsonPath = it["tileSetJsonPath"].GetString();
			this->cvPreload->TileSet(tileSetPath, tileSetJsonPath);
		}
	}
}

void CVState::Create()
{
	Json jsonFile(this->json);
	for (auto& it : jsonFile["groupList"].GetArray())
	{
		std::string type = it["type"].GetString();
		if (type == "TileMap") {
			std::string tileMapJson = Json::GetCharArrayFromValue(it);
			this->cvAdd->TileMap(tileMapJson, false);
		}
	}
}

void CVState::Update()
{
}

void CVState::PreRender()
{
}

void CVState::Render()
{
}

void CVState::Pause()
{
}

void CVState::Resume()
{
}

void CVState::ShutDown()
{
}

void CVState::Load()
{
	this->cvAdd = cvgame->cvAdd;
	this->cvPreload = cvgame->cvPreload;
}


