#pragma once
#include <list>
namespace ggEngine {
	class Group;
	class IGetGroup {
	public:
		virtual ~IGetGroup() {}
		virtual std::list<Group*>* GetGroupList() = 0;
	};
}