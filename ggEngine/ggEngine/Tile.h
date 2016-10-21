#include "DrawObject.h"
#include <string>
namespace ggEngine{
	class SpriteInfo;
	class Tile : public DrawObject{
	public:
		void Draw();
	private:
		SpriteInfo *image = nullptr;
		std::string tileId;
	};
}