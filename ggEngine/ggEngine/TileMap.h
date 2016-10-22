#pragma once
#include "Group.h"
namespace ggEngine {
	class QuadTree;
	class Texture;
	class DrawManager;
	class QuadNode;
	class TileMap : protected Group {
	public:
		TileMap(DrawManager* drawManager);
		~TileMap();
		void Draw(const RECT drawRect);
		void ParseTree(const char *json);
	private:
		void RecuresiveDraw(const RECT &drawRect ,QuadNode *quadNode);
		QuadTree *quadTree;
		Texture *texture;
		DrawManager *drawManager;
		LPD3DXSPRITE spriteHandle;
	};
}