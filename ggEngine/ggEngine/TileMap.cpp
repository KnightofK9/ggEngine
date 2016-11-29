#include "TileMap.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "QuadNode.h"
#include "SpriteInfo.h"
#include "AnimationTile.h"
#include "SingleTile.h"
#include "Camera.h"
#include "Physics.h"
#include "TileSet.h"
#include "Cache.h"
#include "Debug.h"
namespace ggEngine {
	TileMap::TileMap(Camera *camera, DrawManager* drawManager, Cache *cache, Physics *physics) : Group(drawManager)
	{
		this->camera = camera;
		this->physics = physics;
		this->cache = cache;
		this->spriteHandle = drawManager->GetSpriteHandle();
		SetScale(1, 1);
	}
	TileMap::~TileMap()
	{
		this->physics->RemoveTileMap(this);
	}
	void TileMap::Destroy()
	{
		this->alive = false;
	}
	void TileMap::Update()
	{
		Group::Update();
		/*Update check collision and draw list*/
		this->collisionCheckList.clear();
		/*const RECT drawRect = camera->GetRect();
		RecursiveDraw(drawRect, this->quadTree->GetRootNode());*/
	}

	std::list<GameObject*>* TileMap::GetDrawList(){

		this->drawList.clear();
		//g_debug.Log("Current draw size " + std::to_string(this->drawList.size()));
		for (auto it = this->tileList.begin(); it != this->tileList.end(); ++it) {
			this->drawList.push_back(*it);
		}
		return &this->drawList;
	}
	std::list<GameObject*> TileMap::GetCollisionCheckList()
	{
		return this->collisionCheckList;
	}
	void TileMap::UpdateWorldPosition()
	{
		GameObject::UpdateWorldPosition();
		for (auto it = this->tileList.begin(); it != this->tileList.end(); ++it) {
			(*it)->UpdateWorldPosition();
		}
	/*	this->quadTree->GetRootNode()->UpdateWorldPositionFromTileMap();
		std::vector<QuadNode*> *quadNodeList = this->quadTree->GetQuadNodeListAsRef();
		for (auto it = quadNodeList->begin(); it != quadNodeList->end(); ++it) {
			((*it))->UpdateWorldPositionFromTileMap();
		}*/
	}
	void TileMap::BuildTree(std::string jsonChar, bool isLocation)
	{
		Json json(jsonChar, isLocation);
		float x = json["x"].GetFloat();
		float y = json["y"].GetFloat();
		this->width = json["width"].GetDouble();
		this->height = json["height"].GetDouble();
		this->tileWidth = json["tileWidth"].GetDouble();
		this->tileHeight = json["tileHeight"].GetDouble();
		this->isUsedQuadTree = json["isUsedQuadTree"].GetBool();

		const rapidjson::Value&  jsonTileSetList = json["tileSetList"];
		for (rapidjson::SizeType i = 0; i < jsonTileSetList.Size(); i++)
		{
			std::string tileSetKey = jsonTileSetList[i].GetString();
			this->tileSetKeyList.push_back(tileSetKey);
		}
		

		const rapidjson::Value&  jsonTileList = json["tileList"];
		for (rapidjson::SizeType i = 0; i < jsonTileList.Size(); i++)
		{
			const rapidjson::Value& jsonTile = jsonTileList[i];
			std::string type = jsonTile["type"].GetString();
			float tileX = jsonTile["x"].GetFloat();
			float tileY = jsonTile["y"].GetFloat();
			double tileWidth = jsonTile["width"].GetDouble();
			double tileHeight = jsonTile["height"].GetDouble();
			std::string tileSetKey = jsonTile["tileSetKey"].GetString();
			int tileId = jsonTile["tileId"].GetInt();



			TileSet* tileSet = this->cache->GetTileMap(tileSetKey);
			SpriteInfo *tileInfo;
			if (tileSet == nullptr) {
				tileInfo = this->cache->GetDefaultSpriteInfo();
			}
			else tileInfo = tileSet->GetTileSetAt(tileId);
			SingleTile *tile = new SingleTile(this->drawManager, this, tileInfo);
			tile->SetPosition(tileX, tileY);
			tile->SetWidth(tileWidth);
			tile->SetHeight(tileHeight);
			if (type == "StaticTile") {

			}
			tileList.push_back(tile);

		}

		/*this->quadTree = new QuadTree(this, this->drawManager, this->cache, this->physics);
		quadTree->BuildTree(json.GetCharArray());*/
	}
	void TileMap::RecursiveDraw(const RECT & drawRect, QuadNode * quadNode, bool isDrawAllChildNode)
	{
		
		//std::vector<DrawObject *> objectList = quadNode->GetObjectFromNode();
		//if (objectList.size()>0) {
		//	for (auto it = objectList.begin(); it != objectList.end(); ++it) {
		//		//(*it)->Draw();
		//		this->drawList.push_back((*it));
		//	}
		//	return;
		//}
		
		

	}
}