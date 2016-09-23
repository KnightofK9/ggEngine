#pragma once
#include "GGObject.h"
#include <map>
#include <string>
namespace ggEngine {
	class Game;
	class Scene;
	class Cache;
	class StateManager: public GGObject {
	public:
		StateManager(Game *game);
		~StateManager();
		bool Add(std::string key, Scene* scene, bool autoStart = false);
		bool Start(std::string key, bool clearWolrd, bool clearCache);
		bool Restart(bool clearWolrd, bool clearCache);
		bool Remove(std::string key);
		void ClearCurrentState();
		bool CheckScene(std::string key);
		Scene* GetCurrentScene(){ return this->currentScene; }
	private:
		Scene *currentScene;
		Game *game;
		Cache *cache;
		std::map<std::string, Scene*> sceneMap;
	};
}