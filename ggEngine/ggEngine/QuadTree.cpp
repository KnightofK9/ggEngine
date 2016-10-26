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
		return this->rootNode;
	}
	void QuadTree::BuildTree(std::string jsonChar)
	{
		Json json(jsonChar);
		this->width = json["width"].GetInt();
		this->height = json["height"].GetInt();
		int totalNodeSize = json["totalNodeSize"].GetInt();
		this->quadNodeList.resize(totalNodeSize+1);

		const rapidjson::Value&  quadNodeJsonList = json["quadNodeList"];
		for (rapidjson::SizeType i = 0; i <= quadNodeJsonList.Size(); i++)
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

				quadNode = new QuadNode(this, width, height, id);
				std::vector<GameObject*> drawObjectList;
				const rapidjson::Value& drawList = json["tileList"];
				for (rapidjson::SizeType i = 0; i < drawList.Size(); i++)
				{
					const rapidjson::Value& tileInfo = drawList[i];
					GameObject* tile;
					TileType tileType = (TileType)tileInfo["type"].GetInt();
					switch (tileType) {
						case TileType_SingleTile:
							tile = GetSpriteFromTileInfo(tileInfo["value"]["tileMapKey"].GetString(), tileInfo["value"]["tileId"].GetInt(),width,height, quadNode);
							break;
						case TileType_AnimationType:
							tile = GetSpriteAnimationFromTileInfo(tileInfo["value"], width, height, quadNode);
							break;
						default:
							break;
					}
					drawObjectList.push_back(tile);			
				}
			}
			this->quadNodeList[id] = quadNode;
		}
		this->rootNode = new QuadNode(this, this->width, this->height, -1, 0,1,2,3);


	}
	RECT QuadTree::GetRect()
	{
		return{ (long)position.x,(long)position.y,(long)position.x + (long)width,(long)position.y + (long)height };
	}
	QuadNode * QuadTree::GetNodeAt(int index)
	{
		return quadNodeList[index];
	}
	SingleTile * QuadTree::GetSpriteFromTileInfo(std::string tileMapKey, int tileId, double width, double height,QuadNode *parentNode)
	{
		TileMapInfo* tileMapInfo = this->cache->GetTileMap(tileMapKey);
		SpriteInfo *tileInfo;
		if (tileMapInfo == nullptr) {
			tileInfo = this->cache->GetDefaultSpriteInfo();
		}
		tileInfo = tileMapInfo->GetTileMapInfoAt(tileId);
		auto tile = new SingleTile(this->drawManager, parentNode, tileInfo);
		tile->SetWidth(width);
		tile->SetHeight(height);
		return tile;
	}
	AnimationTile * QuadTree::GetSpriteAnimationFromTileInfo(rapidjson::Value const &tileList, double width, double height, QuadNode *parentNode)
	{
		AnimationTile *animationTile = new AnimationTile(this->drawManager, this->tileMap);
		for (rapidjson::SizeType i = 0; i < tileList.Size(); i++) {
			const rapidjson::Value& tileInfo = tileList[i];
			SingleTile *tile = GetSpriteFromTileInfo(tileInfo["tileMapKey"].GetString(), tileInfo["tileId"].GetInt(),width,height, parentNode);
			animationTile->AddTileAnimation(tile);
		}
		return animationTile;
	}
}