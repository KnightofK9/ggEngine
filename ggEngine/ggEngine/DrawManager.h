#pragma once
#include "GGObject.h"
#include "d3d9.h"
#include "d3dx9.h"
#include "ConstantEnum.h"
#include <map>
#include <list>
namespace ggEngine {
	class State;
	class Group;
	class Sprite;
	class Texture;
	class Game;
	class StateManager;
	class DrawObject;
	class DrawManager:public GGObject{
	public:
		DrawManager(Game *game);
		~DrawManager();
		void Destroy();
		void Render2D();
		void DrawObjectFromGroup(std::list<Group*> groupList);
		void DrawList(std::list<DrawObject*> *drawObjectList);
		Sprite* CreateSprite(std::string fileSource);
		IDirect3DDevice9 *GetDevice(){ return this->device; }
	private:
		void Update2D();
		IDirect3DDevice9 *device;
		StateManager *stateManager;
		std::list<Group*> topGroupList;
	};
}