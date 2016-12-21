#pragma once
#include "Group.h"
namespace ggEngine {
	class Game;
	class Camera;
	class CameraActiveGroup : public Group {
	public:
		CameraActiveGroup(Game *game);
		~CameraActiveGroup();
		
		virtual void Update() override;
		virtual void UpdatePhysics() override;

		virtual void CheckCollisionTo(std::list<GameObject*> staticGoList);
		virtual void Draw() override;
		std::list<GameObject*> GetDrawList() override;
	protected:
		Camera *camera = nullptr;
		std::list<GameObject*> activeGameObjectList;

	};
}