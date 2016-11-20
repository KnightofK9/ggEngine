#include "Group.h"
namespace ggEngine{
	class World : public Group{
	public:
		World(DrawManager *drawManager);
		~World();
		void Reset();
		void UpdateWorldPosition() override;
	};
}