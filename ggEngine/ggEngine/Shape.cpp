#include "Shape.h"

ggEngine::Rect ggEngine::Shape::GetRect()
{
	return Rect(this->GetLeft(),this->GetUp(),this->GetRight(),this->GetDown());
}
