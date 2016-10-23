#pragma once
#include "Group.h"
#include "IJsonable.h"
namespace ggEngine {
	class QuadTree;
	class SpriteInfo;
	class DrawManager;
	class QuadNode;
	class TileMap : public Group,public IJsonable {
	public:
		TileMap(DrawManager* drawManager);
		~TileMap();
		void Draw(const RECT drawRect);
		void CheckCollision(const GameObject *gameObject);
		// Inherited via IJsonable
		virtual void ParseJson(const char * jsonChar) override;
		virtual const char * CreateJson() override;
	private:
		void RecursiveDraw(const RECT &drawRect, QuadNode *quadNode, bool isDrawChildNode = false);
		QuadTree *quadTree;
		DrawManager *drawManager;
		LPD3DXSPRITE spriteHandle;

	};
}