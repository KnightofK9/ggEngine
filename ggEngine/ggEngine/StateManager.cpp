#include "StateManager.h"
#include "State.h"
#include "Cache.h"
#include "Game.h"
#include "Group.h"
#include "EventManager.h"
#include "Physics.h"
#include "World.h"
#include "TweenManager.h"
namespace ggEngine {
	StateManager::StateManager(Game * game)
	{
		this->game = game;
		this->cache = game->cache;
		this->currentState = NULL;
	}

	StateManager::~StateManager()
	{
		Destroy();
	}

	void StateManager::Destroy()
	{
		
	}

	bool StateManager::Add(std::string key, State * State, bool autoStart)
	{
		if (State == NULL) {
			g_debug.Error("Parsing NULL State error");
			return false;
		}
		this->stateMap[key] = State;
		if (autoStart) {
			Start(key,false,false);
			LateStart();
			game->SetRunning(true);
		}
		return true;
	}

	bool StateManager::Start(std::string key, bool clearWolrd, bool clearCache)
	{
		if (!isSwitchState) {
			isSwitchState = true;
			this->stateKey = key;
			this->clearWorld = clearWolrd;
			this->clearCache = clearCache;
		}
		return true;
	}

	bool StateManager::Restart(bool clearWolrd, bool clearCache)
	{
		if (clearWolrd) {
			if (this->currentState != NULL) {
				currentState->ShutDown();
			}
		}
		if (clearCache) {
			this->cache->ClearAll();
		}
		if (this->currentState == NULL) {
			g_debug.Error("No State has been init.");
			return false;
		}
		this->currentState->ShutDown();
		this->currentState->Start();
		return true;
	}

	bool StateManager::Remove(std::string key)
	{
		if (!CheckState(key)) {
			g_debug.Warning("No State found with key when trying to remove " + key);
			return true;
		}
		this->stateMap.erase(key);
		return true;
	}

	void StateManager::ClearCurrentState()
	{
		//TO DO reset camera, reset tween, reset time, etc...
	}

	bool StateManager::CheckState(std::string key)
	{
		std::map<std::string, State*>::iterator it = this->stateMap.find(key);
		if (it != this->stateMap.end())
		{
			return true;
		}
		return false;
	}

	void StateManager::LateStart()
	{
		if (!isSwitchState) return;
		isSwitchState = false;
		if (!CheckState(stateKey)) {
			g_debug.Error("No State found with key " + stateKey);
			return;
		}
		if (this->clearWorld) {
			if (this->currentState != NULL) {
				game->world->Reset();
				game->physics->Reset();
				game->eventManager->Reset();
				game->tweenManager->Reset();
				this->currentState->ShutDown();
			}
		}
		if (clearCache) {
			this->cache->ClearAll();
		}
		this->currentState = this->stateMap[stateKey];
		this->currentState->Start();
		game->SetRunning(true);
	}


}