#pragma once
#include <rapidjson.h>
#include <document.h>
#include <string>
#include <stringbuffer.h>
#include <writer.h>
#include <vector>
#include "IValueable.h"
#include <error\error.h>
#include <prettywriter.h>
#define RAPIDJSON_HAS_STDSTRING 1
namespace ggEngine {
	class Json: public rapidjson::Document {
	public:
		Json(std::string jsonChar,bool isLocation = false);
		Json();
		~Json();
		const std::string GetCharArray();
		static std::string GetCharArrayFromValue(const rapidjson::Value &val);
		void SaveTo(std::string location);
	private:
		rapidjson::Document::AllocatorType* allocator;
	};
}