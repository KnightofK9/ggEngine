#include "IJsonable.h"
namespace ggEngine {
	void IJsonable::SaveJsonTo(std::string location)
	{
		auto s = this->CreateJson();
		Json json(s);
		json.SaveTo(location);
	}
	void IJsonable::ParseJsonFrom(std::string location)
	{
		Json json(location);
		this->ParseJson(json.GetCharArray());
	}
}

