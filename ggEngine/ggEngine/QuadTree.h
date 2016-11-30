#pragma once
#include <vector>
#include <string>
#include <d3d9.h>
#include "Vector.h"
#include "Json.h"
#include "Group.h"
namespace ggEngine {
	class Game;
	class QuadNode;
	class GameObject;
	class QuadTree : public Group {
	public:
		QuadTree(Game *game);
		virtual ~QuadTree();

		void Update() override;
		std::list<Body*> *GetActiveObject();
		void RemoveObjectFromList(GameObject *gameObject);
		void AddDrawObjectToList(GameObject* drawObject) override;
		std::list<GameObject*> *GetDrawList() override;
	private:
		int XYIndexTo1dIndex(int x, int y);
		int leafWidth;
		int leafHeight;
		int numberOfNodePerRow;
		int numberOfNodePerColumn;
		int startOfLeafNodeId;
		std::vector<QuadNode*> quadNodeList;
		Game *game;
	};
}