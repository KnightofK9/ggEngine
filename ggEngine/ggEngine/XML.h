#pragma once
#include <msxml.h>
#include <string>
#include "GGObject.h"

namespace ggEngine {
	class XML : public GGObject {
	public:
		XML(std::string path);
		~XML();
	};
}