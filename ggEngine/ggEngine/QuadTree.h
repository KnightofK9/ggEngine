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
		void UpdatePhysics() override;
		void BuildTree(const char * quadTreeJson);

	private:
		int leafWidth;
		int leafHeight;
		int numberOfNodePerRow;
		int numberOfNodePerColumn;
		int startOfLeafNodeId;
		std::vector<QuadNode*> quadNodeList;
		Game *game;
	};
}