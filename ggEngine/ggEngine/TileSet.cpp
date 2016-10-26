#include "TileSet.h"
#include "SpriteInfo.h"
#include "Texture.h"
ggEngine::TileSet::TileSet(Texture * texture)
{
	this->texture = texture;
}

ggEngine::TileSet::~TileSet()
{
	for (auto it = this->tileInfoList.begin(); it != this->tileInfoList.end(); ++it) {
		delete (*it);
	}
	if (this->texture != nullptr) {
		this->texture->Destroy();
		this->texture = nullptr;
	}
}

void ggEngine::TileSet::Destroy()
{
}

void ggEngine::TileSet::ParseJson(std::string jsonChar)
{
	Json json(jsonChar);
	this->id = json["id"].GetString();
	this->width = json["width"].GetInt();
	this->height = json["height"].GetInt();
	this->tileWidth = json["tileWidth"].GetInt();
	this->tileHeight = json["tileHeight"].GetInt();
	this->numberOfCell = json["numberOfCell"].GetInt();
	this->numberOfCellPerColumn = json["numberOfCellPerColumn"].GetInt();
	this->numberOfCellPerRow = json["numberOfCellPerRow"].GetInt();
	const rapidjson::Value &tileList = json["tileList"];
	this->tileInfoList.resize(this->numberOfCell);
	for (rapidjson::SizeType i = 0; i < tileList.Size(); ++i) {
		int x, y, id;
		const rapidjson::Value &tileInfo = tileList[i];
		id = tileInfo["id"].GetInt();
		x = tileInfo["x"].GetInt();
		y = tileInfo["y"].GetInt();
		SpriteInfo *spriteInfo = new SpriteInfo(this->texture, x, y, tileWidth, tileHeight);
		this->tileInfoList[id] = spriteInfo;
	}
}

std::string ggEngine::TileSet::CreateJson()
{
	return nullptr;
}
