#pragma once
#include "ComponentBase.h"
#include <queue>
#include <list>
namespace ggEngine {
	class Game;
	class GameObject;
	class MemoryManager : public ComponentBase {
	public:
		MemoryManager(Game *game);
		virtual ~MemoryManager();

		// Inherited via ComponentBase
		void Update(double dt) override;
		void Reset() override;

		void AddObjectToRemoveQueue(GameObject *gameObject);
	private:
		Game *game;
		std::list<GameObject*> removeQueue;
		//std::queue<GameObject*> removeQueue;
	};
}