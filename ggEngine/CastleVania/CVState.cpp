#include "CVState.h"
CVState::CVState(Game * game):State(game)
{
}

CVState::CVState(Game * game, std::string statePath):State(game)
{
	Json state(statePath, true);
	this->json = state.GetCharArray();
}

CVState::~CVState()
{
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
			this->preload->TileSet(tileSetPath, tileSetJsonPath);
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
			this->add->TileMap(tileMapJson, false);
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
	this->add = new CVAdd(game->world, game->cache, game->tweenManager, game->GetDrawManager(), game->camera, game->physics, game->timeBasedEventManager);
	this->preload = new CVPreload(game->cache);
}


