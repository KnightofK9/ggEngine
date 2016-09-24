#pragma once
#include "GGObject.h"
#include <map>
#include <string>
#include <list>
#include "IGetGroup.h"
namespace ggEngine {
	class Game;
	class State;
	class Cache;
	class StateManager: public GGObject {
	public:
		StateManager(Game *game);
		~StateManager();
		void Destroy();
		bool Add(std::string key, State* State, bool autoStart = false);
		bool Start(std::string key, bool clearWolrd, bool clearCache);
		bool Restart(bool clearWolrd, bool clearCache);
		bool Remove(std::string key);
		void ClearCurrentState();
		bool CheckState(std::string key);
		State* GetCurrentState(){ return this->currentState; }
	private:
		void ClearGroup(std::list<Group*> groupList);
		State *currentState;
		Game *game;
		Cache *cache;
		std::map<std::string, State*> stateMap;
	};
}