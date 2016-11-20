#include "Group.h"
namespace ggEngine{
	class World : public Group{
	public:
		World();
		~World();
		void Reset();
		void UpdateWorldPosition() override;
	};
}