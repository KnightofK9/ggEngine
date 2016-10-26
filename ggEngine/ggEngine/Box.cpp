#include "Box.h"
namespace ggEngine{

	Box::Box(double x, double y, double w, double h, double vx, double vy){
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->vx = vx;
		this->vy = vy;
	}
	Box::Box(){
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
		this->vx = 0;
		this->vy = 0;
	}
	

	std::string Box::CreateJson(){
		Json json;
		json.AddMember("x", x, json.GetAllocator());
		json.AddMember("y", y, json.GetAllocator());
		json.AddMember("w", w, json.GetAllocator());
		json.AddMember("h", h, json.GetAllocator());
		json.AddMember("vx", vx, json.GetAllocator());
		json.AddMember("vy", vy, json.GetAllocator());
		return json.GetCharArray();
	}
	void Box::ParseJson(std::string jsonChar){
		Json json(jsonChar);
		x = json["x"].GetDouble();
		y = json["y"].GetDouble();
		w = json["w"].GetDouble();
		h = json["h"].GetDouble();
		vx = json["vx"].GetDouble();
		vy = json["vy"].GetDouble();
	}
}