#include "QuadTree.h"
#include "ConstantEnum.h"
#include "SpriteAnimation.h"
#include "Cache.h"
#include "AnimationTile.h"
#include "SingleTile.h"
#include "QuadNode.h"
#include "TileMapInfo.h"
namespace ggEngine {
	QuadTree::QuadTree(TileMap *tileMap, DrawManager *drawManager,Cache *cache)
	{
		this->cache = cache;
		this->drawManager = drawManager;
		this->tileMap = tileMap;
	}
	QuadTree::~QuadTree()
	{
		for (auto it = quadNodeList.begin(); it != quadNodeList.end(); ++it) {
			delete (*it);
		}
		quadNodeList.clear();
	}
	QuadNode* QuadTree::GetRootNode()
	{
			return this->quadNodeList[1];
	}
	void QuadTree::BuildTree(const char * jsonChar)
	{
		Json json(jsonChar);
		this->width = json["width"].GetInt();
		this->height = json["height"].GetInt();
		int totalNodeSize = json["totalNodeSize"].GetInt();
		this->quadNodeList.resize(totalNodeSize+1);

		const rapidjson::Value&  quadNodeJsonList = json["quadNodeList"];
		for (rapidjson::SizeType i = 1; i <= quadNodeJsonList.Size(); i++)
		{
			const rapidjson::Value& quadNodeJson = quadNodeJsonList[i];
			int id = quadNodeJson["id"].GetInt();
			int width = quadNodeJson["width"].GetInt();
			int height = quadNodeJson["height"].GetInt();
			QuadNode* quadNode;
			std::string tileList = quadNodeJson["tileList"].GetString();
			if (tileList == "") {
				int leftTop = quadNodeJson["leftTop"].GetInt();
				int rightTop = quadNodeJson["rightTop"].GetInt();
				int leftBottom = quadNodeJson["leftBottom"].GetInt();
				int rightBottom = quadNodeJson["rightBottom"].GetInt();
				quadNode = new QuadNode(this, width, height,id, leftTop, rightTop, leftBottom,rightBottom);
			}
			else {
				std::vector<DrawObject*> drawObjectList;
				const rapidjson::Value& drawList = json["tileList"];
				for (rapidjson::SizeType i = 0; i < drawList.Size(); i++)
				{
					const rapidjson::Value& tileInfo = drawList[i];
					DrawObject* tile;
					TileType tileType = (TileType)tileInfo["type"].GetInt();
					switch (tileType) {
						case TileType_SingleTile:
							tile = GetSpriteFromTileInfo(tileInfo["value"]["tileMapKey"].GetString(), tileInfo["value"]["tileId"].GetInt(),width,height);
							break;
						case TileType_AnimationType:
							tile = GetSpriteAnimationFromTileInfo(tileInfo["value"], width, height);
							break;
						default:
							break;
					}
					drawObjectList.push_back(tile);			
				}
				quadNode = new QuadNode(this, width, height, id, drawObjectList);
			}
			this->quadNodeList[id] = quadNode;
		}


	}
	RECT QuadTree::GetRect()
	{
		return{ (long)position.x,(long)position.y,(long)position.x + (long)width,(long)position.y + (long)height };
	}
	QuadNode * QuadTree::GetNodeAt(int index)
	{
		return quadNodeList[index];
	}
	SingleTile * QuadTree::GetSpriteFromTileInfo(std::string tileMapKey, int tileId, double width, double height)
	{
		TileMapInfo* tileMapInfo = this->cache->GetTileMap(tileMapKey);
		SpriteInfo *tileInfo;
		if (tileMapInfo == nullptr) {
			tileInfo = this->cache->GetDefaultSpriteInfo();
		}
		tileInfo = tileMapInfo->GetTileMapInfoAt(tileId);
		auto tile = new SingleTile(this->drawManager, this->tileMap, tileInfo);
		tile->SetWidth(width);
		tile->SetHeight(height);
		return tile;
	}
	AnimationTile * QuadTree::GetSpriteAnimationFromTileInfo(rapidjson::Value const &tileList, double width, double height)
	{
		AnimationTile *animationTile = new AnimationTile(this->drawManager, this->tileMap);
		for (rapidjson::SizeType i = 0; i < tileList.Size(); i++) {
			const rapidjson::Value& tileInfo = tileList[i];
			SingleTile *tile = GetSpriteFromTileInfo(tileInfo["tileMapKey"].GetString(), tileInfo["tileId"].GetInt(),width,height);
			animationTile->AddTileAnimation(tile);
		}
		return animationTile;
	}
}