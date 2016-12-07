#include "Factory.h"
#include "TileBase.h"
GameObject* Factory::GetInstanceOf(std::string type)
{
	GameObject *go;
	if (type == "TileBrick") {
		//go = new TileB
	}
	return go;
}
