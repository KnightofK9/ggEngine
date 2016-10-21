#include "GGObject.h"
#include "IJsonable.h"
#include <d3d9.h>
#include <string>
namespace ggEngine{
	class Texture;
	class TilesSetSprite : public GGObject, public IJsonable{
	public:
		TilesSetSprite();
		~TilesSetSprite();
		void CreateJson(Json json);
		void ParseJson(Json json);
		void Destroy(bool isClearFromCache = false);
	private:
		int cellWidth;
		int cellHeight;
		int width;
		int height;
		int numberOfCell;
		std::string tilesSetName;
		Texture *tileSetTexture;
	};
}