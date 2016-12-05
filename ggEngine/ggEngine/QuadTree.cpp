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
	}

	void QuadTree::RemoveObjectFromList(GameObject * gameObject)
	{
	
	}
	void QuadTree::AddDrawObjectToList(GameObject * drawObject)
	{
		
	}
	std::list<GameObject*> QuadTree::GetDrawList()
	{
		return Group::GetDrawList();
	}
	void QuadTree::BuildTree(char * stateJson)
	{

	}
	void QuadTree::UpdatePhysics()
	{
	}
	int QuadTree::XYIndexTo1dIndex(int x, int y)
	{
		return startOfLeafNodeId + x + this->numberOfNodePerRow*y;
	}
}