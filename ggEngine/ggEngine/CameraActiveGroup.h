#pragma once
#include "Group.h"
namespace ggEngine {
	class Game;
	class Camera;
	class CameraActiveGroup : public Group {
	public:
		CameraActiveGroup(Game *game);
		~CameraActiveGroup();
		
		void Update() override;
		void UpdatePhysics() override;
		void Draw() override;
		std::list<GameObject*> GetDrawList() override;
	private:
		Camera *camera = nullptr;
		std::list<GameObject*> activeGameObjectList;

	};
}