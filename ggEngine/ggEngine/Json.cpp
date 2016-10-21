#include "Json.h"
#include <fstream>
#include <filereadstream.h>
#include <cstdio>
ggEngine::Json::Json(const char * jsonChar)
{
	this->Parse(jsonChar);
	allocator = &this->GetAllocator();
}

ggEngine::Json::Json(std::string location)
{
	FILE* fp = fopen(location.c_str(), "rb"); // non-Windows use "r"
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	this->ParseStream(is);
	fclose(fp);
	allocator = &this->GetAllocator();
}

ggEngine::Json::Json()
{
	this->SetObject();
	allocator = &this->GetAllocator();
}


ggEngine::Json::~Json()
{
}

const char* ggEngine::Json::GetCharArray(){
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	this->Accept(writer);
	const char* output = buffer.GetString();
	return output;
}


void ggEngine::Json::SaveTo(std::string location)
{
	std::ofstream ofs(location);
	{
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		this->Accept(writer);
		std::string json(buffer.GetString(), buffer.GetSize());
		ofs << json;
		if (!ofs.good()) throw std::runtime_error("Can't write the JSON string to the file!");
	}
}
