#pragma once
#include "GGObject.h"
#include <string>
namespace ggEngine{
	class Sprite;
	class Group;
	class DrawManager;
	class Add:public GGObject  {
	public:
		Add(DrawManager *drawManager);
		Sprite* Sprite(float x, float y, std::string textureKey, int frameName, Group *group);
		Group* Group();
	private:
		DrawManager *drawManager;
	};
}