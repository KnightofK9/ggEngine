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
		void Draw() override;

		void RemoveGameObjectFromDrawList(GameObject *go) override;
	private:
		QuadNode* rootNode = nullptr;
		Game *game;
	};
}