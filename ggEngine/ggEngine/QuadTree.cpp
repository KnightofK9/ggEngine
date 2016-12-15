#include "QuadTree.h"
#include "ConstantEnum.h"
#include "SpriteAnimation.h"
#include "Cache.h"
#include "AnimationTile.h"
#include "SingleTile.h"
#include "QuadNode.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Debug.h"
#include "Physics.h"
#include "Body.h"
#include "Game.h"
#include "GameObject.h"
#include <exception>
#include <Math.h>
#include "Camera.h"
namespace ggEngine {
	QuadTree::QuadTree(Game * game): Group(game)
	{
		this->game = game;
	}
	QuadTree::~QuadTree()
	{
	}
	void QuadTree::Update()
	{
		this->drawList.clear();
		Rect r = this->game->camera->GetNormalRect();
		rootNode->Retrieve(&this->drawList, r);
		//g_debug.Log(this->drawList.size());
	}
	void QuadTree::UpdatePhysics()
	{
		/*for (auto it = this->drawList.begin(); it != this->drawList.end(); ++it) {
			(*it)->body->Update();
		}*/
	}

	
	void QuadTree::BuildTree(const char * quadTreeJson)
	{
		rootNode = new QuadNode(this->game, this, quadTreeJson);
	}
	void QuadTree::Draw()
	{
		for (auto it = this->drawList.begin(); it != this->drawList.end(); ++it) {
			(*it)->UpdateWorldPosition();
			(*it)->Draw();
		}
	}

	void QuadTree::RemoveGameObjectFromDrawList(GameObject * go)
	{
		Group::RemoveGameObjectFromDrawList(go);
	}


}