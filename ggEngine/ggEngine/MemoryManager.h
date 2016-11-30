#pragma once
#include "ComponentBase.h"
#include <queue>
namespace ggEngine {
	class Game;
	class GameObject;
	class MemoryManager : public ComponentBase {
	public:
		MemoryManager(Game *game);
		~MemoryManager();

		// Inherited via ComponentBase
		void Update(double dt) override;
		void Reset() override;

		void AddObjectToRemoveQueue(GameObject *gameObject);
	private:
		Game *game;
		std::queue<GameObject*> removeQueue;
	};
}