#include "StateManager.h"
#include "Scene.h"
#include "Cache.h"
#include "Game.h"
namespace ggEngine {
	StateManager::StateManager(Game * game)
	{
		this->game = game;
		this->cache = game->cache;
		this->currentScene = NULL;
	}

	StateManager::~StateManager()
	{
	}

	bool StateManager::Add(std::string key, Scene * scene, bool autoStart)
	{
		if (scene == NULL) {
			Debug::Error("Parsing NULL scene error");
			return false;
		}
		this->sceneMap[key] = scene;
		if (autoStart) {
			Start(key,false,false);
		}
		return true;
	}

	bool StateManager::Start(std::string key, bool clearWolrd, bool clearCache)
	{
		if (!CheckScene(key)) {
			Debug::Error("No scene found with key " + key);
			return false;
		}
		if (clearWolrd) {
			if (this->currentScene != NULL) {
				this->currentScene->ShutDown();
			}
		}
		if (clearCache) {
			this->cache->ClearAll();
		}
		this->currentScene = this->sceneMap[key];
		this->currentScene->Start();
		return true;
	}

	bool StateManager::Restart(bool clearWolrd, bool clearCache)
	{
		if (clearWolrd) {
			if (this->currentScene != NULL) {
				currentScene->ShutDown();
			}
		}
		if (clearCache) {
			this->cache->ClearAll();
		}
		if (this->currentScene == NULL) {
			Debug::Error("No scene has been init.");
			return false;
		}
		this->currentScene->ShutDown();
		this->currentScene->Start();
		return true;
	}

	bool StateManager::Remove(std::string key)
	{
		if (!CheckScene(key)) {
			Debug::Warning("No scene found with key when trying to remove " + key);
			return true;
		}
		this->sceneMap.erase(key);
		return true;
	}

	void StateManager::ClearCurrentState()
	{
		//TO DO reset camera, reset tween, reset time, etc...
	}

	bool StateManager::CheckScene(std::string key)
	{
		std::map<std::string, Scene*>::iterator it = this->sceneMap.find(key);
		Scene* tex;
		if (it != this->sceneMap.end())
		{
			return true;
		}
		return false;
	}

}