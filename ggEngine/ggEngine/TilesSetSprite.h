#include "GGObject.h"
#include "IJsonable.h"
#include <d3d9.h>
#include <string>
namespace ggEngine{
	class Texture;
	class TilesSetSprite : public GGObject{
	public:
	private:
		int cellWidth;
		int cellHeight;
		int width;
		int height;
		int numberOfCell;
		std::string tilesSetId;
		Texture *tileSetTexture;
	};
}