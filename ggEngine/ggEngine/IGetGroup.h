#pragma once
#include <list>
namespace ggEngine {
	class Group;
	class IGetGroup {
	public:
		~IGetGroup() {}
		virtual std::list<Group*> *GetGroupList() = 0;
	};
}