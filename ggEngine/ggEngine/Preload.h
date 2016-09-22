#pragma once
#include "GGObject.h"
#include <string>
namespace ggEngine{
	class Sprite;
	class Group;
	class DrawManager;
	class Preload :public GGObject  {
	public:
		Preload(DrawManager *drawManager);
		void Sprite(std::string textureKey, std::string texturePath);
	private:
		DrawManager *drawManager;
	};
}