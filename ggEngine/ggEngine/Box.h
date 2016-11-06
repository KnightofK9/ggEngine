#pragma once
#include <d3d9.h>
#include "ISerializable.h"
#include "IJsonable.h"
#include "Rect.h"
namespace ggEngine {
	class Box : public ISerializable, public IJsonable {
	public:
		Box(double x, double y, double w, double h, double vx, double vy);
		Box();
		double x, y;
		double w, h;
		double vx, vy;
		double r, d;
		Rect GetRect() { return Rect{ x,y,(x + w),(y + h) }; }

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {
			ar & x;
			ar & y;
			ar & w;
			ar & h;
			ar & vx;
			ar & vy;
		}
		// Inherited via IJsonable
		virtual std::string CreateJson() override;
		virtual void ParseJson(std::string jsonChar) override;
	private:

	};
}