#pragma once
#include <rapidjson.h>
#include <document.h>
#include <string>
#include <stringbuffer.h>
#include <writer.h>
#include <vector>
#include "IValueable.h"
#define RAPIDJSON_HAS_STDSTRING 1
namespace ggEngine {
	class Json: public rapidjson::Document {
	public:
		Json(std::string jsonChar,bool isLocation = false);
		Json();
		~Json();
		const std::string GetCharArray();
		void SaveTo(std::string location);
	private:
		rapidjson::Document::AllocatorType* allocator;
	};
}