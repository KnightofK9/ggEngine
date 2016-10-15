#include "NiseVector.h"
#include "Matrix.h"
ggEngine::NiseVector::NiseVector(double x, double y):Vector(x,y)
{
	orgX = x;
	orgY = y;
}

ggEngine::NiseVector::NiseVector(double f):Vector(f)
{
	orgX = f;
	orgY = f;
}

ggEngine::NiseVector::NiseVector(const D3DXVECTOR2 & v): Vector(v)
{
	orgX = v.x;
	orgY = v.y;
}

ggEngine::NiseVector::NiseVector() :Vector(1, 1)
{
	orgX = 1;
	orgY = 1;
}

ggEngine::NiseVector::~NiseVector()
{
}

void ggEngine::NiseVector::SetTransform(Matrix mat)
{
	D3DXVec2TransformCoord(this, &Vector(orgX, orgY), &mat);
}
