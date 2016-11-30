#include "MemoryManager.h"
#include "GameObject.h"
ggEngine::MemoryManager::MemoryManager(Game * game)
{
	this->game = game;
}

ggEngine::MemoryManager::~MemoryManager()
{
}

void ggEngine::MemoryManager::Update(double dt)
{
	/*for (auto it = this->removeQueue.begin(); it != this->removeQueue.end(); ++it) {
		delete (*it);
	}
	this->removeQueue.clear();*/
	while (!this->removeQueue.empty()) {
		GameObject* go = this->removeQueue.front();
		delete go;
		this->removeQueue.pop();
	}
}

void ggEngine::MemoryManager::Reset()
{
}

void ggEngine::MemoryManager::AddObjectToRemoveQueue(GameObject * gameObject)
{
	this->removeQueue.push(gameObject);
	//this->removeQueue.push_back(gameObject);
}
