#include "StateManager.h"
#include "State.h"
#include "Cache.h"
#include "Game.h"
#include "Group.h"
#include "EventManager.h"
#include "Physics.h"
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
		ClearGroup(this->currentState->GetGroupList());
	}

	bool StateManager::Add(std::string key, State * State, bool autoStart)
	{
		if (State == NULL) {
			Debug::Error("Parsing NULL State error");
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
			Debug::Error("No State has been init.");
			return false;
		}
		ClearGroup(this->currentState->GetGroupList());
		this->currentState->ShutDown();
		this->currentState->Start();
		return true;
	}

	bool StateManager::Remove(std::string key)
	{
		if (!CheckState(key)) {
			Debug::Warning("No State found with key when trying to remove " + key);
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
			Debug::Error("No State found with key " + stateKey);
			return;
		}
		if (this->clearWorld) {
			if (this->currentState != NULL) {
				ClearGroup(this->currentState->GetGroupList());
				game->physics->Reset();
				game->eventManager->Reset();
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

	void StateManager::ClearSprite(Group* group)
	{
		std::list<DrawObject*> *drawList = group->GetDrawList();
		for (std::list<DrawObject*>::const_iterator it = drawList->begin(); it != drawList->end(); it++)
		{
			delete *it;
		}
		drawList->clear();
	}
	void StateManager::ClearGroup(std::list<Group*> *groupList)
	{
		for (std::list<Group*>::iterator it = groupList->begin(); it != groupList->end(); ++it) {
			std::list<Group*> *groupList = (*it)->GetGroupList();
			ClearGroup(groupList);
			(*it)->Reset();
			delete (*it);
		}
		groupList->clear();
	}

}