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
	template < class Archive >
	void Box::serialize(Archive & ar, const unsigned int version){
		ar & x;
		ar & y;
		ar & w;
		ar & h;
		ar & vx;
		ar & vy;
	}
}