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
	QuadTree::QuadTree(Game * game): Group(game->GetDrawManager())
	{
		this->game = game;
	}
	QuadTree::~QuadTree()
	{
	}
	void QuadTree::Update()
	{
	}
	std::list<Body*>* QuadTree::GetActiveObject()
	{
		return nullptr;
	}
	void QuadTree::RemoveObjectFromList(GameObject * gameObject)
	{
		Rect r = gameObject->GetRect();
		int top, left, right, bottom;
		left = (floor(r.left) + 1) / this->leafWidth;
		top = (floor(r.top) + 1) / this->leafHeight;
		right = (floor(r.right) + 1) / this->leafWidth;
		bottom = (floor(r.bottom) + 1) / this->leafHeight;

		for (int idY = top; idY <= bottom;idY++) {
			for (int idX = left; idX <= right;idX++) {
				int id = XYIndexTo1dIndex(idX, idY);
				quadNodeList[id]->gameObjectList.remove(gameObject);
			}
		}
	}
	void QuadTree::AddDrawObjectToList(GameObject * drawObject)
	{
		Rect r = drawObject->GetRect();
		int top, left, right, bottom;
		left = (floor(r.left) + 1) / this->leafWidth;
		top = (floor(r.top) + 1) / this->leafHeight;
		right = (floor(r.right) + 1) / this->leafWidth;
		bottom = (floor(r.bottom) + 1) / this->leafHeight;

		for (int idY = top; idY <= bottom;idY++) {
			for (int idX = left; idX <= right;idX++) {
				int id = XYIndexTo1dIndex(idX, idY);
				//TO DO put game object to quad node here
			}
		}
	}
	std::list<GameObject*>* QuadTree::GetDrawList()
	{
		return nullptr;
	}
	int QuadTree::XYIndexTo1dIndex(int x, int y)
	{
		return startOfLeafNodeId + x + this->numberOfNodePerRow*y;
	}
}