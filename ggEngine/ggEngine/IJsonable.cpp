#include "IJsonable.h"
namespace ggEngine {
	void IJsonable::SaveJsonTo(std::string location)
	{
		Json json(this->CreateJson());
		json.SaveTo(location);
	}
	void IJsonable::ParseJson(std::string location)
	{
		Json json(location);
		this->ParseJson(json.GetCharArray());
	}
}

