#include "DrawObject.h"
#include <string>
namespace ggEngine{
	class SpriteInfo;
	class Tile : public DrawObject{
	public:
		Tile(DrawManager *DrawManager);
		~Tile();
		void Draw();
	private:
		SpriteInfo *image = nullptr;
		std::string tileId;
	};
}