#pragma once
#include "GGObject.h"
#include "d3d9.h"
#include "d3dx9.h"
#include "ConstantEnum.h"
#include <map>
#include <list>
namespace ggEngine {
	class Group;
	class Sprite;
	class Texture;
	class DrawManager:public GGObject{
	public:
		DrawManager(IDirect3DDevice9 *device);
		~DrawManager();
		void Destroy();
		void Render2D();
		Sprite* CreateSprite(std::string fileSource);
	private:
		void Update2D();
		IDirect3DDevice9 *device;
		std::list<Group*> groupList;
		std::map<std::string, Texture*> textureMap;
	};
}