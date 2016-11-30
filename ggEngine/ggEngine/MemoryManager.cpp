#include "MemoryManager.h"

ggEngine::MemoryManager::MemoryManager(Game * game)
{
	this->game = game;
}

ggEngine::MemoryManager::~MemoryManager()
{
}

void ggEngine::MemoryManager::Update(double dt)
{

}

void ggEngine::MemoryManager::Reset()
{
}

void ggEngine::MemoryManager::AddObjectToRemoveQueue(GameObject * gameObject)
{
	this->removeQueue.push(gameObject);
}
