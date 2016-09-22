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
		Sprite* Sprite(std::string textureKey);
		Group* Group();
	private:
		DrawManager *drawManager;
	};
}