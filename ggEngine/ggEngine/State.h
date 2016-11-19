#pragma once
#include "GGObject.h"
#include "IGetGroup.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include <list>
namespace ggEngine{
	class Map;
	class Group;
	class Add;
	class Preload;
	class DrawManager;
	class World;
	class Game;
	class State : public GGObject{
	public:
		~State();
		void Start();
		virtual void Load();
		Add *add = nullptr;
		Preload *preload = nullptr;
		virtual void Destroy();
		virtual void Init() = 0; //Called after start a State
		virtual void Preload() = 0; //Called after init
		virtual void Create() = 0;//Called after preload complete
		virtual void Update() = 0;//Called before each game update loop
		virtual void PreRender() = 0;//Called before enter each render
		virtual void Render() = 0;//Called after render completed
		virtual void Pause() = 0;//Called when the game is set to paused
		virtual void Resume() = 0;//Called when the game is resumed
		virtual void ShutDown() = 0;//Called when start a new State
	protected:
		State(Game *game, bool isLoadAutomatic = false);
		Game *game;
	private:
		DrawManager *drawManager;
		Map *map;
		World *world;
	};
}