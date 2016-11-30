#pragma once
namespace ggEngine {
	class GGObject {
	public:
		GGObject();
		virtual ~GGObject();
		virtual void Destroy(){
			this->alive = false;
		}
		bool IsAlive() { return this->alive; }
	protected:
		bool alive;
	};
}