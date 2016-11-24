#include "Json.h"
#include <fstream>
#include <filereadstream.h>
#include <cstdio>
ggEngine::Json::Json(std::string jsonChar,bool isLocation)
{
	if (isLocation) {
		std::string location = jsonChar;
		FILE* fp = fopen(location.c_str(), "rb"); // non-Windows use "r"
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		this->ParseStream(is);
		fclose(fp);
		allocator = &this->GetAllocator();
		return;
	}
	this->Parse(jsonChar.c_str());
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

const std::string ggEngine::Json::GetCharArray(){
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	this->Accept(writer);
	std::string o = buffer.GetString();
	return o;
}

std::string ggEngine::Json::GetCharArrayFromValue(const rapidjson::Value & val)
{
	rapidjson::StringBuffer buf;
	rapidjson::Writer<rapidjson::StringBuffer> wr(buf);
	val.Accept(wr);
	return buf.GetString();
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
